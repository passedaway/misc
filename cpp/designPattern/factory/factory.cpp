/*
 * =====================================================================================
 *
 *       Filename:  factory.cpp
 *
 *    Description:  factory
 *
 *        Version:  1.0
 *        Created:  10/25/2013 09:10:06 PM
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

Factory::Factory()
{
	cout<<"Factory"<<endl;
}

Factory::~Factory()
{
	cout<<"~Factory"<<endl;
}

Product* Factory::CreateProduct()
{
	cout<<"Factory::CreateProduct"<<endl;
	return (Product*)0;
}

AFactory::AFactory()
{
	cout<<"AFactory"<<endl;
}

AFactory::~AFactory()
{
	cout<<"~AFactory"<<endl;
}

Product* AFactory::CreateProduct()
{
	cout<<"AFactory::CreateProduct"<<endl;
	return new ProductA();
}

