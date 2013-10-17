//#include <iostream>
//using namespace std;
//
//#include <string.h>
//
//#include "hdfs.h"
//
//int hdfs_main(){
//	hdfsFS fs=hdfsConnect("58.198.176.115",9000);
//	const char * readpath="/home/casa/input/wiki/wikistats_featurized/part-00001";
//	hdfsFile readFile=hdfsOpenFile(fs,readpath,O_RDONLY,0,0,0);
//	if(!readFile){
//		cout<<"open file error"<<endl;
//	}
//	char *buffer=new char[25712743];
//	tSize bytes_num=hdfsRead(fs,readFile,(void *)buffer,25712743);
//	hdfsCloseFile(fs,readFile);
//
//	cout<<"print a one: "<<*reinterpret_cast<int *>(buffer)<<endl;
//
//	return 0;
//}
