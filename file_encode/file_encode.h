/*
 * =====================================================================================
 *
 *       Filename:  file_encode.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/16/2013 11:45:17 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Lihong.wang ()
 *          Email:  xiaowang73@163.com
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */

#ifndef __FILE_ENCODE_H__
#define __FILE_ENCODE_H__

#include <stdio.h>

#define private static
#ifndef protected
#define protected
#endif
#define public

protected int file_encoding(const unsigned char *buf, size_t nbytes, char **ubuf, size_t *ulen, const char **code, const char **type);

#endif
