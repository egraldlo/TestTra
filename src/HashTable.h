/*
 * HashTable.h
 *
 *  Created on: 2013-8-29
 *      Author: casa
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stdlib.h>
#include <string.h>

#include <vector>
using namespace std;

#define CACHE_LINE 64

//如果不和cacheline对齐的话性能损失有多大？
inline unsigned get_cacheline_aligned_space(unsigned bucket_size){
	return ((bucket_size+2*sizeof(void*)-1)/CACHE_LINE+1)*CACHE_LINE;
}

class HashTable {
public:
	class HashTableIterator{
		friend class HashTable;
	public:
		HashTableIterator(unsigned bucket_size,unsigned tuple_size)
		:bucket_size_it(bucket_size),tuple_size_it(tuple_size),cur_it(0),
		free_it(0),next_it(0){
		};
		virtual ~HashTableIterator(){};

		//这个函数读取下一个tuple，返回下一个tuple的位置
		inline void *readnext(){
			void *ret;
			//some ugly here
			//TODO: do something strong
			if(cur_it<free_it){
				ret=cur_it;
				cur_it=(char *)cur_it+tuple_size_it;
				return ret;
			}
			else if(next_it!=0){
				//在这个链中还有bucket没有被遍历的时候，切换到下一个bucket
				ret=next_it;
				cur_it=(char *)next_it+tuple_size_it;
				//这个指针指向一个地址，转化为指向指针的指针
				free_it=*(void **)((char *)next_it+bucket_size_it);
				next_it=*(void **)((char *)next_it+bucket_size_it+sizeof(void *));
				return ret< free_it? free_it: 0;
			}
			else{
				return 0;
			}
		}
	private:
		unsigned bucket_size_it;
		unsigned tuple_size_it;

		void *cur_it;
		void *free_it;
		void *next_it;
		void *bucketlink_start_it;
	};

	HashTable(unsigned n_buckets,unsigned bucket_size,unsigned tuple_size);
	virtual ~HashTable();

	void *allocate(unsigned offset);
	bool placeIterator(HashTableIterator &it,unsigned int offset){
		if(offset>=n_buckets)
			return false;

		//这个地址是key的hash值所对应的hash链中的首地址
		void *start=repo_start+offset*get_cacheline_aligned_space(bucket_size);
		it.cur_it=start;
		//取到的是free的地址
		it.free_it=*(void **)((char *)start+bucket_size);
		it.next_it=*(void **)((char *)start+bucket_size+sizeof(void *));
		it.tuple_size_it=tuple_size;
		it.bucketlink_start_it=start;
		it.bucket_size_it=bucket_size;
		return true;
	}

	HashTable::HashTableIterator createIterator(){
		return HashTable::HashTableIterator(bucket_size,tuple_size);
	}

private:
	//hash表有几个bucket
	unsigned n_buckets;
	//一个bucket多大
	unsigned bucket_size;
	//一个tuple大小
	unsigned tuple_size;
	//指向bucket指针的起始地址
	void **buckets_start;
	//一个内存仓库的大小，每个bucket从这个内存仓库中取内存，如果没有内存了，就再建一个内存仓库
	unsigned repo_size;

	char *repo_start;
	//当前内存仓库分配的内存大小
	unsigned cur_repo_dis;
	//内存仓库的list
	std::vector<char *> repo_list;
};

#endif /* HASHTABLE_H_ */
