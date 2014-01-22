/*
 * =====================================================================================
 *
 *       Filename:  watch.c
 *
 *    Description:  implement the api which defines in watch.h 
 *
 *        Version:  1.0
 *        Created:  05/26/2013 12:44:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *			Email:	echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */

#include "watch.h"
#include "hash.h"

#include <unistd.h>
#include <linux/inotify.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
#ifdef DEBUG_WATCH
#define MODULE_NAME		"watch"
#define dbg(fmt, args...)	printf(MODULE_NAME"[%s]: "fmt, __FUNCTION__, ##args )
#else
#define dbg(fmt, args...)
#endif
#else
#define dbg(fmt, args...)	
#endif

/* *******************module local varable*************** */
typedef struct patch_hash_s{
	int fd, prefix_fd;
	unsigned int hash;
}path_hash_t;

#define PATH_ENTRY_NUM	256	
#define PATH_ENTRY_SIZE	PATH_ENTRY_NUM*sizeof(path_hash_t) + 16384
typedef struct path_entry_s{
	struct path_entry_s *next;
	int min, max;/* min value & max value from this entry */
	char *start, *end;
	path_hash_t path_hash[0];/* every data saved is: fd + prefix_fd + hash */
}path_entry_t;
/* when save , not save it's fullpath
 *	save this level name and hash_entry
 *	and plus prefix name's hash entry,
 *	so  it some directory changes, 
 *	I can adjust all result's by 
 *	"calculate" the path, not just read
 * */
typedef struct watch_entry_s{
	int fd;
	watch_handler_t handler;
	path_entry_t *normal_entry, *except_entry;
	hash_table_t hash_table;/* every watch data has an hash_table */
}watch_entry_t;

typedef struct watch_data_s{
	int init;
	int max_instance;
	pthread_t task_pid;
	int task_runflag;

	watch_entry_t *entry;
}watch_data_t;
static watch_data_t g_watch_data;
/* *****************local function declare*************** */
#if 1
#define WATCH_EVENTS	IN_CREATE | IN_DELETE | IN_DELETE_SELF | IN_MOVE_SELF | IN_MOVE
#else
#define WATCH_EVENTS	IN_ALL_EVENTS
#endif
static void *_watch_task(void* args);
static int _watch_on_dir_recur(watch_entry_t *pentry, const char *dir_path, int parent_fd);
static int _watch_on_directory(watch_entry_t *pentry, const char *dir_path, int recursive);
static void _default_handler(watch_entry_t *pentry, int file_fd, 
		const char *dir_name, E_CHANGE_MODE_t change_mode);
static void _process_event(watch_entry_t *pentry);
static path_entry_t *_get_path_entry(void);

static unsigned int _get_hash_by_fd(watch_entry_t *pentry, int file_fd);
static char *_get_path_by_fd(watch_entry_t *pentry, int file_fd, 
			char *path_buf, int *path_len);
static int _map_fd_path(watch_entry_t *pentry, int file_fd, 
			const char *dir_path, int parent_fd);

static inline int str_end_with(const char *str, int c)
{
	int len = strlen(str);
	return str[len-1] == c;
}

/* *******************global function impe*************** */
int watch_init(int max_instance)
{
	/* check param */
	if( max_instance < 0 )
	{
		return -1;
	}

	/* check already init */
	if( g_watch_data.init )
		return -1;

	/* malloc data */
	g_watch_data.max_instance = max_instance ? max_instance : 16;
	g_watch_data.entry = (watch_entry_t *)malloc( sizeof(watch_entry_t) * \
								g_watch_data.max_instance );
	if( NULL == g_watch_data.entry )
	{
		dbg("memory out\n");
		return -1;
	}

	/* init data */
	{
		int i = 0;
		watch_entry_t *pentry = g_watch_data.entry;
		for(; i < g_watch_data.max_instance; i++, pentry++)
		{
			pentry->fd = -1;
		}
	}

	/* start thread */
	g_watch_data.task_runflag = 1;
	if( -1 == pthread_create(&g_watch_data.task_pid, NULL, _watch_task, NULL) )
	{
		dbg("create task error\n");
		goto err_out;
	}

	/* set init flag */
	g_watch_data.init = 1;

	return 0;

	/* clear allocated data */
err_out:
	/* set int flag to 1, then call watch_exit */
	g_watch_data.init = 1;
	watch_exit(1);
	return -1;
}

