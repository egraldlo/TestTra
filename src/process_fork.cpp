//fork函数调用一次，返回两次，子进程返回的是0，但是父进程返回的是新建子进程的ID
//为什么子进程返回的进程ID是0，但是父进程返回的进程ID是子进程的ID，因为对于子进程来说父进程是可以通过getppid函数得到的，
//对于父进程来说，是没有一个函数可以获得一个进程的所有子进程的ID的
#include <stdio.h>
#include <unistd.h>
int glob=6;
char buff[]="a write to stdout\n";

int process_fork(void){
	int var;
	pid_t pid;
	var = 88;
	//write函数在第一个参数为标准输出文件的时候，相当与printf函数，参数为
	//1， 文件描述符
	//2， buffer的地址
	//3， buffer的大小
	//返回值是写出的大小
	if(write(STDOUT_FILENO,buff,sizeof(buff)-1)!=sizeof(buff)-1)
		printf("error writing!\n");
	printf("before fork\n");

	if((pid=fork())<0)
		printf("error forking\n");
	else if(pid==0){
		//在子进程中，
		glob++;
		var++;
		printf("\n\n\n\nin the child proc\n");
	}
	else{
		sleep(2);
		printf("\n\n\n\nin the parent proc\n");
		printf("the child proc is: %d\n",pid);
	}

	//在子进程和父进程输出不同的结果时，可以想到，子进程获得父进程的数据空间，堆和栈的副本，注意是副本，而不是共享这些东西（如果是共享就不会出现不同的结果）
	//但是父进程和子进程是共享正文段的。
	printf("pid=%d,glob=%d,var=%d\n",getpid(),glob,var);
	return 0;
}
