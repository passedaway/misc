/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  test log 
 *
 *        Version:  1.0
 *        Created:  06/29/2013 01:47:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *			Email:	echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */

#include "log.h"

#include <iostream>

using std::cout;
using std::endl;
int main(int argc, char **argv)
{
	Log *log = new Log();
	log->print("abcd\b\b %s", "shit!");

	cout<<"argc="<<argc<<endl;
	cout<<"log:string is ["<<log->to_str()<<"]"<<endl;


	return 0;
}

