/******************************************************************************/
/*    Filename: cclientsocket.h                                                                        */
/*    Description: client clientsocket, externed form clientsocet,multithread   */
/*                                                                                                                  */
/*    Author:zhaocq (changqing.1230@163.com)  2010/11/30                        */
/******************************************************************************/
#ifndef CClientSocket_H
#define CClientSocket_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HOST_THREAD
#define HOST_THREAD	1
#endif
#ifndef NET_THREAD
#define NET_THREAD	2
#endif

void c_client_socket_init(char *addr, int port);
void c_client_socket_exit();

void c_start_thread();
void c_join(int opcode);

#ifdef __cplusplus
}
#endif

#endif
