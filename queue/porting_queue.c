#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
typedef struct
{
    int q1stWordOfMsg;                /* First word of a queue message.  */
    int q2ndWordOfMsg;                /* Second word of a queue message. */
    int q3rdWordOfMsg;                /* Third word of a queue message.  */
    int q4thWordOfMsg;                /* Fourth word of a queue message. */
} IPANEL_QUEUE_MESSAGE;
typedef struct
{
	IPANEL_QUEUE_MESSAGE message;
	struct queue_node *next;
	char name[8];
	int value_flag;
}queue_node;
typedef struct
{
	queue_node *queue;
	int len;
}porting_queue;
/************************************/
static porting_queue *m_queue;
static queue_node *w_ptr,*r_ptr;
static int  w_count,r_count;
static pthread_mutex_t q_mutex;
/***********************************/


queue_node* __list_create(int len)
{
	queue_node *listnode = NULL;
	queue_node *temp_p1 = NULL;
	queue_node *temp_p2 = NULL;
	int i = 0;
	listnode = (queue_node *)malloc(sizeof(queue_node));
	if(listnode == NULL)
	{
		printf("printf __list_create fail\n");
		return NULL;
	}
	temp_p2 = temp_p1 = listnode;
	memset(&listnode->message,0,sizeof(IPANEL_QUEUE_MESSAGE));
	if(len > 0)
	{
		for(i = 0;i < len;i++)
		{
			temp_p1 = (queue_node *)malloc(sizeof(queue_node));
			if(temp_p1 == NULL)
			{
				printf("temp_p1 fail\n");
				return NULL;
			}
			memset(&temp_p1->message,0,sizeof(IPANEL_QUEUE_MESSAGE));
			temp_p1->value_flag = 0;
			temp_p2->next = temp_p1;
			temp_p2 = temp_p1;
		}
		temp_p1->next = listnode;
		return listnode;
	}
	else
	{
		printf("len is Illegal values =< 0\n");
		return NULL;
	}
}
int porting_queue_create(const char *name, int len)
{
//	printf("porting_queue_create start\n");
	pthread_mutex_init(&q_mutex,NULL);
	m_queue = (porting_queue *)malloc(sizeof(porting_queue));
	m_queue->queue = __list_create(len);
	m_queue->len = len;
	if(strlen(name) < 8)
	{
		strncpy(m_queue->queue->name,name,strlen(name));
	}
	w_ptr = r_ptr = m_queue->queue;
//	printf("porting_queue_create end\n");
}
#if 0
void porting_queue_destory(porting_queue *L)
{
	printf("porting_queue_destory start\n");
	int i;
	for(i = 0;i < L->len;i++)
	{

	}
	printf("porting_queue_destory end\n");
}
#endif
int porting_queue_send(IPANEL_QUEUE_MESSAGE *message)
{
//	printf("porting_queue_send start\n");
	queue_node *p1,*p2;
	p1 = w_ptr;
	p2 = p1->next;
	pthread_mutex_lock(&q_mutex);
	if(w_ptr->next != m_queue->queue)
	{
		printf("[%s] : conditon 1\n", __FUNCTION__);
		if(p2->value_flag == 1)
		{
			printf("send error\n");
			goto A_ERR;
		}
		else
		{
			memcpy(&p2->message,message,sizeof(IPANEL_QUEUE_MESSAGE));
#if 0
			p2->value_flag = 1;
#else
			w_ptr->value_flag = 1;
#endif
			w_count += 1;
			w_ptr = p2;
		}
	}
	else
	{
		printf("[%s] : conditon 2. maybe error\n", __FUNCTION__);
		if(p2->value_flag == 1)
		{
			printf("send2 error\n");
			goto A_ERR;
		}
		else
		{
			memcpy(&p2->message,message,sizeof(IPANEL_QUEUE_MESSAGE));
#if 0
			p2->value_flag = 1;
#else
			w_ptr->value_flag = 1;
#endif
			w_ptr = m_queue->queue;
			w_count = 0;
		}
	}
	pthread_mutex_unlock(&q_mutex);
//	printf("porting_queue_send end\n");
	return 0;
A_ERR:
	pthread_mutex_unlock(&q_mutex);
//	printf("porting_queue_send end\n");
	return -1;
}
int porting_queue_read(IPANEL_QUEUE_MESSAGE *message)
{
//	printf("porting_queue_read start\n");
	pthread_mutex_lock(&q_mutex);
	queue_node *p1,*p2;
	p1 = r_ptr;
	p2 = r_ptr->next;
	if(r_ptr->next != m_queue->queue)
	{
		printf("[%s]:condition 1\n", __FUNCTION__);
		if(r_ptr->value_flag == 1)
		{
			memcpy(message,&r_ptr->message,sizeof(IPANEL_QUEUE_MESSAGE));
			r_ptr->value_flag = 0;
			r_count += 1;
			r_ptr = p2;
		}
		else
		{
			printf("this node is null\n");
			goto A_ERR;
		}
	}
	else
	{
		printf("[%s]:condition 2\n", __FUNCTION__);
		if(r_ptr->value_flag == 1)
		{
			memcpy(message,&r_ptr->message,sizeof(IPANEL_QUEUE_MESSAGE));
			r_ptr->value_flag = 0;
			r_ptr = m_queue->queue;
			r_count = 0;
		}
		else
		{
//			printf("next is headnode,cur node is null\n");
			goto A_ERR;
		}
	}
	pthread_mutex_unlock(&q_mutex);
//	printf("porting_queue_read end\n");
	return 0;
A_ERR:
	pthread_mutex_unlock(&q_mutex);
//	printf("porting_queue_read NULL\n");
	return -1;
}
void *send_1(void *arg);
void *send_2(void *arg);
int main()
{
	pthread_t pid1;
	pthread_t pid2;
	int i = 0;
	int j = 0;
	IPANEL_QUEUE_MESSAGE event;
	porting_queue_create("test",36);
	pthread_create(&pid1, NULL, send_1, 0);
	pthread_create(&pid2, NULL, send_2, 0);
	while(1)
	{
		if(-1 == porting_queue_read(&event))
		{
		//	printf("node is null\n");
			printf("[main]:send_1=%d, send_2=%d\n",i,j);
	//		sleep(1);
			usleep(500*1000);
		}
		else
		{
			if(event.q1stWordOfMsg == 113)
			{
				i++;
			}
			if(event.q1stWordOfMsg == 114)
			{
				j++;
			}
		}
	}
	return 0;
}
void *send_1(void *arg)
{
	int i = 0;
	while(1)
	{
		IPANEL_QUEUE_MESSAGE event;
		event.q1stWordOfMsg = 114;
		event.q2ndWordOfMsg = 0;
	    event.q3rdWordOfMsg = 0;
	    event.q4thWordOfMsg = 0;
#if 0
	    if(-1 == porting_queue_send(&event))
	    {
	    	printf("send_1 again\n");
	    	porting_queue_send(&event);
	    }
	    else
	    {
	    	usleep(50*1000);
		}
#else
		printf("[%s]: send %d\n", __FUNCTION__, i+1);
	    if(-1 == porting_queue_send(&event))
		{
			sleep(1);
			continue;
		}
#endif
	    i++;
	    if(i >= 100)
	    	break;
	    usleep(500*1000);
		//sleep(1);

	}
}
void *send_2(void *arg)
{
	int i = 0;
	while(1)
	{
		IPANEL_QUEUE_MESSAGE event;
		event.q1stWordOfMsg = 113;
		event.q2ndWordOfMsg = 0;
	    event.q3rdWordOfMsg = 0;
	    event.q4thWordOfMsg = 0;
#if 0
	    if(-1 == porting_queue_send(&event))
	    {
	    	printf("send_2 again\n");
	    	porting_queue_send(&event);
	    }
	    else
	    {
	    	usleep(50*1000);
	    }
#else
		printf("[%s]: send %d\n", __FUNCTION__, i+1);
	    if(-1 == porting_queue_send(&event))
	    {
			sleep(1);
			continue;
		}
#endif
	    i++;
		printf("[%s]: send %d\n", __FUNCTION__, i);
	    if(i >= 100)
	    	break;
		usleep(500*1000);
		//sleep(1);
	}
}
