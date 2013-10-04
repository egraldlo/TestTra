/*
 * BarrierTest.h
 *
 *  Created on: 2013-9-9
 *      Author: casa
 */

#ifndef BARRIERTEST_H_
#define BARRIERTEST_H_

#include "Barrier.h"

#include <iostream>
#include <vector>
using namespace std;

#include <pthread.h>

class BarrierTest {
public:
	BarrierTest(int nThreads);
	virtual ~BarrierTest();

	void funcAdd();
	void init();
	static void * func(void *args);

private:
	Barrier *barrier;
	int nThreads;

public:
	vector<pthread_t> ps;
};

#endif /* BARRIERTEST_H_ */
