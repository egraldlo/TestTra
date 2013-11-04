#include <string>
#include <iostream>
using namespace std;
#include <memory.h>
#include <malloc.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
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
	for(int i=0;i<(file_length_/4);i++){
//		getchar();
		printf("data: %d\n",*(reinterpret_cast<int*>(base)+i));
	}
	cout<<"time2: (cycles)"<<time2<<endl;
}

int binary_search(int begin,int end,void *base,int temp){
	int middle=(begin+end)/2;
	if(temp>=*(reinterpret_cast<int*>(base)+middle)){
		begin=middle;
		end=end;
	}
	else{
		begin=begin;
		end=middle;
	}
	if((begin+1)==end){
		return middle;
	}
	return binary_search(begin,end,base,temp);
}

void binaray_insert_sort(string file)
{
	unsigned long long time1,time2,timeslice;
	unsigned long long timemove=0;
	void *base=0,*data_;
	int first=0;
	startTimer(&time1);
	unsigned file_length_=0;
	int fd_=open(file.c_str(),O_RDONLY);//|O_WRONLY);
	if(fd_==-1) {
		printf("Cannot open file ! Reason: \n");
	}
	file_length_ = lseek(fd_, 0, SEEK_END);
	int last=(file_length_/4);
	base=  mmap(0, file_length_, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd_, 0);
	for(int i=0;i<(file_length_/4);i++){
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
	int swap;

	startTimer(&time2);
	for (i = first+1; i<last;i++)
	{
		temp = *(reinterpret_cast<int*>(base)+i);//array[i];
		// 二分法
		j=i-1;
		int begin=0;
		int end=j;
		int exact;
		if(temp<=*(reinterpret_cast<int*>(base)+begin)){
			exact=0;
		}
		else if(temp>=*(reinterpret_cast<int*>(base)+end)){
			*((int *)base+end+1)=temp;
			continue;
		}
		else{
			exact=binary_search(begin,end,base,temp);
		}
//		cout<<"time2: (cycles)"<<time2<<endl;
//		cout<<"time2: (cycles)"<<time2/(double)3200000000<<endl;
		sliceTimerStart(&timeslice);
		memmove(base+4*(exact+1),base+(4*exact),(i-exact)*4);
		*((int *)base+exact)=temp;
		sliceTimerStop(&timeslice);
		timemove+=timeslice;
	}
	stopTimer(&time2);
	for(int i=0;i<(file_length_/4);i++){
		printf("data: %d\n",*(reinterpret_cast<int*>(base)+i));
	}
	cout<<"time2: (cycles)"<<time2/(double)3200000000<<endl;
	cout<<"timemove: (cycles)"<<timemove/(double)3200000000<<endl;
}

void fetch_sort(string file)
{
	unsigned long long time1,time2,timeslice;
	unsigned long long timemove=0;
	void *base=0,*data_;
	int first=0;
	startTimer(&time1);
	unsigned file_length_=0;
	int fd_=open(file.c_str(),O_RDONLY);//|O_WRONLY);
	if(fd_==-1) {
		printf("Cannot open file ! Reason: \n");
	}
	file_length_ = lseek(fd_, 0, SEEK_END);
	int last=(file_length_/4);
	base=  mmap(0, file_length_, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd_, 0);
	for(int i=0;i<(file_length_/4);i++){
		printf("data: %d\n",*(reinterpret_cast<int*>(base)+i));
	}
	if (base== 0) {
		printf("mmap errors!\n");
	}
	read(fd_,base,file_length_);
	void *new_mem=malloc(file_length_);
	stopTimer(&time1);
	cout<<"time1: (cycles)"<<time1<<endl;

	int i,j;
	int temp;
	int swap;

	startTimer(&time2);
	int max=0;
	int max_postion;
	for (i = first; i<last;i++)
	{
//		if(i==100){
//			for(int l=0;l<100000;l++){
//				printf("data: %d\n",*(reinterpret_cast<int*>(new_mem)+l));
//			}
//		}
		max = *(reinterpret_cast<int*>(base)+i);//array[i];
		for(j=first;j<last;j++){
			if(*(reinterpret_cast<int*>(base)+j)>max){
				max_postion=j;
				max=*(reinterpret_cast<int*>(base)+j);
			}
		}
		*(reinterpret_cast<int*>(base)+max_postion)=0;
		*((int *)new_mem+i)=max;
//		// 二分法
//		j=i-1;
//		int begin=0;
//		int end=j;
//		int exact;
//		if(temp<=*(reinterpret_cast<int*>(base)+begin)){
//			exact=0;
//		}
//		else if(temp>=*(reinterpret_cast<int*>(base)+end)){
//			*((int *)base+end+1)=temp;
//			continue;
//		}
//		else{
//			exact=binary_search(begin,end,base,temp);
//		}
////		cout<<"time2: (cycles)"<<time2<<endl;
////		cout<<"time2: (cycles)"<<time2/(double)3200000000<<endl;
//		sliceTimerStart(&timeslice);
//		memmove(base+4*(exact+1),base+(4*exact),(i-exact)*4);
//		*((int *)base+exact)=temp;
//		sliceTimerStop(&timeslice);
//		timemove+=timeslice;
	}
	stopTimer(&time2);
	for(int i=0;i<(file_length_/4);i++){
		printf("data: %d\n",*(reinterpret_cast<int*>(new_mem)+i));
	}
	cout<<"time2: (cycles)"<<time2/(double)3200000000<<endl;
//	cout<<"timemove: (cycles)"<<timemove/(double)3200000000<<endl;
}

//void qsort(void *base, size_t nmemb, size_t size, int(*compar)(const void *, const void *));

int compar(const void *a, const void *b){
	if(*(int *)a>*(int *)b){
		return 1;
	}
	if(*(int *)a==*(int *)b){
		return 0;
	}
	if(*(int *)a<*(int *)b){
		return -1;
	}
}

void c_lib_sort(string file)
{
	unsigned long long time1,time2,timeslice;
	unsigned long long timemove=0;
	void *base=0,*data_;
	int first=0;
	startTimer(&time1);
	unsigned file_length_=0;
	int fd_=open(file.c_str(),O_RDONLY);//|O_WRONLY);
	if(fd_==-1) {
		printf("Cannot open file ! Reason: \n");
	}
	file_length_ = lseek(fd_, 0, SEEK_END);
	int last=(file_length_/4);
	base=  mmap(0, file_length_, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd_, 0);
//	for(int i=0;i<(file_length_/4);i++){
//		printf("data: %d\n",*(reinterpret_cast<int*>(base)+i));
//	}
	if (base== 0) {
		printf("mmap errors!\n");
	}
	read(fd_,base,file_length_);
	qsort(base,last,4,compar);
	stopTimer(&time1);
//	for(int i=0;i<(file_length_/4);i++){
//		printf("data: %d\n",*(reinterpret_cast<int*>(base)+i));
//	}
	cout<<"time1: (cycles)"<<time1/(double)3200000000<<endl;
}

void swap(int *a, int *b)
{
    int tmp;
    tmp = *a; *a = *b; *b = tmp;
}

void quick_sort(void * a, int left, int right)
{
    int i = left + 1, j = right;
    int  key = *(reinterpret_cast<int *>(a)+left);

    if (left >= right) return;

    /* 从i++和j--两个方向搜索不满足条件的值并交换  *
     * 条件为：i++方向小于key，j--方向大于key      */
    while (1) {
       while (*(reinterpret_cast<int *>(a)+j) > key) j--;
       while (*(reinterpret_cast<int *>(a)+i) < key&&i<j) i++;
       if(i >= j) break;
       swap((reinterpret_cast<int *>(a)+i),(reinterpret_cast<int *>(a)+j));
       if(*(reinterpret_cast<int *>(a)+i)==key)j--;
       else  i++;
    }

    /* 关键数据放到‘中间’ */
    swap((reinterpret_cast<int *>(a)+left),(reinterpret_cast<int *>(a)+j));

    if(left  < i - 1)   quick_sort(a, left, i - 1);
    if(j + 1 < right)  quick_sort(a, j + 1 , right);
}

void self_quick_sort(string file){
	unsigned long long time1,time2,timeslice;
	unsigned long long timemove=0;
	void *base=0,*data_;
	int first=0;
	startTimer(&time1);
	unsigned file_length_=0;
	int fd_=open(file.c_str(),O_RDONLY);//|O_WRONLY);
	if(fd_==-1) {
		printf("Cannot open file ! Reason: \n");
	}
	file_length_ = lseek(fd_, 0, SEEK_END);
	int last=(file_length_/4);
	base=  mmap(0, file_length_, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd_, 0);
//	for(int i=0;i<(file_length_/4);i++){
//		printf("data: %d\n",*(reinterpret_cast<int*>(base)+i));
//	}
	if (base== 0) {
		printf("mmap errors!\n");
	}
	read(fd_,base,file_length_);
	startTimer(&time1);
	quick_sort(base,0,last);
	stopTimer(&time1);
//	for(int i=0;i<(file_length_/4);i++){
//		printf("data: %d\n",*(reinterpret_cast<int*>(base)+i));
//	}
	cout<<"time1: (cycles)"<<time1/(double)3200000000<<endl;
}
