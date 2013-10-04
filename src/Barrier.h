/*
 * Barrier.h
 *
 *  Created on: 2013-9-8
 *      Author: casa
 */

#ifndef BARRIER_H_
#define BARRIER_H_

#include <pthread.h>
#include <stdio.h>

class Barrier {
public:
	Barrier(int nThreads);
	virtual ~Barrier();

	void Arrive();

private:
	int             m_nThreads;
	pthread_mutex_t m_l_SyncLock;
	pthread_cond_t  m_cv_SyncCV;
	volatile int    m_nSyncCount;
};

#endif /* BARRIER_H_ */
