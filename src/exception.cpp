#include <stdexcept>
#include <exception>
#include <iostream>
#include <new>
using namespace std;

#include <stdio.h>

class Exception:public runtime_error{
public:
	Exception():runtime_error("error"){}
	inline unsigned getErrorID(){
		return errorID;
	}
	inline void printError(){
		printf("error in here\n");
	}
private:
	unsigned errorID;
};

class NetWorkException:public Exception{
public:
	NetWorkException():Exception(){}
};

class Exception1:public exception{
public:
	Exception1():exception(){}
};

class Exception2:public out_of_range{
public:
	Exception2():out_of_range("out of range"){}
};

class Exception3:public bad_alloc{
public:
	Exception3():bad_alloc(){}
};

class Exception4:public runtime_error{
public:
	Exception4(const string &errorInfo):runtime_error(errorInfo){
	}
};



int exception_test(void){
	int input;
	printf("input a integer: \n");
	scanf("%d",&input);

	int value;

	try {
		if(input==0)
			throw Exception();
		if(input==1)
			throw Exception1();
		if(input==2)
			throw Exception2();
		if(input==3)
			throw Exception3();
		if(input==4)
			throw Exception4("this is the error of iterator");
		if(input==5)
			throw range_error("some range error");
		if(input==6)
			throw overflow_error("some overflow error");
		if(input==7)
			throw underflow_error("some underflow error");
		if(input==8)
			throw logic_error("some logic error");
		if(input==9)
			throw domain_error("some domain error");
		if(input==10)
			throw invalid_argument("some invalid argument");
		if(input==10)
			throw length_error("some length error");
		if(input==11)
			throw out_of_range("some out of range");
		value=89/input;
		printf("value=%d\n",value);
	} catch (Exception &e) {
		cerr<<e.what();
		e.printError();
	}catch(Exception1 &e1){
		cerr<<e1.what()<<endl;
		printf("can i invoke a function in the catch block?\n");
	}catch(Exception2 &e2){
		cerr<<e2.what()<<endl;
	}catch(Exception3 &e3){
		cerr<<e3.what()<<endl;
	}catch(Exception4 &e4){
		cerr<<e4.what()<<endl;
	}

	return 0;
}
