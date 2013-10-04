/*
 * SChild1.cpp
 *
 *  Created on: 2013-8-25
 *      Author: casa
 */

#include "SChild1.h"

SChild1::SChild1() {
	// TODO 自动生成的构造函数存根

}

SChild1::SChild1(int ID):ID(ID),child(0){

}

SChild1::SChild1(int ID,SParent *sc):ID(ID),child(sc){

}

SChild1::~SChild1() {
	// TODO 自动生成的析构函数存根
}

SChild::SChild(){

}

SChild::SChild(int ID):ID(ID){

}

SChild::~SChild() {

}
