/*
 * =====================================================================================
 *
 *       Filename:  product.h
 *
 *    Description:  product
 *
 *        Version:  1.0
 *        Created:  10/25/2013 08:54:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *          Email:  echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */

#ifndef _PRODUCT_H_
#define _PRODUCT_H_

class Product{
	public:
		virtual ~Product() = 0;

	protected:
		Product();
	
	private:
};

class ProductA : public Product{
	public:
		~ProductA();
		ProductA();

	protected:

	private:

};

#endif

