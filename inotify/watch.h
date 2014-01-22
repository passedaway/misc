/*
 * =====================================================================================
 *
 *       Filename:  watch.h
 *
 *    Description:  watch directory's info
 *
 *        Version:  1.0
 *        Created:  05/26/2013 12:11:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 * 			Email:	echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *        Release:	2013-06-02 14:31:10 zhaocq V2
 *        	1.fix bug: > 1021 , then segfault error
 *
 * =====================================================================================
 */
#ifndef _WATCH_H_
#define _WATCH_H_
/* module description
 * function:
 * 		the module is watch the change of content in the special directoy which
 * 	be watched on.
 * 	then , user can register the handler of the change, to process the change.
 * 	at last, user should call watch_off, to destory all things
 *
 * 	demo is:
 * 	1. watch_init(16);
 * 	2. int watch_fd = watch_on("/opt", WATCH_ALL);
 * 	3. watch_install_handler(watch_fd, you_handler);
 * 	4. do your things
 * 	5. when exit, should call:
 * 		watch_off(watch_fd);
 * 		watch_exit();
 *
 * see test.c 
 * */

/* module init
 * should call this first, then the other api can used
 * param:
 * 	max_instance:	can watch_on directory's num(recomment values is 32)
 *
 * return:
 * 	fail : -1
 * 	success: 0
 * */
int watch_init(int max_instance);
/* module exit
 * cleanup the data when allocated in watch_init
 * params:
 * 	sync:if sync = 1, the function will wait interal task exit, then return
 * 	if sync = 0, return immediately
 */
void watch_exit(int sync);

typedef enum{
	WATCH_THIS = 0, /* just watch this directory's change */
	WATCH_ALL = 1,	/* watch the directory's all file & directory (recursive) */

	E_WATCH_MODE_MAX,
}E_WATCH_MODE_t;
/* desp: watch directory init
 * param:
 * 		dir_path:[in], be watched directory's full path
 * 		mode:[in], the mode is E_WATCH_MODE_t, see it's define
 *
 * return:
 * 		fail: -1
 * 		success: return the watch_fd
 * */
int watch_on(const char *dir_path, E_WATCH_MODE_t mode);

/* desp: watch directory exit/cleanup
 * param:
 * 		watch_fd:[in], be created witch watch_on()
 *
 * return:
 * 		fail: -1	error occured when cleanup 
 * 		success: 0
 * */
int watch_off(int watch_fd);

/* sometimes, need just add one dir_path to the opened watch_fd
 * like this:
 * 	watch_fd = watch_on(....);
 * 	file_fd = watch_add(watch_fd, dir_path, WATCH_ALL);
 * 	..
 *
 * 	param:
 * 		watch_fd:[in], return by watch_on(..)
 * 		dir_path:[in], new added path(dir or file)
 * 		mode:[in], see E_WATCH_MODE_t define
 *
 * 	return:
 * 		fail: -1
 * 		success: >=0, if( E_WATCH_MODE_t == WATCH_THIS ) return the watched file_fd
 * 			else return 0
 * */
int watch_add(int watch_fd, const char *dir_path, E_WATCH_MODE_t mode);

/* when the path name is be changed, should remove the file_fd
 * and user determine to add this file or not
 * param:
 * 		watch_fd:[in], return by watch_on
 * 		file_fd:[in], return by watch_add(..., mode = WATCH_THIS), 
 * 				or the watch handler's first param( see the defination of watch_handler_t )
 * return:
 * 		fail: -1
 * 		success: 0
 * */
int watch_rm(int watch_fd, int file_fd);

typedef enum{
	NO_CHANGE = 0,
	SUB_MOVE_FROM,/* in watched directory, something has be moved from */
	SUB_MOVE_TO,/* in watched directory, something has be moved to */
	SUB_DELETE, /* file or directory which in watched directory has be deleted */
	SUB_CREATE,	/* file or directory which in watched directoyr has be added */
	SELF_MOVE,	/* the watched directroy itself be moved */
	SELF_DELETE,/* the watched directory itself be deleted */
	E_CHANGE_MODE_MAX,
}E_CHANGE_MODE_t;
/* just for print */
static inline const char *change_mode_2_str(E_CHANGE_MODE_t change_mode)
{
	static const char *_str[] = {
		"NO_CHANGE",
		"SUB_MOVE_FROM", 
		"SUB_MOVE_TO", 
		"SUB_DELETE",
		"SUB_CREATE",
		"SELF_MOVE",
		"SELF_DELETE",
		"UNKNOWN"
	};

	if( change_mode > E_CHANGE_MODE_MAX )
		return _str[E_CHANGE_MODE_MAX];
	return _str[change_mode];
}

typedef int (*watch_handler_t)(int file_fd, const char *change_path, E_WATCH_MODE_t change_mode);

/* install the handler of this watch_fd
 * when data is changed the watch_handler will be called
 * param:
 * 		watch_fd:[in], be created witch watch_on()
 * 		watch_handler: [in], user define is process function
 *
 * 	return:
 * 		fail: -1	error occured when install handler
 * 		success: 0
 * */
int watch_install_handler(int watch_fd, watch_handler_t watch_handler);
/* remove the handler on watch_fd
 * param:
 * 		watch_fd:[in], be created witch watch_on()
 *
 * 	return:
 * 		fail: -1	error occured when install handler
 * 		success: 0
 * */
int watch_remove_handler(int watch_fd);

#endif

