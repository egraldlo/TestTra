/*
 * BitMap.h
 *
 *  Created on: 2013-8-28
 *      Author: casa
 */

#ifndef BITMAP_H_
#define BITMAP_H_

#include <cstring>
using namespace std;

class BitMap {
public:
	BitMap(){
		b_bitmap=0;
		b_size=0;
	};

	BitMap(char *_bitmap,int _size){
		b_bitmap=_bitmap;
		b_size=_size;
	};

	BitMap(const BitMap& bm){
		b_bitmap=new char[bm.b_size];
		for(int i=0;i<bm.b_size;i++){
			b_bitmap[i]=bm.b_bitmap[i];
		}
		b_size=bm.b_size;
	}

	virtual ~BitMap(){};

	inline int BitMap_init(int size){
		b_size=size/8+1;
		b_bitmap=new char[b_size];
		if(b_bitmap==NULL)
			return 0;
		memset(b_bitmap,0x0,b_size);
		return 1;
	}

	inline int BitMap_set(int index){
		int byte_position=(index)>>3;
		int byte_offset=(index)&7;
		unsigned char x=(0x1<<byte_offset);
		if(byte_position>b_size)
			return 0;
		b_bitmap[byte_position]|=x;
		return 0;
	}

	inline int BitMap_get(int index){
		int byte_position=(index)>>3;
		int byte_offset=(index)&7;
		unsigned char x=(0x1<<byte_offset);
		if(byte_position>=b_size)
			return -1;
		unsigned char re;
		re=b_bitmap[byte_position]&x;
		return re>0?1:0;
	}

	inline BitMap * BitMap_merge(BitMap *bm){
		BitMap *re_bm=new BitMap();
		re_bm->b_bitmap=new char[this->b_size];
		for(int i=0;i<this->b_size;i++){
			re_bm->b_bitmap[i]=bm->b_bitmap[i]&this->b_bitmap[i];
		}
		re_bm->b_size=this->b_size;
		return re_bm;
	}

	inline int BitMap_free(){
		delete [] b_bitmap;
		return 0;
	}

private:
	char *b_bitmap;
	int b_size;
};


#endif /* BITMAP_H_ */
