#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUF_SIZE 5

int in, out;
int buf[BUF_SIZE];

pthread_mutex_t mutex;   ///生产者与消费者互斥访问缓冲区
sem_t empty;             ///缓冲区可用资源数，对于生产者
sem_t full;              ///产品可用资源数，对于消费者

void *producer(void *arg) {
	int i;
	for (i=1; i<=20; i++) {
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		in = (in + 1) % BUF_SIZE;
		buf[in] = i;
		printf("produce %d\n", buf[in]);
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
	return NULL;
}

void *customer(void *arg) {
	int i;
	for (i=1; i<=20; i++) {
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		out = (out + 1) % BUF_SIZE;
		printf("customer %d\n", buf[out]);
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	}
	return NULL;
}

int producer_consumer(void) {
	pthread_t tid_prod, tid_cust;

	in = out = -1;
	sem_init(&empty, 0, BUF_SIZE);   ///初始化为BUF_SIZE个缓冲可用
	sem_init(&full, 0, 0);           ///初始化为不可用
	pthread_mutex_init(&mutex, NULL);

	if (pthread_create(&tid_prod, NULL, producer, NULL) != 0) {
		perror("create producer pthread error!\n");
		exit(1);
	}

	if (pthread_create(&tid_cust, NULL, customer, NULL) != 0) {
		perror("create customer pthread error!\n");
		exit(1);
	}

	if (pthread_join(tid_prod, NULL) != 0) {
		perror("join producer pthread error!\n");
		exit(1);
	}

	if (pthread_join(tid_cust, NULL) != 0) {
		perror("join customer pthread error!\n");
		exit(1);
	}

	sem_destroy(&empty);
	sem_destroy(&full);
	pthread_mutex_destroy(&mutex);

	return 0;
}
