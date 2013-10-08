#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

// 查看物理CPU的个数 注释
// cat /proc/cpuinfo | grep "physical id" | sort |uniq |wc -l
// 查看每个CPU上核的个数
// cat /proc/cpuinfo | grep "core id" | sort -u |wc -l
// 查看线程数
// cat /proc/cpuinfo | grep "processor" |sort -u |wc -l

cpu_set_t mask_t;
cpu_set_t get_t;

void *func(void *arg){
	char buf[256];
	pthread_setaffinity_np(pthread_self(), sizeof(mask_t), &mask_t);
	long j=0;
	while (j++ < 2000000000) {
		memset(buf, 0, sizeof(buf));
	}
	CPU_ZERO(&get_t);
	//获得的只是线程分配的时候的允许运行在核的情况
	//而不是线程真正运行的核的ID，所以下面输出的是运行在三个核上而不是一个
	if (pthread_getaffinity_np(pthread_self(), sizeof(get_t), &get_t) < 0) {
		fprintf(stderr, "get thread affinity failed\n");
	}
	for (j = 0; j < 4; j++) {
		if (CPU_ISSET(j, &get_t)) {
			printf("thread %d is running in processor %ld\n", (int)pthread_self(), j);
		}
	}
	pthread_exit(NULL);
	return (void *)(0);
}

int affinity_test_1(void){
	//将CPU的set清零
	CPU_ZERO(&mask_t);
	//将本序号加入cpu_set中
	CPU_SET(0, &mask_t);
	CPU_SET(1, &mask_t);
	CPU_SET(2, &mask_t);
	pthread_t p1,p2;
	if (pthread_create(&p1, NULL, func, NULL) != 0) {
		fprintf(stderr, "thread create failed\n");
		return -1;
	}
	if (pthread_create(&p2, NULL, func, NULL) != 0) {
		fprintf(stderr, "thread create failed\n");
		return -1;
	}
	//以阻塞的方式等待线程的结束，threadid指定的线程必须是joinable的，
	//当函数返回时，被等待的线程资源被回收
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	return 0;
}


void *myfun(void *arg)
{
	cpu_set_t mask;
	cpu_set_t get;
	char buf[256];
	int i;
	long j;
	int num = sysconf(_SC_NPROCESSORS_CONF);
	printf("in the PC, there is %d processors!\n",num);

	for (i = 0; i < num; i++) {
		//将CPU的set清零
		CPU_ZERO(&mask);
		//将本序号加入cpu_set中
		CPU_SET(i, &mask);
		CPU_SET((i+1)%4, &mask);
		//用pthread_self取得thread id，
		if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) {
			fprintf(stderr, "set thread affinity failed\n");
		}
		CPU_ZERO(&get);
		//获得的只是线程分配的时候的允许运行在核的情况
		//而不是线程真正运行的核的ID，所以下面输出的是运行在三个核上而不是一个
		if (pthread_getaffinity_np(pthread_self(), sizeof(get), &get) < 0) {
			fprintf(stderr, "get thread affinity failed\n");
		}
		for (j = 0; j < num; j++) {
			if (CPU_ISSET(j, &get)) {
				printf("thread %d is running in processor %ld\n", (int)pthread_self(), j);
			}
		}
		j = 0;
		while (j++ < 1000000000) {
			memset(buf, 0, sizeof(buf));
		}
	}
	pthread_exit(NULL);
	return (void *)(0);
}

int affinity_test(void)
{
	pthread_t tid;
	if (pthread_create(&tid, NULL, myfun, NULL) != 0) {
		fprintf(stderr, "thread create failed\n");
		return -1;
	}
	//以阻塞的方式等待线程的结束，threadid指定的线程必须是joinable的，
	//当函数返回时，被等待的线程资源被回收
	pthread_join(tid, NULL);
	return 0;
}

int affinity_test_(void)
{
	int s, j;
	cpu_set_t cpuset;
	pthread_t thread;

	thread = pthread_self();

	/* Set affinity mask to include CPUs 0 to 7 */

	CPU_ZERO(&cpuset);
	for (j = 0; j < 4; j++)
	  CPU_SET(j, &cpuset);

	s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
	if (s != 0)
	  printf("pthread_setaffinity_np");

	/* Check the actual affinity mask assigned to the thread */

	s = pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
	if (s != 0)
		printf("pthread_getaffinity_np");

	printf("Set returned by pthread_getaffinity_np() contained:\n");
	for (j = 0; j < CPU_SETSIZE; j++)
	  if (CPU_ISSET(j, &cpuset))
		  printf("    CPU %d\n", j);

	exit(EXIT_SUCCESS);
}
