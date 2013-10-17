//============================================================================
// Name        : training.cpp
// Author      : zhanglei
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/assume_abstract.hpp>

#include <stdio.h>
#include "producer_consumer.h"
#include "test_theron.h"
#include "test_tree.h"
#include "test_daemon.h"
#include "process_fork.h"
#include "exception.h"
#include "effect_cpp.h"
#include "gen_data.h"
#include "boost_asio.h"
#include "SChild1.h"
#include "RegisterChild.h"
#include "BitMap.h"
#include "HashTable.h"
#include "Thread_Pool.h"
#include "affinity.h"
#include "processor_num.h"
#include "Barrier.h"
#include "BarrierTest.h"
#include "Trees.h"
#include "insert_sort.h"
#include "writter.h"
#include "readder.h"
#include "hdfs_mine.h"

#include <pthread.h>
#include <unistd.h>

int array[]={3,1,8,4,9,3,4,23,42,43,52,13,5,7,243,35,765,86,234,5467678,243,525,25};

pthread_mutex_t lock_;

//thread func
void dummy_task(void *arg) {
	usleep(10000);
	pthread_mutex_lock(&lock_);
	sleep(2);
	printf("I am doing my work, use seconds!\n");
	pthread_mutex_unlock(&lock_);
}

int main() {
	printf("%d",sizeof(float));
	printf("%d",sizeof(long));

	std::cout << "!!!Hello New Machine!!!" <<std::endl; // prints !!!Hello World!!!
	std::cout<<"little program, and you can choose:"<<std::endl;
	std::cout<<"1, producer consumer"<<std::endl;
	std::cout<<"2, test theron(you must use two terminate to do the test!)"<<std::endl;
	std::cout<<"3, use vector to construct a tree"<<std::endl;
	std::cout<<"4, daemon test"<<std::endl;
	std::cout<<"5, fork a proc"<<std::endl;
	std::cout<<"6, exception test"<<std::endl;
	std::cout<<"7, effect cpp"<<std::endl;
	std::cout<<"8, gen data for test"<<std::endl;
	std::cout<<"9, boost asio test"<<std::endl;
	std::cout<<"10, boost serial test"<<std::endl;
	std::cout<<"11, bitmap"<<endl;
	std::cout<<"12, hashtable test"<<endl;
	std::cout<<"13, thread pool implemetation"<<endl;
	std::cout<<"14, thread affinity test"<<endl;
	std::cout<<"15, "<<endl;
	std::cout<<"16, cpu processor test"<<endl;
	std::cout<<"17, barrier test"<<endl;
	std::cout<<"18, B tree"<<endl;
	std::cout<<"19, insert sort"<<endl;
	std::cout<<"20, writter protobuf"<<endl;
	std::cout<<"21, readder protobuf"<<endl;
	std::cout<<"22, hdfs read in c++"<<endl;

	int choose=0;
	scanf("%d",&choose);
	switch(choose){
	case 1:
		printf("producer consumer problems! \n");
		if(producer_consumer()==0)
			printf("\nproducer consumer successed!\n");;
		break;
	case 2:
		printf("test theron! \n");
		if(test_theron()==0)
			printf("\ntest theron successed!\n");
		break;
	case 3:
		printf("construct a tree! \n");
		if(test_tree()==0)
			printf("\ntest tree successed!\n");
		break;
	case 4:
		printf("test the daemon!");
		if(test_daemon()==0){
			printf("\ntest the daemon!\n");
		}
		break;
	case 5:
		printf("fork a process\n");
		if(process_fork()==0){
			printf("\nfork a process\n");
		}
		break;
	case 6:
		printf("exception test\n");
		if(exception_test()==0){
			printf("\nexception test\n");
		}
		break;
	case 7:{
		printf("effect cpp test\n");
		Compute<int> c1;
		c1.CallWithMax(1,2);
		printf("\neffect cpp test\n");

		Parent *c=new Children();
		c->f2();

		HomeForSale h1;
		HomeForSale h2;
		HomeForSale h3(h1);
		h1=h2;
		break;
	}
	case 8:{
		printf("data gen for test\n");
		if(gen_data_binary()==0){
			printf("data gen for test\n");
		}
		break;
	}
	case 9:
		printf("\nboost asio test\n");
		if(boost_asio_1()==0){
			printf("boost asio_1 test\n");
		}
		if(boost_asio_2()==0){
			printf("boost asio_2 test\n");
		}
		break;

	case 10:{
		printf("boost serial test\n");
		SParent *sc=new SChild(1234567);
		SParent *c1_1=new SChild1(1234321,sc);

		std::ostringstream os;
		std::cout<<"----------"<<endl;
		boost::archive::text_oarchive oa(os);
		std::cout<<"----------"<<endl;
		Register_children(oa);
		oa<<c1_1;
		std::cout<<"----------"<<endl;

		std::cout<<"after serial the os is: "<<os.str().c_str()<<std::endl;

		std::istringstream is(os.str());
		boost::archive::text_iarchive ia(is);
		Register_children(ia);
		SParent *cs;

		ia>>cs;
		cs->f1();

		SChild1 *sc1=reinterpret_cast<SChild1*>(cs);
		SChild *sc_=reinterpret_cast<SChild*>(sc1->child);
		sc_->f1();

		printf("\nboost serial test\n");
		break;
	}
	case 11:{
		printf("data gen for test\n");
//		if(gen_data()==0){
//			printf("data gen for test\n");
//		}

		BitMap *bm_1=new BitMap();
		bm_1->BitMap_init(15);
//		bm->BitMap_set(0);
		bm_1->BitMap_set(1);
//		bm->BitMap_set(2);
		bm_1->BitMap_set(3);
//		bm->BitMap_set(4);
		bm_1->BitMap_set(5);
		for(int i=0;i<24;i++){
			std::cout<<"the bit is:"<<	bm_1->BitMap_get(i)<<std::endl;
		}

		BitMap *bm_2=new BitMap();
		bm_2->BitMap_init(15);
//		bm->BitMap_set(0);
//		bm_2->BitMap_set(1);
//		bm->BitMap_set(2);
		bm_2->BitMap_set(3);
//		bm->BitMap_set(4);
		bm_2->BitMap_set(5);
		for(int i=0;i<24;i++){
			std::cout<<"the bit is:"<<	bm_2->BitMap_get(i)<<std::endl;
		}

		BitMap *bm=bm_1->BitMap_merge(bm_2);
		for(int i=0;i<24;i++){
			std::cout<<"the bit is:"<<bm->BitMap_get(i)<<std::endl;
		}

		std::cout<<"copy constructor func"<<std::endl;
		BitMap *_bm=new BitMap((*bm));
		for(int i=0;i<24;i++){
				std::cout<<"the bit is:"<<_bm->BitMap_get(i)<<std::endl;
			}

		break;
	}
	case 12:{
		printf("hashtable test!\n");
		HashTable *ht=new HashTable(4,4096,4);
		void *p=ht->allocate(1);
		*(int *)(p)=4;
		HashTable::HashTableIterator it=ht->createIterator();
		ht->placeIterator(it,1);
		cout<<"input: "<<*reinterpret_cast<int *>(it.readnext());
		printf("hashtable test!\n");
		break;
	}
	case 13:{
		printf("thread pool test\n");
		pthread_mutex_init(&lock_,NULL);
		Thread_Pool *tp=new Thread_Pool();
		tp->Thread_Pool_init(10,5);
		tp->Thread_Pool_add(dummy_task,tp);
		sleep(5);
		printf("thread pool test\n");
		break;
	}
	case 14:{
		printf("thread affinity test\n");
		if(affinity_test_1()==0){
			printf("thread affinity test\n");
		}
		break;
	}
	case 16:{
		printf("cpu processor test: %d\n",processor_get_num());
		break;
	}
	case 17:{
		printf("barrier test\n");
		BarrierTest *bt=new BarrierTest(3);
		bt->init();
		bt->funcAdd();
		bt->funcAdd();
		bt->funcAdd();
		for(unsigned i=0;i<(bt->ps).size();i++){
			pthread_join((bt->ps)[i],NULL);
		}
		printf("barrier test\n");
		break;
	}
	case 18:{
		printf("b tree test\n");
		TreeNode *tn=new TreeNode();
		Trees *t=new Trees(tn);
		t->insert(3);
		t->insert(2);
		t->insert(4);
		t->insert(5);
		t->insert(6);
		t->insert(7);
		t->insert(8);
		t->insert(9);
		t->insert(13);
		t->insert(12);
//		t->insert(14);
//		t->insert(15);
//		t->insert(16);
//		t->insert(17);
//		t->insert(18);
//		t->insert(19);
//		t->insert(20);
//		t->insert(23);
//		t->insert(22);
//		t->insert(24);
//		t->insert(25);
//		t->insert(26);
//		t->insert(27);
//		t->insert(28);
//		t->insert(29);
//		t->insert(33);
//		t->insert(32);
//		t->insert(34);
//		t->insert(35);
//		t->insert(36);
//		t->insert(37);
//		t->insert(38);
//		t->insert(39);
//		t->insert(43);
//		t->insert(42);
//		t->insert(44);
//		t->insert(45);
//		t->insert(46);
//		t->insert(47);
//		t->insert(48);
//		t->insert(49);
//		t->insert(53);
//		t->insert(52);
//		t->insert(54);
//		t->insert(55);
//		t->insert(56);
//		t->insert(57);
//		t->insert(58);
//		t->insert(59);
//		t->insert(63);
//		t->insert(62);
//		t->insert(64);
//		t->insert(65);
//		t->insert(66);
//		t->insert(67);
//		t->insert(68);
//		t->insert(69);
//		t->insert(73);
//		t->insert(72);
//		t->insert(74);
//		t->insert(75);
//		t->insert(76);
//		t->insert(77);
//		t->insert(78);
//		t->insert(79);
//		t->insert(83);
//		t->insert(82);
//		t->insert(84);
//		t->insert(85);
//		t->insert(86);
//		t->insert(87);
//		t->insert(88);
//		t->insert(89);
//		t->insert(93);
//		t->insert(92);
//		t->insert(94);
//		t->insert(95);
//		t->insert(96);
//		t->insert(97);
//		t->insert(98);
//		t->insert(99);
		t->display();
		printf("b tree test\n");
		break;
	}
	case 19:{
			printf("insert sort test\n");
			insertion_sort("/home/casa/storage/data/file_sort_int.txt",0,3);
			printf("insert sort test\n");
			break;
		}
	case 20:{
			printf("writter test\n");
			writter();
			printf("writter test\n");
			break;
		}
	case 21:{
			printf("readder test\n");
			readder();
			printf("readder test\n");
			break;
		}
	case 22:{
			printf("hdfs in c++ test\n");
//			hdfs_main();
			printf("hdfs in c++ test\n");
			break;
		}
	default:
		printf("over!\n");
	}



	return 0;
}
