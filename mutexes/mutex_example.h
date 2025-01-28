#ifndef MUTEX_EXAMPLE_H
#define MUTEX_EXAMPLE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MUTEX_EXAMPLE_NUMBER_THREADS 10

struct mutex_example_argument {
    int* count_location; // 8 bytes for the pointer
    int thread_id; // 4 bytes for the thread id
    int count_to; // 4 bytes for the integer
};

void* mutex_example_thread_routine(void* args) {
    struct mutex_example_argument* arg = (struct mutex_example_argument*)args;
    for (int i = 0; i < arg->count_to; ++i) {
        ++(*(arg->count_location));
    }
    free(args);
    return NULL;
}

void run_mutex_example() {
    const int count_to = 1000;
    int count = 0;

    pthread_t threads[MUTEX_EXAMPLE_NUMBER_THREADS];

    for (int i = 0; i < MUTEX_EXAMPLE_NUMBER_THREADS; ++i) {
        struct mutex_example_argument* arg = (struct mutex_example_argument*) malloc(sizeof(struct mutex_example_argument));
        arg->count_location = &count;
        arg->count_to = count_to;
        arg->thread_id = i;
        if (pthread_create(&threads[i], NULL, &mutex_example_thread_routine, arg) != 0) {
            perror("Error, unable to spawn thread\n");
        }
    }

    for (int i = 0; i < MUTEX_EXAMPLE_NUMBER_THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Error, unable to join thread\n");
        }
    }

    const int theoretical_count = MUTEX_EXAMPLE_NUMBER_THREADS * count_to;

    printf("Theoretical count: %d\nFinal Count: %d\n", theoretical_count, count);
}

#endif