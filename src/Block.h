/*
 * Block.h
 *
 *  Created on: 2013-8-27
 *      Author: casa
 */

#ifndef BLOCK_H_
#define BLOCK_H_

class Block {
public:
	class BlockIterator{
		explicit BlockIterator(Block *block){

		}
	};

	Block();
	virtual ~Block();

	virtual void* allocateTuple(unsigned bytes)=0;

	friend class BlockIterator;
	BlockIterator *createIterator(){
		//因为在Block的成员变量中，直接用schema，是直接可以起到iterator的作用的
		//但是这么写的好处是：
		//   1,可以有多个读iterator独立的遍历这个block
		//   2,只能有一个写去调用Block中的成员函数去写
		//这样能够满足多读一写的封装形式
		return new BlockIterator(this);
	}

};

class BlockFix{
public:
	BlockFix();
	virtual ~Block();
private:
	unsigned block_size;
};

#endif /* BLOCK_H_ */
