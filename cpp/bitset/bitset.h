/*
 * =====================================================================================
 *
 *       Filename:  bitset.h
 *
 *    Description:  bitset
 *
 *        Version:  1.0
 *        Created:  2013年04月02日 13时33分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing ,changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */
#ifndef _BIT_SET_H_
#define _BIT_SET_H_

#include <iostream>

using std::ostream;

class BitSet{
		friend ostream& operator<<(ostream &os, BitSet &bs);

	public:
		BitSet(int size) 
		{ 
			int n = size / (sizeof(int) * 8) + ((size%8)?1:0); 
			_pi = new int[n];
			_size = size;
		}

		~BitSet()
		{ 
			if( _pi ) 
				delete []_pi;
		}

		inline bool test(int pos){
			if( _checkIndex(pos) )
				return _pi[_pos1(pos)] & (1<<_pos2(pos))?true:false;

			return false;
		}

		inline void set(int pos){
			if( _checkIndex(pos) )
				_pi[_pos1(pos)] |= (1<<_pos2(pos));
		}

		inline void reset(int pos){
			if( _checkIndex(pos) )
				_pi[_pos1(pos)] &= ~(1<<_pos2(pos));
		}

		inline void flip(int pos)
		{
			if( !_checkIndex(pos) )
				return;
			test(pos) ? reset(pos):set(pos);
		}

		inline int size(){
			return _size;
		}

		inline int operator[](int elem){ return test(elem); }

		void set(void);
		void reset(void);
		void flip(void);

	private:
		int *_pi;
		int _size;
		bool _checkIndex(int pos){
			return (pos>=0) && (pos<_size);
		}
		int _pos1(int pos) { return pos/32; }
		int _pos2(int pos) { return pos%32; }
};
#endif

