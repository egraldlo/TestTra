//程序首先是通过预处理器，然后经过编译器，所以当类似与#define存在的时候，编译器根本看不见这些定义，在编译器
//在处理代码之前早就被预处理器移走了，所以编译器最后看见的只是define定义之后交换的那个值
//#define NUMBER 3
//解决方法是将#define写为const int Number=3;
//当使用#define的时候，会导致最后的.o文件中出现多份3，如果改为常量就不会出现这种情况

#include <iostream>
using namespace std;

const char * const authorName = "zhanglei";
//这个写法的意思是：常量指针，指针所指的是常量，const写在类型之前和类型之后都可以

//对于形似函数的宏，最好用inline函数替换#define

template <typename T>
//每一个template的模板的模板标志是不一样的，比如
//有两个模板template<class T1>和template<class T2>
//这两个模板的名字T1,T2是一定不能一样的
class Compute{
public:
	inline void CallWithMax(const T &a,const T &b){
		if(a>b)
			cout<<"a>b"<<endl;
		else
			cout<<"a<b"<<endl;
	}
	//尽量将函数宏用inline函数代替
};

class Chinese{
private:
	static const string national;
	//有些编译器不能在class中这么直接写"China"进行赋值，那样就要在.cpp实现文件中写才行
	//就比如在class中只是static const string national;
	//在cpp中会是const string Chinese::national="China";
	//单例模式中的单例可以这么写
public:
	enum{Number=5};
	int score[Number];
	//由于编译器不允许在class中给Number赋值，但是score数组有必须先知道Number的值，这个时候可以用枚举enum
	//enum有点像#define，因为取得const的地址是合法的,但是取得enum或者#define的地址是不合法的，如果你不想
	//让别人获得一个pointer活reference指向你的某个整数常量，可以这么做
};

//条款3 使用const
//STL迭代器是以指针为根据塑模出来，所以迭代器的作用就像个T*指针，申明迭代器为const就像申明指针为const一样（T * const）
//表明这个迭代器不能指向不同的东西，但是所指的东西的值是可以改变的，如果你指向的东西不可被改动，你需要的是const_iterator
//int * const p;//指针不可变，指针指向的内容可变

//如果类中的成员函数用const修饰，代表此函数不能改变类的成员变量

//条款41	了解隐式接口和编译期多态
//单看题目就能获得一些信心，多态可以是编译期时产生，还可以是运行时产生，后者可以利用基类+虚函数实现
//前者可以利用template实现，两种方式前者在编译期，对后来运行时的时间消耗会有所减小，后者虚函数是在
//运行时才去决定去调用哪个函数

//尝试写一个继承的实现
class Parent{
public:
	void f1(){
		cout<<"in p"<<endl;
	}

	void f2(){
		f1();
	}
};

class Children:public Parent{
public:
	void f1(){
		cout<<"in c"<<endl;
	}
};

//条款6 如果不想使用编译器自动生成的函数，就该明确拒绝
//如果出现拷贝相关的语句就不应该通过，但是你自己不申明，编译器会自动为你生成一个，所有编译器
//生成的都是public的
class HomeForSale{//
public:
	HomeForSale(){}
private:
//	HomeForSale(const HomeForSale&);
//	HomeForSale & operator=(const HomeForSale);
	//以上这么写的是为了避免对象直接调用拷贝构造函数和对象赋值，造成独一无二的对象被复制
};