void watch_exit(int sync)
{
	dbg("in. sync=%d\n", sync);
	/* check if init */
	if( !g_watch_data.init )
	{
		return ;
	}

	/* free data */
	if( g_watch_data.entry )
	{
		int i = 0;
		watch_entry_t *pentry = g_watch_data.entry;
		for( ; i < g_watch_data.max_instance; i++, pentry++ )
		{
			if(-1 != pentry->fd)
			{
				watch_off(i+1);
			}
		}
	}

	/* stop thread */
	if( g_watch_data.task_pid )
	{
		/* just set runflag to 0, the thread will stop */
		g_watch_data.task_runflag = 0;
		if( sync )
		{
			while(2 != g_watch_data.task_runflag )
				usleep(100*1000);
		}
		g_watch_data.task_pid = 0;
	}

	/* clear init flag */
	g_watch_data.init = 0;

	dbg("out\n");
	return;
}

int watch_on(const char *dir_path, E_WATCH_MODE_t mode)
{
	int index;
	int ret = -1;
	watch_entry_t *pentry = g_watch_data.entry;

	/* check param */
	if( !dir_path || mode >= E_WATCH_MODE_MAX )
		return -1;

	/* check module init */
	if( !g_watch_data.init )
		return -1;

	/* find valid entry */
	for( index = 0; index < g_watch_data.max_instance; index++, pentry++)
	{
		if( -1 == pentry->fd )
		{
			pentry->handler = NULL;
			break;
		}
	}
	if( index >= g_watch_data.max_instance )
		return -1;

	/* init entry data */
	pentry->normal_entry = NULL;
	pentry->except_entry = NULL;
	/* init hash table */
	hash_table_init(&pentry->hash_table);

	dbg("watch:hash_table init over\n");
	/* just watch this */
	ret = _watch_on_directory(pentry, dir_path, mode);

	/* if has error, return -1 */
	if( ret )
		return -1;
	return index+1;
}

int watch_off(int watch_fd)
{
	watch_entry_t *pentry = g_watch_data.entry;

	dbg("in watch_fd = %d\n", watch_fd);
	/* check init */
	if( !g_watch_data.init )
		return -1;
	/* check fd valid */
	if((watch_fd < 0) ||  (watch_fd > g_watch_data.max_instance))
		return -1;
	/* check pentry is be used */
	pentry += (watch_fd - 1);
	if( -1 != pentry->fd )
	{
		return -1;
	}

	/* clear data */
	/* 1.remove all watched child */
	/* todo */

	/* 2. close this fid */
	close(pentry->fd);
	pentry->fd = -1;
	{
		path_entry_t *path_entry = pentry->normal_entry;
		path_entry_t *tmp = NULL;
		while( path_entry )
		{
			tmp = path_entry ;
			path_entry = path_entry->next;
			free(tmp);
		}

		path_entry = pentry->except_entry;
		while( path_entry )
		{
			tmp = path_entry;
			path_entry = path_entry->next;
			free(tmp);
		}

		pentry->normal_entry = NULL;
		pentry->except_entry = NULL;
	}
	/* 3.free hash table */
	hash_table_exit(&pentry->hash_table);

	dbg("out\n");
	return 0;
}

int watch_rm(int watch_fd, int file_fd)
{
	watch_entry_t *pentry = g_watch_data.entry;

	/* check init */
	if( !g_watch_data.init )
		return -1;
	/* check fd valid */
	if( watch_fd > g_watch_data.max_instance || file_fd <= 0)
		return -1;
	/* check pentry is be used */
	pentry += (watch_fd - 1);
	if( -1 != pentry->fd )
	{
		return -1;
	}

	/* remove */
	return inotify_rm_watch(pentry->fd, file_fd);

}

