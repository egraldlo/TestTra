#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include <iostream>
#include <bitset>
#include <cstring>
using namespace std;

#include "gen_data.h"

const int ONE=1;
const int TWO=2;

int gen_data_int(void){
	int file=0;
	if((file=open("/home/casa/data/data_for_test",O_RDWR|O_CREAT))==0)
		printf("cant open file\n");
	printf("file: %d\n",file);
	int number_for_test=0;
	for(int i=0;i<268435456;i++){//1G
		while(number_for_test<100){
			*reinterpret_cast<int *>(&number_for_test)=rand()%1000;
		}
		char str[4];
		sprintf(str,"%d\n",number_for_test);
		int n=0;
		if((n=write(file,str,4))!=4){
			printf("write error %d\n",n);
		}
	}
	close(file);
	return 0;
}

int gen_data_binary(void){
	int file=0;
	if((file=open("/home/casa/storage/data/1",O_RDWR|O_CREAT))==0)
		printf("cant open file\n");
	printf("file: %d\n",file);
	int number_for_test=0;
	for(int i=0;i<16777216;i++){//100M
//		while(number_for_test<100){
//			number_for_test=i;
			number_for_test=rand()%10;
//			printf("%d\n",number_for_test);
//		}
//		char str[4];
//		sprintf(str,"%d\n",number_for_test);
		int n=0;
		if((n=write(file,reinterpret_cast<char *>(&number_for_test),4))!=4){
			printf("write error %d\n",n);
		}
	}

//	for(int i=0;i<8000;i++){//100M
//	//		while(number_for_test<100){
//				number_for_test=1;
//	//			number_for_test=rand()%10;
//	//			printf("%d\n",number_for_test);
//	//		}
//	//		char str[4];
//	//		sprintf(str,"%d\n",number_for_test);
//			int n=0;
//			if((n=write(file,reinterpret_cast<char *>(&number_for_test),4))!=4){
//				printf("write error %d\n",n);
//			}
//		}

	close(file);
	return 0;
}

int zipf(void){

	return 0;
}
