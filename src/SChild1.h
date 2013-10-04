/*
 * SChild1.h
 *
 *  Created on: 2013-8-25
 *      Author: casa
 */

#ifndef SCHILD1_H_
#define SCHILD1_H_

#include <iostream>
using namespace std;

#include "SParent.h"

class SChild1:public SParent{
public:
	SChild1();
	SChild1(int ID);
	SChild1(int ID,SParent *sc);
	virtual ~SChild1();

	void f1(){
		cout<<"in the child_1 c_func1"<<endl;
	}

public:
	int ID;
	SParent *child;

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version){
		ar & boost::serialization::base_object<SParent>(*this) & ID & child;
	}
};

class SChild:public SParent{
public:
	SChild();
	SChild(int ID);
	virtual ~SChild();

	void f1(){
		cout<<"in the child func1"<<endl;
	}

public:
	int ID;

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version){
		ar & boost::serialization::base_object<SParent>(*this) & ID;
	}
};

#endif /* SCHILD1_H_ */