int watch_add(int watch_fd, const char *dir_path, E_WATCH_MODE_t mode)
{
	int file_fd = -1;
	watch_entry_t *pentry = g_watch_data.entry;

	/* check init */
	if( !g_watch_data.init )
		return -1;
	/* check fd valid */
	if( watch_fd > g_watch_data.max_instance )
		return -1;
	/* check pentry is be used */
	pentry += (watch_fd - 1);
	if( -1 != pentry->fd )
	{
		return -1;
	}

	/* add this dir_path by it's mode */
	if( WATCH_THIS == mode )
	{
		file_fd = inotify_add_watch(pentry->fd, dir_path, WATCH_EVENTS);
		if( -1 == file_fd )
		{
			close(pentry->fd);
			pentry->fd = -1;
			return -1;
		}
	}else{
		return _watch_on_dir_recur(pentry, dir_path, -1);
	}

	return file_fd;
}

int watch_remove_handler(int watch_fd)
{
	watch_entry_t *pentry = g_watch_data.entry;

	/* check init */
	if( !g_watch_data.init )
		return -1;
	/* check fd valid */
	if( watch_fd > g_watch_data.max_instance )
		return -1;
	/* check pentry is be used */
	pentry += (watch_fd - 1);
	if( -1 == pentry->fd )
		return -1;

	/* just set handler null */
	pentry->handler = NULL;

	return 0;
}

int watch_install_handler(int watch_fd, watch_handler_t watch_handler)
{
	watch_entry_t *pentry = g_watch_data.entry;

	/* check init */
	if( !g_watch_data.init )
		return -1;
	/* check watch_handler */
	if( !watch_handler )
		return -1;
	/* check fd valid */
	if( (watch_fd > g_watch_data.max_instance) || (watch_fd < 0))
		return -1;
	/* check pentry is be used */
	pentry += (watch_fd - 1);
	if( -1 == pentry->fd )
		return -1;

	pentry->handler = watch_handler;
	return 0;
}

/* ******************* local function impe*************** */
static void *_watch_task(void* args)
{
	fd_set rfds;
	struct timeval timeout;

	watch_entry_t *pentry;
	int i = 0, max_fd = 0, ret;

	dbg("task start\n");
	while( g_watch_data.task_runflag )
	{
		/* set timeout value */
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		/* add fds */
		FD_ZERO(&rfds);
		for(i=0, max_fd=0, pentry = g_watch_data.entry; \
				i < g_watch_data.max_instance; \
				i++, pentry++)
		{
			if( -1 != pentry->fd )
			{
				FD_SET(pentry->fd, &rfds);
				if( pentry->fd > max_fd )
					max_fd = pentry->fd;
			}
		}

		if( 0 == max_fd )
		{
			usleep(50*1000);
			dbg("no watched\n");
			continue;
		}
		//dbg("watched %d\n", max_fd);

		/* do select */
		ret = select(max_fd + 1, &rfds, NULL, NULL, &timeout);
		//dbg("select ret=%d\n", ret);
		if( -1 == ret )
		{
			perror("select()");
		}else if( ret ){
			/* find which fd can be read */
			for( i=0, pentry=g_watch_data.entry; \
					i<g_watch_data.max_instance; \
					i++, pentry++)
			{
				if( (-1 != pentry->fd) &&  FD_ISSET(pentry->fd, &rfds) )
				{
					/* read the event, the find it & process */
					_process_event(pentry);
					break;
				}
			}
		}
	}

	dbg("task exit\n");
	g_watch_data.task_runflag = 2;

	return NULL;
}

