/*
 * =====================================================================================
 *
 *       Filename:  bitset.cpp
 *
 *    Description:  bitset
 *
 *        Version:  1.0
 *        Created:  2013年04月02日 14时17分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */
#include "bitset.h"

ostream& operator<<(ostream &os, BitSet &bs)
{
	for( int i = 0; i < bs._size; i++)
	{
		if ( (i%32) == 0 )
			os << ' ';
		os << bs.test(i);
	}

	return os;
}

void BitSet::set(void)
{
	for(int i = 0, n = _size/32 + (_size%8?1:0); i< n; i++)
		_pi[i] = ~0;
}

void BitSet::reset(void)
{
	for(int i = 0, n = _size/32 + (_size%8?1:0); i< n; i++)
		_pi[i] = 0;
}

void BitSet::flip(void)
{
	for(int i = 0, n = _size/32 + (_size%8?1:0); i< n; i++)
		_pi[i] = ~_pi[i];
}

