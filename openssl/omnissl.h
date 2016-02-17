/*
 * =====================================================================================
 *
 *       Filename:  omnissl.h
 *
 *    Description:  omnific encapsulate openssl
 *
 *        Version:  1.0
 *        Created:  04/15/2014 05:56:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *          Email:  echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */
#ifndef _OMNI_SSL_H_
#define _OMNI_SSL_H_

typedef omni_ssl_socket_s *omni_ssl_socket_t;

typedef enum {
	TYPE_NORMAL = 0,
	TYPE_SERVER_SSL,
	TYPE_SERVER_NORMAL,
	TYPE_CLIENT_SSL,
	TYPE_CLIENT_NORMAL,
}SOCKET_TYPE_t;

omni_ssl_socket_t socket_to_ssl(void *user_socket);
void *sslsocket_to_normal(omni_ssl_socket_t);

int omni_ssl_setup(omni_ssl_socket_t socket, int sock_type, const char *key_file, const char *cert_file);
void omni_ssl_exit(omni_ssl_socket_t omnissl);

omni_ssl_socket_t omni_ssl_socket_create(int af, int type, int protocol);
void omni_ssl_socket_close(omni_ssl_socket_t omni_socket);

int omni_ssl_socket_connect(omni_ssl_socket_t omni_socket, uint32_t ip, uint16_t port);
omni_ssl_socket_t omni_ssl_socket_accept(omni_ssl_socket_t omni_socket, uint32_t *ip, uint16_t *port);

int omni_ssl_socket_bind(omni_ssl_socket_t omni_socket, int max);
int omni_ssl_socket_listen(omni_ssl_socket_t omni_socket);
int omni_ssl_socket_read(omni_ssl_socket_t omni_socket, void *buf, int size);
int omni_ssl_socket_write(omni_ssl_socket_t omni_socket, void *buf, int size);

const char *omni_ssl_perror(int err_code);

/*
 * other operations use like this, such as setsockopt:
 *
 * int socket = (int)sslsocket_to_normal(ssl_socket);
 * setsockopt(socket, ...);
 *
 */

#endif

