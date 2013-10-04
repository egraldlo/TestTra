#include <sched.h>

int processor_get_num(void){
	int number=0;
	cpu_set_t cpus;

	// Returns number of processors available to process (based on affinity mask)
	if( sched_getaffinity(0, sizeof(cpus), (cpu_set_t*) &cpus) < 0) {
		number = -1;
		CPU_ZERO( &cpus );
	}

	for (unsigned i = 0; i < sizeof(cpus)*8; i++) {
		if( CPU_ISSET( i, &cpus )) {
			number++;
		}
	}
	return number;
}

