#ifndef BARRIER_H_
#define BARRIER_H_

#include <semaphore.h>

class Barrier {
private:
    int num_of_threads;
    int enter_counter;
    int exit_counter;
    pthread_mutex_t mutex_1;
public:
    Barrier(unsigned int num_of_threads);
    void wait();
	unsigned int waitingThreads();
    ~Barrier();

	// TODO: define the member variables
	// Remember: you can only use semaphores!
};

#endif // BARRIER_H_