static void _process_event(watch_entry_t *pentry)
{
	static char buf[1024];
	static char path_buf[256];
	int path_len;
	char *dir_name = NULL;
	static int ret = 0;

	ret = read(pentry->fd, buf, sizeof(buf));
	if( ret > 0 )
	{
		char *cur = buf;
		struct inotify_event *pie = NULL; /* see defination: use man 7 inotify */
		E_CHANGE_MODE_t change_mode = NO_CHANGE;

		while( ret > 0 )
		{
			pie = (struct inotify_event*)cur;
#if 0
			dbg("watch_fd = %d\nmask = 0x%x\ncookie = 0x%x\nlen = %d\nname = %s\n",
					pie->wd, pie->mask, pie->cookie, pie->len, pie->name);
#endif
			/* inotify_event to our event */
			if( pie->mask & IN_MOVE_SELF )
				change_mode = SELF_MOVE;
			else if( pie->mask & IN_DELETE_SELF )
				change_mode = SELF_DELETE;
			else if( pie->mask & IN_CREATE )
				change_mode = SUB_CREATE;
			else if( pie->mask & IN_DELETE )
				change_mode = SUB_DELETE;
			else if( pie->mask & IN_MOVED_FROM )
				change_mode = SUB_MOVE_FROM;
			else if( pie->mask & IN_MOVED_TO )
				change_mode = SUB_MOVE_TO;

#if 0
			/* self_move, cannot find the new name, ?
			 * just replace it's new name */
#endif
			/* prefix path */
			path_len = sizeof(path_buf)-128;
			memset(path_buf, 0, sizeof(path_buf));
			dir_name = _get_path_by_fd(pentry, pie->wd, path_buf, &path_len);
			dbg("mask=0x%0x dir_name = %s pie_name=%s<END>\n", 
					pie->mask, dir_name, pie->name);
			/* this path or filename */
			dbg("dir_name=%s pie->name=%s\n", dir_name, pie->name);
			if( dir_name ) 
				strcat(dir_name, pie->name); 

			/* call default handler */
			/* this will add or remove the fd */
			_default_handler(pentry, pie->wd, dir_name, change_mode);

			/* call user's process handler */
			if( pentry->handler )
			{
				pentry->handler(pie->wd, dir_name, change_mode);
			}

			/* for next event */
			cur += (sizeof(struct inotify_event) + pie->len);
			ret -= (sizeof(struct inotify_event) + pie->len);
		}
	}
}

static int _watch_on_directory(watch_entry_t *pentry, const char *dir_path, int recursive)
{
	dbg("in\n");
	if( !pentry->normal_entry )
	{
		pentry->normal_entry = _get_path_entry();
		if( !pentry->normal_entry )
		{
			return -1;
		}
		pentry->normal_entry->min = 0;
		pentry->normal_entry->max = PATH_ENTRY_NUM;
	}

	pentry->fd = inotify_init();
	if( -1 == pentry->fd )
		return -1;
	dbg("inotify_init success: %d\n", pentry->fd);

	if( !recursive )
	{
		int file_fd = inotify_add_watch(pentry->fd, dir_path, WATCH_EVENTS);
		if( -1 == file_fd )
		{
			close(pentry->fd);
			pentry->fd = -1;
			return -1;
		}
		_map_fd_path(pentry, file_fd, dir_path, -1);
	}else{
		return _watch_on_dir_recur(pentry, dir_path, -1);
	}

	return 0;
}

static int _watch_on_dir_recur(watch_entry_t *pentry, const char *dir_path, int parent_fd)
{
	/* cause of may recursive many levels, so the Stack_Var replace with Static_Var */
	static struct stat fstat;
	static int _watch_fd = 0;
	static int ret = 0;
	char fullpath[128];

	_watch_fd = inotify_add_watch(pentry->fd, dir_path, WATCH_EVENTS);
	if( -1 == _watch_fd )
	{
		return -1;
	}
	_map_fd_path(pentry, _watch_fd, dir_path, parent_fd);
	printf("\tadd:%d %d %s\n", pentry->fd, _watch_fd, dir_path);
	parent_fd = _watch_fd;

	if( -1 == lstat(dir_path, &fstat) )
	{
		dbg("\tget %s stat error.\n", dir_path);
		return -1;
	}
	if( S_ISDIR(fstat.st_mode) )
	{
		/* the two cannot define with static, must be Stack_Var */
		DIR *dir;
		struct dirent *dir_ent;
		dir = opendir(dir_path);
		while( NULL != (dir_ent = readdir(dir)) )
		{
			/* skip . && .. */
			if( (0 == strcmp(dir_ent->d_name, ".")) \
				|| (0 == strcmp(dir_ent->d_name, "..")) )
				continue;

			/* is directory then recursive */
			if( str_end_with(dir_path, '/') )
				ret = sprintf(fullpath, "%s%s", dir_path, dir_ent->d_name);
			else
				ret = sprintf(fullpath, "%s/%s", dir_path, dir_ent->d_name);
			fullpath[ret] = 0;
#if 0
			printf("\nd_name=%s\ndir_path=%s\nfullpath: %s\n",
					dir_ent->d_name, dir_path, fullpath);
#endif
			if( -1 == lstat(fullpath, &fstat) )
				continue;
			if( S_ISDIR(fstat.st_mode) )
			{
				dbg("%s is dir\n", dir_ent->d_name);
				_watch_on_dir_recur(pentry, fullpath, parent_fd);
			}
		}

		/* 2013-06-02 14:25:49 zhaocq */
		if( dir )
			closedir(dir);
	}

	return 0;
}

