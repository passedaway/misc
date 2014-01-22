/*
 * =====================================================================================
 *
 *       Filename:  product.cpp
 *
 *    Description:  product.cpp
 *
 *        Version:  1.0
 *        Created:  10/25/2013 08:58:46 PM
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

#include <iostream>
using std::cout;
using std::endl;

Product::Product()
{
	cout<<"Product"<<endl;
}

Product::~Product()
{
	cout<<"~Product"<<endl;
}

ProductA::ProductA()
{
	cout<<"ProductA"<<endl;
}

ProductA::~ProductA()
{
	cout<<"~ProductA"<<endl;
}
