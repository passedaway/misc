/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  test factory
 *
 *        Version:  1.0
 *        Created:  10/25/2013 09:19:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *          Email:  echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */

#include "product.h"
#include "factory.h"

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char **argv)
{
	Factory *fac = new AFactory;

	Product *pd = fac->CreateProduct();


	cout<<"====create over"<<endl<<endl;
	delete pd;

	delete fac;

	return 0;
}

