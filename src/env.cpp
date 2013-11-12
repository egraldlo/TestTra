// 环境变量是每个程序都可以存取的字符串数组，每个字符串都以var=value的形式出现
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 此程序为用getenv()函数读入并修改环境变量

int env(){
	char *env=getenv("JAVA_HOME");
	printf("%s\n",env);
	// printf中一般有行缓冲，在子进程被父进程创建的时候，行缓冲中的内容
	// 在子进程中也是存在的

	// 可以用这个性质的函数进入环境变量中，首先得到的是环境变量的目录，
	// 然后进入环境变量的是
	return 0;
}
