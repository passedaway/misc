/*
 * =====================================================================================
 *
 *       Filename:  keymgnr.c
 *
 *    Description:  key manager for ipanel porting input
 *
 *        Version:  1.0
 *        Created:  2012年11月01日 12时01分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */
#include "keymgnr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _MAX_KEY_NUM_ 512

#define THIS_printf(fmt, args...)	do{ if( print_flag ) {printf(fmt, ## args ); } }while(0)

typedef struct ipanel_key_s{
	unsigned short ipanel_key;
	unsigned int keycode;
}ipanel_key_t;

typedef struct key_mgnr_s{
	unsigned int usercode;
	unsigned int nums;
	const char *ir_cfg_name;
	ipanel_key_t *key;
}key_mgnr_t;

/* ************************************************************************************ */
/* local varable declearing */
static key_mgnr_t m_key_mgnr;

/* local function declearing */
static int construct_key_mgnr(key_mgnr_t *);
static long long mystrtol(char *str); /*  stdlib.h strtol cannot process 0xabcd, so rewirte it */

static int print_flag = 0;

/* ************************************************************************************* */
/* global function implementing */
int key_mgnr_init(const char *ir_cfg_name, int pflag)
{
	if( ir_cfg_name == NULL )
		return -1;

	print_flag = pflag;

	if( m_key_mgnr.nums != 0 )
	{
		if( 0 == strcmp(m_key_mgnr.ir_cfg_name, ir_cfg_name) )
		{
			return -1;
		}

		free(m_key_mgnr.key);
		m_key_mgnr.key = NULL;
		m_key_mgnr.nums = 0;
	}

	m_key_mgnr.key = (ipanel_key_t*)malloc(sizeof(ipanel_key_t)*_MAX_KEY_NUM_);
	if( m_key_mgnr.key == NULL )
	{
		return -1;
	}
	memset(m_key_mgnr.key, 0, sizeof(ipanel_key_t)*_MAX_KEY_NUM_);

	m_key_mgnr.ir_cfg_name = ir_cfg_name;

	return construct_key_mgnr(&m_key_mgnr);
}

void key_mgnr_exit(void)
{
	if( m_key_mgnr.key )
	{
		free(m_key_mgnr.key);
		m_key_mgnr.key = NULL;
	}
	m_key_mgnr.nums = 0;
}

int key_mgnr_get_usercode(void)
{
	return m_key_mgnr.usercode;
}

int key_mgnr_get_ipanel_key(unsigned int keycode)
{
	int i = 0;
	for (; i < m_key_mgnr.nums; i++)
	{
		if ( m_key_mgnr.key[i].keycode == keycode )
			return m_key_mgnr.key[i].ipanel_key;
	}

	return -1;
}

int key_mgnr_get_input_key(unsigned int ipanel_key)
{
	int i = 0;
	for (; i < m_key_mgnr.nums; i++)
	{
		if ( m_key_mgnr.key[i].ipanel_key == ipanel_key)
			return m_key_mgnr.key[i].keycode;
	}

	return -1;
}

int key_mgnr_get_keynums()
{
	return m_key_mgnr.nums;
}

