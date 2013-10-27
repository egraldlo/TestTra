/*
 * Friend.h
 *
 *  Created on: 2013-10-25
 *      Author: casa
 */

#ifndef FRIEND_H_
#define FRIEND_H_

#include <iostream>
using namespace std;

// 友元函数是一种定义在类外部的普通函数，但他需要在类体内进行说明，
// 与成员函数进行区分，要用关键字friend,可以访问类的私有成员
class Friend {
public:
	Friend(int x,int y);
	friend int distance(Friend &f);
	~Friend();
private:
	int x_,y_;
};

int distance(Friend &f){
	return (f.x_+f.y_);
};

int main(){
	Friend *f=new Friend(1,2);
	cout<<"dis: "<<distance(*f)<<endl;
	return 0;
}

#endif /* FRIEND_H_ */
