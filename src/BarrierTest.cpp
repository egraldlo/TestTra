/*
 * BarrierTest.cpp
 *
 *  Created on: 2013-9-9
 *      Author: casa
 */

#include "BarrierTest.h"

BarrierTest::BarrierTest(int nThreads)
:nThreads(nThreads){

}

BarrierTest::~BarrierTest() {
	// TODO 自动生成的析构函数存根
}

void * BarrierTest::func(void *args){
	BarrierTest *bt=(BarrierTest *)(args);
	cout<<"in the func"<<endl;
	bt->barrier->Arrive();
	cout<<"cao ni ma ge bi!+++++++++++=="<<endl;
	return (void *)(0);
}

void BarrierTest::funcAdd(){
	pthread_t p1;
	pthread_create(&p1,NULL,func,this);
	cout<<"create a thread: "<<p1<<endl;
	ps.push_back(p1);
}

void BarrierTest::init(){
	barrier=new Barrier(nThreads);
}