static path_entry_t *_get_path_entry(void)
{
	path_entry_t *tmp = malloc(PATH_ENTRY_SIZE);
	if( NULL == tmp )
	{
		dbg("memory out\n");
		return NULL;
	}else{
		dbg("new memory 0x%0x\n", PATH_ENTRY_SIZE);
	}

	tmp->next = NULL;
	tmp->min = 0;
	tmp->max = 0;
	tmp->end = ((char *)tmp+PATH_ENTRY_SIZE);
	tmp->start = (char *)tmp->path_hash;

	dbg("ok\n");
	return tmp;
}

static int _map_fd_path(watch_entry_t *pentry, int file_fd, 
			const char *fullpath, int parent_fd)
{
	int len, index;
	path_entry_t *ppath = pentry->normal_entry;

	dbg("in file_fd=%d parent_fd=%d fullpath=%s\n", file_fd, parent_fd, fullpath);
	len = strlen(fullpath) + 1;
	/* find the valid paht_entry */
	do{
		/* didnot in this path_entry, try next */
		if( (file_fd >= ppath->min) && (file_fd <= ppath->max)
				&& (ppath->start + len < ppath->end ) )
		{
			/* can use */
			break;
		}
		/* this path_entry no memory, try next */
		ppath = ppath->next;
	}while(ppath != NULL);

	if( NULL == ppath )
	{
		/* get new path_entry */
		ppath = _get_path_entry();
		if( NULL == ppath )
		{
			/* no memory */
			return -1;
		}

		/* insert to list */
		ppath->next = pentry->normal_entry;
		pentry->normal_entry = ppath;
		ppath->min = (file_fd/PATH_ENTRY_NUM) * PATH_ENTRY_NUM;
		ppath->max = ppath->min + PATH_ENTRY_NUM;
		dbg("min=%d max = %d\n", ppath->min, ppath->max);
	}
	dbg("find path_entry\n");

	/* set the data */
	index = file_fd - ppath->min;
	ppath->path_hash[index].fd = file_fd;
	ppath->path_hash[index].prefix_fd = parent_fd;
	dbg("index=%d max=%d min=%d\n", index, ppath->max, ppath->min);
	if(-1 == parent_fd )
	{
		/* if not parrent, this fullpath is it's path */
		int len = strlen(fullpath);
		unsigned int hash = hash_gen(fullpath,len);
		
		dbg("find this_path: %s hash=%u\n", fullpath, hash);
		if( (len > 2) && str_end_with(fullpath, '/') )
			len -= 1;
		ppath->end -= (len+1);
		strncpy(ppath->end, fullpath, len);
		ppath->end[len] = 0;
		if( NULL == hash_insert(&pentry->hash_table, hash, ppath->end) )
		{
			dbg("watch: map fd path failed: hash:%u path:%s\n", 
					hash, ppath->end);
			return -1;
		}

		ppath->path_hash[index].hash = hash;
	}else{
		/* split this_data & prefix_data , get them's hash_data */
		char *this_path;
		unsigned int this_hash;
		int this_len = 0;

		len = strlen(fullpath);
		this_path = strrchr(fullpath, '/');
		if( this_path )
		{
			/* the fullpath is start with "/", and no other level */
			this_path++;
			/* end with '/' */
			if( ! *this_path )
			{
				this_path = (char *)fullpath;
			}
		}

		if( NULL == this_path )
		{
			/* fullpath is no prefix path */
			this_path = (char *)fullpath;
		}

		/* save the this path to the memory */
		this_len = strlen(this_path) + 1;
		ppath->end -= this_len;
		strncpy(ppath->end, this_path, this_len);
		if( (this_len > 2) && str_end_with(this_path, '/') )
		{
			ppath->end[this_len-2] = 0;
		}

		this_hash = hash_gen(this_path, this_len-1);
		dbg("find this_path: %s hash=%u\n", this_path, this_hash);
		if( NULL == hash_insert(&pentry->hash_table, this_hash, ppath->end) )
		{
			dbg("watch: map fd path failed: hash:%u path:%s\n", 
					this_hash, ppath->end);
			return -1;
		}

		ppath->path_hash[index].hash = this_hash;
	}

#if 0
	/* incarse max */
	if( file_fd > ppath->max )
	{
		//ppath->max = file_fd;
	}
#endif

	/* modify start point */
	ppath->start += sizeof(path_hash_t);
	return 0;
}

