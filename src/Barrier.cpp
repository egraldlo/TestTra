/*
 * Barrier.cpp
 *
 *  Created on: 2013-9-8
 *      Author: casa
 */

#include "Barrier.h"

Barrier::Barrier(int nThreads) {
	m_nThreads = nThreads;
	int ret;
	ret = pthread_mutex_init(&m_l_SyncLock, NULL);
	if(ret!=0)
		printf("pthread_mutex_init failed at barrier creation.\n");
	printf("the init of barrier\n");
	ret = pthread_cond_init(&m_cv_SyncCV, NULL);
	if(ret!=0)
		printf("pthread_cond_init failed at barrier creation.\n");

	m_nSyncCount = 0;
}

Barrier::~Barrier() {
	  pthread_mutex_destroy(&m_l_SyncLock);
	  pthread_cond_destroy(&m_cv_SyncCV);
}

void Barrier::Arrive() {
	pthread_mutex_lock(&m_l_SyncLock);
	m_nSyncCount++;
	printf("cpu processor test: %d\n",m_nSyncCount);
	if(m_nSyncCount == m_nThreads) {
		printf("arrive the nthreads\n");
		printf("arrive the broadcast\n");
		pthread_cond_broadcast(&m_cv_SyncCV);
		m_nSyncCount = 0;
	}
	else {
		printf("arrive the wait\n");
		pthread_cond_wait(&m_cv_SyncCV, &m_l_SyncLock);

	}

	pthread_mutex_unlock(&m_l_SyncLock);
}
