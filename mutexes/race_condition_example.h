#ifndef RACE_CONDITION_EXAMPLE_H
#define RACE_CONDITION_EXAMPLE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define RACE_CONDITION_EXAMPLE_NUMBER_THREADS 100

static const int count_to = 10000;
static int count = 0;

void* race_condition_thread_routine(void* args) {
    for (int i = 0; i < count_to; ++i) {
        ++count;
    }
    return NULL;
}

void run_race_condition_example() {
    pthread_t threads[RACE_CONDITION_EXAMPLE_NUMBER_THREADS];

    for (int i = 0; i < RACE_CONDITION_EXAMPLE_NUMBER_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, &race_condition_thread_routine, NULL) != 0) {
            perror("Error creating thread\n");
        }
    }

    for (int i = 0; i < RACE_CONDITION_EXAMPLE_NUMBER_THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Error joining threads\n");
        }
    }

    const int theoretical_count = RACE_CONDITION_EXAMPLE_NUMBER_THREADS * count_to;

    printf("Theoretical count: %d\nFinal Count: %d\n", theoretical_count, count);
}

#endif