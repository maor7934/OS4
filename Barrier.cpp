#include "Barrier.h"
#include <semaphore.h>
#include <pthread.h>

    Barrier::Barrier(unsigned int num_of_threads): num_of_threads(num_of_threads),enter_counter(0),exit_counter(0) {
        pthread_mutex_init(&mutex_1, NULL);
        sem_init(&sem, 0, 0);
        sem_init(&sem2, 0, 0);
    }
    void Barrier::wait() {
        pthread_mutex_lock(&mutex_1);
        this->enter_counter++;
        if (this->enter_counter == this->num_of_threads){
           for (int i = 0; i < this->num_of_threads; i++){
               sem_post(&sem);
           }
        }
        pthread_mutex_unlock(&mutex_1);
        sem_wait(&sem);
        pthread_mutex_lock(&mutex_1);
        if (exit_counter == num_of_threads){
            exit_counter = 0;
        }
        exit_counter++;
        if (exit_counter == num_of_threads){
            for (int i = 0; i < this->num_of_threads; i++){
                sem_post(&sem2);
            }
        }
        pthread_mutex_unlock(&mutex_1);
        sem_wait(&sem2);
        pthread_mutex_lock(&mutex_1);
        if (enter_counter == num_of_threads){
            enter_counter = 0;
        }
        pthread_mutex_unlock(&mutex_1);
    }
    unsigned int Barrier::waitingThreads(){
        pthread_mutex_lock(&mutex_1);
        int return_arg = enter_counter;
        pthread_mutex_unlock(&mutex_1);
        return return_arg;
}
    Barrier::~Barrier() = default;

    // TODO: define the member variables
    // Remember: you can only use semaphores!


//void Barrier::wait() {
//    pthread_mutex_lock(&mutex_1);
//    enter_counter++;
//    pthread_mutex_unlock(&mutex_1);
//    while (enter_counter !=num_of_threads){
//
//    }
//    pthread_mutex_lock(&mutex_1);
//    if (exit_counter == 0){
//        exit_counter = num_of_threads;
//
//    }
//    exit_counter--;
//    pthread_mutex_unlock(&mutex_1);
//    while (exit_counter != 0){
//
//    }
//    pthread_mutex_lock(&mutex_1);
//    if (enter_counter == num_of_threads){
//        enter_counter = 0;
//    }
//    pthread_mutex_unlock(&mutex_1);
//}