/* ************************************************************************************ */
/* local function implementing */
int construct_key_mgnr(key_mgnr_t *pkeymgnr)
{
	FILE *fp = NULL;
	char buf[121] = {0};

	char *equalp = NULL, *frontp = NULL, *endp= NULL, *tmp = NULL;
	int i = 0;
	int ipanel_key = 0, keycode = 0;

	if( pkeymgnr == NULL )
		return -1;

	fp = fopen(pkeymgnr->ir_cfg_name, "r");
	if( !fp )
	{
		perror("open file ");
		return -1;
	}

	for( ; NULL != fgets(buf, 120, fp);  memset(buf, 0, sizeof(buf)) )
	{
		i++;
		THIS_printf("line %d : %s ", i, buf);

		/* 1.ignore spcase or tab */
		frontp = buf;
		while( *frontp == ' ' || *frontp == '\t' )
			frontp++;

		/* 2.check if '#' is the first bytes */
		if( *frontp == '#' )
		{
			THIS_printf("line %d : is comment.\n", i);
			continue;
		}

		/*  3. check syntax */
		/*  have '=' */
		equalp = strchr(frontp, '=');
		if( equalp == NULL )
		{
			THIS_printf("line %d syntax error : no '='\n", i);
			continue;
		}
		tmp = strchr(equalp+1, '=');
		if( tmp != NULL )
		{
			THIS_printf("line %d syntax error : have more then one '='\n", i);
			continue;
		}
		
		/*  if have '#' , should after '=' */
		endp = strchr(frontp, '#');
		if( endp && (endp < equalp) )
		{
			THIS_printf("line %d : syntax error. no '=' is valid.\n", i);
			continue;
		}
		endp = equalp+1;

		/*  first field should end with '_num' */
		tmp = equalp-1;
		while( (equalp != tmp) &&  (frontp != tmp) &&
				(*tmp != '_') &&
				(*tmp == ' ' || *tmp == '\t' || (*tmp >= '0' && *tmp <='9') )
			)
			tmp--;

		if( (equalp <= tmp) || (frontp == tmp ) ||  (*tmp != '_' ) )
		{
			THIS_printf("tmp = %s\n", tmp);
			THIS_printf("line %d : syntax error. first field is not end with '_num' \n", i);
			continue;
		}
		frontp = tmp+1;

		/* second field should all num or xX abcdefABCDEF  */
		tmp = endp;
		if( *tmp == '0' )
		{
			tmp++;
			if( *tmp == 'x' || *tmp == 'X' )
				*tmp++;
		}

		while( (*tmp != 0) && (*tmp != '#') && (*tmp != ' ' ) && (*tmp != '\t') && (*tmp != '\n') && (*tmp != '\r') )
		{
			if( ( (*tmp >='0') && (*tmp <='9') ) ||
				( (*tmp >='a') && (*tmp <='f') ) || 
				( (*tmp >='A') && (*tmp <='F') )  )
				*tmp++;
			else
			{
				THIS_printf("error : %s \n", tmp);
				tmp = NULL;
				break;
			}
		}
		if( tmp == NULL )
		{
			THIS_printf("line %d syntax error. second field is not all num \n", i );
			continue;
		}

		THIS_printf("process over : frontp = %s\n endp=%s\n", frontp, endp);

		/*  syntax is ok */
		ipanel_key = (int)mystrtol(frontp);
		keycode = (int)mystrtol(endp);

		//printf("ipanel_key = %d  keycode = %d\n", ipanel_key, keycode);
		/* end. copy the data to the struct */
		if( ipanel_key == 0 )
		{
			pkeymgnr->usercode = keycode;
		}else{
			pkeymgnr->key[pkeymgnr->nums].ipanel_key = ipanel_key ;
			pkeymgnr->key[pkeymgnr->nums].keycode= keycode;
			pkeymgnr->nums ++;
		}
	}

	fclose(fp);
	return 0;
}

long long mystrtol(char *str)
{
	char *end = 0;
	long long data = 0;
	long long qen = 1, qenue = 0;

	while( *str != 0 )
	{
		if( *str == ' ' || *str == '\t' )
			str++;
		else
			break;
	}

	if(*str == '0' && ( *(str + 1) == 'x' || *(str+1) == 'X'))
	{
		qenue = 16;
		str += 2;
	}
	else
		qenue = 10;

	end = str;
	while( *end != 0 )
	{
		if ( ((*end >= '0') && (*end <= '9')) ||
			((*end >= 'a') && (*end <= 'f' )) ||
			((*end >= 'A') && (*end <= 'F' ))  )
			end++;
		else
			break;
	}
	end--;

	while(end >= str)
	{
		if(*end >= '0' && *end <= '9')
			data += (*end - '0') * qen;
		else if( *end >= 'a' && *end <= 'f')
			data += (*end - 'a' + 0x0a) * qen;
		else if( *end >= 'A' && *end <= 'F')
			data += (*end - 'A' + 0x0a) * qen;
		else
			return data;

		end--;
		qen *= qenue;
	}

	return data;
}

