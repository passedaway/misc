/*
 * =====================================================================================
 *
 *       Filename:  factory.h
 *
 *    Description:  factory
 *
 *        Version:  1.0
 *        Created:  10/25/2013 09:05:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *          Email:  echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */

#ifndef _FACTORY_H_
#define _FACTORY_H_

class Product;

class Factory
{
	public:
		virtual ~Factory() = 0;
		virtual Product *CreateProduct() = 0;

	protected:
		Factory();

	private:

};

class AFactory : public Factory
{
	public:
		~AFactory();
		AFactory();

		Product *CreateProduct();

	protected:

	private:
};

#endif