static unsigned int _get_hash_by_fd(watch_entry_t *pentry, int file_fd)
{
	int index;
	path_entry_t *ppath = pentry->normal_entry;

	/* find the valid paht_entry */
	do{
		/* didnot in this path_entry, try next */
		if( file_fd > ppath->max && file_fd < ppath->min )
			break;

		ppath = ppath->next;
	}while(ppath != NULL);

	if( NULL == ppath )
	{
		/* file_fd not in the entry */
		return 0;
	}
	index = file_fd - ppath->min;

	return ppath->path_hash[index].hash;
}

static char *_get_path_by_fd(watch_entry_t *pentry, int file_fd, 
			char *path_buf, int* path_len)
{
	int index, len;
	path_entry_t *ppath = pentry->normal_entry;
	char **pstr = NULL;

	dbg("in file_fd = %d\n", file_fd);
	/* find the valid paht_entry */
	do{
		/* didnot in this path_entry, try next */
		if( (file_fd <= ppath->max) && (file_fd > ppath->min) )
			break;

		ppath = ppath->next;
	}while(ppath != NULL);

	if( NULL == ppath )
	{
		/* file_fd not in the entry */
		return NULL;
	}

	index = file_fd - ppath->min;
	dbg("find path_entry hash=%u\n", ppath->path_hash[index].hash);
	/* return the path */
	pstr = (char **)hash_find(&pentry->hash_table, ppath->path_hash[index].hash);
	if( !pstr )
	{
		return NULL;
	}

	len = strlen(*pstr) + 1;
	dbg("=====path name : %s=====path_len=%d len=%d\n", *pstr, *path_len, len);
	if( *path_len >= len )
	{
		/* replace the 0(terminal char) with '/' */
		path_buf[*path_len-1] = '/';
		memcpy(path_buf+*path_len-len, *pstr, len-1);
		*path_len -= len;
		if( -1 != ppath->path_hash[index].prefix_fd )
		{
			if( NULL == _get_path_by_fd ( pentry, 
							ppath->path_hash[index].prefix_fd, 
							path_buf, 
							path_len )
					)
				return path_buf + *path_len;
		}
	}

	dbg("path return:%s path_len=%d\n", 
			path_buf+*path_len, *path_len );
	
	return path_buf+*path_len;
}

