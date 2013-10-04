#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* daemon函数用于将调用函数的进程转化为守护进程 */
int daemon(int nochdir, int noclose){
	pid_t pid;
	pid = fork ();

	/* 如果创建进程失败 */
	if (pid < 0){
		perror ("fork");
		return -1;
	}

	/* 父进程退出运行 */
	if (pid != 0)
		exit (0);

	/* 成为会话领头进程 */
	pid = setsid();

	if (pid < -1){
		perror ("setsid");
		return -1;
	}

	/* 将工作目录修改成根目录 */
	if (! nochdir)
		chdir ("/");

	/* 将标准输入输出重定向到空设备 */
	if (! noclose){
		int fd;
		fd = open ("/dev/null", O_RDWR, 0);
		if (fd != -1){
			dup2 (fd, STDIN_FILENO);
			dup2 (fd, STDOUT_FILENO);
			dup2 (fd, STDERR_FILENO);
			if (fd > 2)
				close (fd);
		}
	}
	umask (0027);
	return 0;
}

int test_daemon(){
	daemon(0,0);
	sleep(1000);

	return 0;
}
