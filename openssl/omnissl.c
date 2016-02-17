/*
 * =====================================================================================
 *
 *       Filename:  omnissl.c
 *
 *    Description:  omnific openssl integration
 *
 *        Version:  1.0
 *        Created:  04/15/2014 07:05:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *          Email:  echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */
#include "openssl/crypto.h"
#include "openssl/x509.h"
#include "openssl/pem.h"
#include "openssl/ssl.h"
#include "openssl/err.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unstid.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct omni_ssl_socket_s {
	int sock_fd;

	int type;

	SSL_CTX *ctx;
	SSL *ssl;
}

omni_ssl_socket_t socket_to_ssl(void *user_socket)
{
	omni_ssl_socket_t pssl_socket = malloc(sizeof(*pssl_socket));
	if( pssl_socket )
	{
		pssl_socket->sock_fd = (int)user_socket;
		pssl_socket->type = 0;
		pssl_socket->ctx = NULL;
		pssl_socket->ssl = NULL;
	}
	return pssl_socket;
}

void *sslsocket_to_normal(omni_ssl_socket_t psslsocket)
{
	return pssl_socket->sock_fd;
}

int omni_ssl_setup(omni_ssl_socket_t socket, int socktype, const char *key_file, const char *cert_file)
{
	SSL_METHOD *meth;
	int err = -1;
	//check param
	if( (socktype == TYPE_SERVER_SSL) && (key_file == NULL || cert_file == NULL ) )
		return -1;

	socket->type = socktype;
	//not use ssl, just return
	if( socktype == TYPE_SERVER_NORMAL || socktype == TYPE_CLIENT_NORMAL )
		return 0;

	//use ssl
	//SSL init
	SSL_load_error_strings();
	SSLeay_add_ssl_algorithms();
	if( socktype == TYPE_SERVER_SSL )
		meth = (SSL_METHOD*)SSLv23_server_method();
	else if (socktype == TYPE_CLIENT_SSL )
		meth = (SSL_METHOD *)SSLv23_client_method();
	else
		goto err_out;
	socket->ctx = SSL_CTX_new(meth);
	if( socket->ctx == NULL )
		goto err_out;
	
	if( cert_file )
	{
		//load cert file
		err = SSL_CTX_use_certificate_file(socket->ctx, cert_file, SSL_FILETYPE_PEM);
		if( err <= 0 )
			goto err_out;

	}
	if( key_file )
	{
		//load key file
		err = SSL_CTX_use_PrivateKey_file(socket->ctx, key_file, SSL_FILETYPE_PEM);
		if( err <= 0 )
			goto err_out;

		err = SSL_CTX_check_private_key(ctx);
		if( err <= 0 )
			goto err_out;
	}


	return 0;

err_out:
	if( socket->ctx )
	{
		SSL_CTX_free(ctx);
	}

	return err;
}

void omni_ssl_exit(omni_ssl_socket_s omnissl)
{
	if( omnissl )
	{
		if( omnissl->ssl )
			SSL_free(omnissl->ssl);

		if( omnissl->ctx )
			SSL_CTX_free(ctx);

		ERR_free_strings();
	}
}