static void _default_handler(watch_entry_t *pentry, int file_fd, 
		const char *dir_name, E_CHANGE_MODE_t change_mode)
{
	static char *move_from_str;
	static char *move_to_str;
	static char *last_to;
	static char *last_from;
	static int same_level_move = 0;
#if 0
	SUB_MOVE_FROM,/* in watched directory, something has be moved from */
	SUB_MOVE_TO,/* in watched directory, something has be moved to */
	SUB_DELETE, /* file or directory which in watched directory has be deleted */
	SUB_CREATE,	/* file or directory which in watched directoyr has be added */
	SELF_MOVE,	/* the watched directroy itself be moved */
	SELF_DELETE,/* the watched directory itself be deleted */
#endif
	dbg("file_fd=%d dir_name=%s EVENT=%s\n", 
			file_fd, dir_name, change_mode_2_str(change_mode));

	/* process delete */
	if( SELF_DELETE == change_mode || SUB_DELETE == change_mode )
		return;

#if 1
	/* sometimes cannot process, because the event didnot have new name 
	 * when it's parent is watched, then can process
	 * */
	/* process selfmove */
	if( SELF_MOVE == change_mode )
	{
		/* 1.check if moved to the same directory, just rename it in table */
		if( same_level_move )
		{
			/* in same directory, just rename */
			unsigned int *phash; 
			int index, len;
			path_entry_t *ppath = pentry->normal_entry;

#if 0
			last_from = strrchr(move_from_str, '/'); 
			last_to = strrchr(dir_name, '/');
#endif
			last_to ++;/* skip '/' */
			len = strlen(last_to);

			dbg("same level move\n");
			/* find path hash */
			do{
				/* didnot in this path_entry, try next */
				if( file_fd <= ppath->max && file_fd > ppath->min )
					break;

				dbg("ppath->min = %d max=%d\n", ppath->min, ppath->max);
				ppath = ppath->next;
			}while(ppath != NULL);
			if( NULL == ppath )
			{
				/* file_fd not in the entry */
				dbg("find old path fail. file_fd=%d\n", file_fd);
				goto SELF_MOVE_OUT;
			}
			index = file_fd - ppath->min;
			phash = &ppath->path_hash[index].hash;
			dbg("find old path. old hash=%u\n", *phash);

			/* find where to save new name */
			ppath = pentry->normal_entry;
			do{
				if( ppath->end - ppath->start > len + 1 )
				{
					break;
				}
				ppath = ppath->next;
			}while(ppath != NULL);
			if( NULL == ppath )
			{
				dbg("find where to save\n");
				ppath = _get_path_entry();
				if( NULL == ppath )
					goto SELF_MOVE_OUT;
				ppath->next = pentry->normal_entry;
				pentry->normal_entry= ppath;
				ppath->min = pentry->normal_entry->max;
				ppath->max = ppath->min + PATH_ENTRY_NUM;
			}
			dbg("find new path\n");

			/* save new name */
			ppath->end -= len+1;
			strcpy(ppath->end, last_to);

			/* member in hash, replace with new hash */
			dbg("len:%d move_from_str:%s move_to_str:%s\n", len, move_from_str, move_to_str);
			*phash = hash_gen(last_to, len);
			dbg("new hash=%u\n", *phash);
			hash_insert(&pentry->hash_table, *phash, ppath->end);
			if( move_from_str )
			{
				free(move_from_str);
				move_from_str = NULL;
			}
SELF_MOVE_OUT:
			same_level_move = 0;
			if( move_to_str )
			{
				free(move_to_str);
				move_to_str = NULL;
			}
			if( move_from_str )
			{
				free(move_from_str);
				move_from_str = NULL;
			}
			return;
		}
		/* 2.if moved to another directory, need change it's,
		 * the parent will do it, so just return
		 * */
		return;
	}
#endif

	if( SUB_MOVE_FROM == change_mode )
	{
		if( move_from_str )
		{
			free(move_from_str);
			move_from_str = NULL;
		}
		if( dir_name )
			move_from_str = strdup(dir_name);
		return;
	}

	/* check if move to the same dir
	 * if in same the watch can work continuly, just replace the name
	 * if didnot in same directory, then it same as SUB_CREATE
	 * */
	if( SUB_MOVE_TO == change_mode )
	{
		if( !move_from_str )
		{
			return;
		}

		if( move_to_str )
		{
			free(move_to_str);
			move_to_str = NULL;
		}
		if( dir_name )
			move_to_str = strdup(dir_name);

		dbg("%d: move_to_str=%s move_from_str=%s\n", __LINE__, move_to_str, move_from_str);
		last_from = strrchr(move_from_str, '/'); 
		last_to = strrchr(move_to_str, '/');

		dbg("move_from_str=%s move_to_str=%s\n", move_from_str, move_to_str);
		if( last_to && last_from )
		{
			dbg("last_to=%s last_from=%s\n", last_to, last_from);
			if( (last_to - move_to_str) != (last_from - move_from_str) )
				goto MOVE_TO_CREATE;
			if( strncmp(move_from_str, move_to_str, last_to - move_to_str) )
				goto MOVE_TO_CREATE;

			same_level_move = 1;
			return;
		}/* end of  if( !(last_to && last_from)) */
MOVE_TO_CREATE:
		change_mode = SUB_CREATE;
	}

	/* process add */
	if( SUB_CREATE == change_mode )
	{
		struct stat fstat;
		dbg("process add: dir_name=%s\n", dir_name);
		if( -1 == lstat(dir_name, &fstat) )
		{
			return;
		}

		/* process dir, if not dir, just return */
		if ( S_ISDIR(fstat.st_mode) )
		{
			/* process add */
			_watch_on_dir_recur(pentry, dir_name, file_fd);
		}
		return;
	}
}

