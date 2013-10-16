#include <string>
#include <iostream>
using namespace std;
#include <memory.h>
#include <malloc.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

#include "rdtsc.h"

void insertion_sort(string file, int first, int last)
{      //0 4
	unsigned long long time1;
	char *base=0,*data_;
	unsigned file_length_=16;//4*1024*1024*1024;
	startTimer(&time1);
	int fd_=open(file.c_str(),O_RDONLY);
	if(fd_==-1) {
		printf("Cannot open file ! Reason: \n");
	}
	base= (char*) mmap(0, file_length_, PROT_READ, MAP_PRIVATE, fd_, 0);
	if (base== 0) {
		printf("mmap errors!\n");
	}
//	read(fd_,base,file_length_);
	data_ = (char*) malloc(file_length_);
	memcpy(data_, base, file_length_);
	memset(data_,0,file_length_);
	stopTimer(&time1);
	cout<<"time1: (cycles)"<<time1<<endl;

	for(int i=0;i<4;i++){
		printf("data: %d\n",*(reinterpret_cast<int*>(base)+i));
	}

	int i,j;
	int temp;
	int swap;
	for (i = first+1; i<=last;i++)
	{
		cout<<"_______-"<<endl;
		temp = *(reinterpret_cast<int*>(base)+i);//array[i];
		printf("cao ni mage bi%d \n",temp);
		j=i-1;
		printf("cao ni mage bi%d\n",(*(reinterpret_cast<int*>(base)+j)));
		//與已排序的數逐一比較，大於temp時，該數向後移
		while((j>=first) && (*(reinterpret_cast<int*>(base)+j) > temp))  //当first=0，j循环到-1时，由于[[短路求值]]，不会运算array[-1]
		{
			//将后面的值，如果小于前面的值就放在前面去，一个一个向前比较
			int *val=(reinterpret_cast<int*>(base)+j);
			*(reinterpret_cast<int*>(base)+j+1)= *val;
			j--;
		}
//		int *v=(reinterpret_cast<int*>(base)+i);
//		*(reinterpret_cast<int*>(base)+j+1)=*v;
	}
	for(int i=0;i<4;i++){
		printf("data: %d\n",*(reinterpret_cast<int*>(base)+i));
	}
}
