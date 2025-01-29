#ifndef SEMAPHORE_EXAMPLE_TWO_H
#define SEMAPHORE_EXAMPLE_TWO_H

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define SEMAPHORE_EXAMPLE_TWO_NUMBER_THREADS 1000

struct semaphore_example_two_arguments {
    sem_t* semaphore;
    int process_id;
};

void* semaphore_example_two_thread_routine(void* args) {
    struct semaphore_example_two_arguments* arg = (struct semaphore_example_two_arguments*)args;
    sem_wait(arg->semaphore);
    sleep(1);
    printf("Hello from thread: %d\n", arg->process_id);
    sem_post(arg->semaphore);
    free(args);
    return NULL;
}

void run_semaphore_example_two(void) {

    const int semaphore_initial_value = 500;

    pthread_t threads[SEMAPHORE_EXAMPLE_TWO_NUMBER_THREADS];

    sem_t semaphore;

    sem_init(&semaphore, 0, semaphore_initial_value);

    for (int i = 0; i < SEMAPHORE_EXAMPLE_TWO_NUMBER_THREADS; ++i) {
        struct semaphore_example_two_arguments* arg = (struct semaphore_example_two_arguments*) malloc(sizeof(struct semaphore_example_two_arguments));
        arg->process_id = i;
        arg->semaphore = &semaphore;
        if (pthread_create(&threads[i], NULL, &semaphore_example_two_thread_routine, arg) != 0) {
            perror("Unable to spawn thread\n");
        }
    }

    for (int i = 0; i < SEMAPHORE_EXAMPLE_TWO_NUMBER_THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Unable to join thread\n");
        }
    }

    sem_destroy(&semaphore);
}

#endif // SEMAPHORE_EXAMPLE_TWO_H