/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  test bitset
 *
 *        Version:  1.0
 *        Created:  2013年04月02日 14时01分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */

#include <iostream>
#include "bitset.h"

using std::cout;
using std::endl;

int main(int argc, char **argv)
{
	BitSet *pbs = new BitSet(50);
	if( pbs == NULL )
	{
		cout << "error : memory out." << endl;
		return -1;
	}

	//test print
	cout << "pbs size : " << pbs->size() <<endl;
	cout << "pbs is : " << *pbs << endl;

	//test set
	pbs->set(1);
	pbs->set(2);
	pbs->set(31);
	pbs->set(32);
	pbs->set(33);
	pbs->set(50);
	cout << "pbs is : " << *pbs << endl;

	//test reset
	pbs->set(0);
	pbs->reset(2);
	pbs->reset(32);
	cout << "pbs is : " << *pbs << endl;

	//test []
	cout << "pbs[32] " << (*pbs)[32] << endl;
	cout << "pbs[33] " << (*pbs)[33] << endl;

	//test op-all:flip,set, reset
	pbs->flip();
	cout << "after flip: \n" << "pbs is : " << *pbs << endl;
	pbs->set();
	cout << "after set: \n" << "pbs is : " << *pbs << endl;
	pbs->reset();
	cout << "after reset: \n" << "pbs is : " << *pbs << endl;

	delete pbs;
	return 0;
}

