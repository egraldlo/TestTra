#include <string>
#include <iostream>
using namespace std;
#include <memory.h>
#include <malloc.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

#include "rdtsc.h"

//void *pthread_sort(void *args){
//
//}

void assign(void *src,void * &desc){
	cout<<"------------------"<<endl;
	cout<<*(int *)src<<endl;
	*(int *)desc=*(int *)src;

}

void insertion_sort(string file)
{
	unsigned long long time1,time2;
	void *base=0,*data_;
	int first=0;
	startTimer(&time1);
	startTimer(&time2);
	unsigned file_length_=0;
	int fd_=open(file.c_str(),O_RDONLY);//|O_WRONLY);
	if(fd_==-1) {
		printf("Cannot open file ! Reason: \n");
	}
	file_length_ = lseek(fd_, 0, SEEK_END);
	int last=(file_length_/4);
	base=  mmap(0, file_length_, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd_, 0);
	for(int i=0;i<(file_length_/4);i++){
//		getchar();
		printf("data: %d\n",*(reinterpret_cast<int*>(base)+i));
	}
	if (base== 0) {
		printf("mmap errors!\n");
	}
	read(fd_,base,file_length_);
	stopTimer(&time1);
	cout<<"time1: (cycles)"<<time1<<endl;

	int i,j;
	int temp;
	void *a,*b,*c;
	int swap;
	for (i = first+1; i<=last;i++)
	{
		temp = *(reinterpret_cast<int*>(base)+i);//array[i];
		j=i-1;
		//與已排序的數逐一比較，大於temp時，該數向後移
		while((j>=first) && (*(reinterpret_cast<int*>(base)+j) > temp))  //当first=0，j循环到-1时，由于[[短路求值]]，不会运算array[-1]
		{
			//将后面的值，如果小于前面的值就放在前面去，一个一个向前比较
			swap=*((int *)base+j);
			*((int *)base+j)=*((int *)base+j+1);
			*((int *)base+j+1)=swap;
			j--;
		}
	}
	stopTimer(&time2);
	cout<<"time2: (cycles)"<<time2<<endl;
	for(int i=0;i<(file_length_/4);i++){
//		getchar();
		printf("data: %d\n",*(reinterpret_cast<int*>(base)+i));
	}
}
