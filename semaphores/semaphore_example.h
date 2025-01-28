#ifndef SEMAPHORE_EXAMPLE_H
#define SEMAPHORE_EXAMPLE_H

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

// The number of threads that we are going to spawn in the example
#define SEMAPHORE_EXAMPLE_NUMBER_OF_THREADS 1000

/**
 * There are only two operations that you can do on a semaphore on a thread:
 * 		Wait
 * 			 -Very similar to a lock on a mutex
 * 		Post
 * 			- Very similar to an unlock on a mutex
 */
static sem_t example_semaphore;

static void* semaphore_thread_routine(void* args) {
    sem_wait(&example_semaphore);
    sleep(1);
    int argument = *(int*)args;
    free(args);
    printf("Hello from thread %d\n", argument);
    sem_post(&example_semaphore);
    return NULL;
}

void run_semaphore_example() {

    pthread_t threads[SEMAPHORE_EXAMPLE_NUMBER_OF_THREADS];

    /**
     * Call the constructor for the semaphore
     * args:
     *  1. A reference to the semaphore
     *  2. Boolean : true => shared between processes : false => only shared between threads
     *  3. The initial value of the semaphore
     */
    sem_init(&example_semaphore, 0, 50);

    /**
     * Spawn all of the threads
     */

    for (int i = 0; i < SEMAPHORE_EXAMPLE_NUMBER_OF_THREADS; ++i) {
        /**
         * Create an argument for the thread
         */
        int* argument = (int*) malloc(sizeof(int));
        *argument = i;

        if (pthread_create(&threads[i], NULL, &semaphore_thread_routine, argument) != 0) {
            perror("Failed to spawn thread\n");
        }
    }

    /**
     * Join all of the threads back to the main process
     */
    for (int i = 0; i < SEMAPHORE_EXAMPLE_NUMBER_OF_THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread\n");
        }
    }

    /**
     * Call the destructor for the semaphore
     * args:
     *  1. A reference to the semaphore
     */
    sem_destroy(&example_semaphore);
}

#endif