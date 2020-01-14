#include "Barrier.h"
#include <semaphore.h>

class Barrier {
public:
    Barrier(unsigned int num_of_threads);
    void wait();
    unsigned int waitingThreads();
    ~Barrier();

    // TODO: define the member variables
    // Remember: you can only use semaphores!
};


