#ifndef FIBONACCI_SEMAPHORE_H
#define FIBONACCI_SEMAPHORE_H

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define FIBONACCI_NUMBER_THREADS 20

struct sem_argument {
    sem_t* semaphore_lock;
    int num_to_calculate;
    int thread_id;
};

int bad_fibonacci(int num) {
    if (num <= 0) {
        return 0;
    } else if (num == 1) {
        return 1;
    }

    return bad_fibonacci(num - 1) + bad_fibonacci(num - 2);
}

void* fibonacci_semaphore_thread_routine(void* args) {
    struct sem_argument* arg = (struct sem_argument*)args;
    sem_wait(arg->semaphore_lock);
    int* result = (int*) malloc(sizeof(int));
    *result = bad_fibonacci(arg->num_to_calculate);
    sem_post(arg->semaphore_lock);
    free(args);
    return result;
}

void run_fibonacci_semaphore(void) {
    const unsigned int semaphore_initial_val = 3;
    pthread_t threads[FIBONACCI_NUMBER_THREADS];
    sem_t semaphore;
    sem_init(&semaphore, 0, semaphore_initial_val);

    for (int i = 0; i < FIBONACCI_NUMBER_THREADS; ++i) {
        struct sem_argument* arg = (struct sem_argument*) malloc(sizeof(struct sem_argument));
        arg->num_to_calculate = i + 1;
        arg->thread_id = i;
        arg->semaphore_lock = &semaphore;
        if (pthread_create(&threads[i], NULL, &fibonacci_semaphore_thread_routine, arg) != 0) {
            perror("Failed to create thread");
        }
    }

    for (int i = 0; i < FIBONACCI_NUMBER_THREADS; ++i) {
        int** result = NULL;
        if (pthread_join(threads[i], (void**)result) != 0) {
            perror("Failed to join thread");
        } else {
            printf("")
        }
    }

    sem_destroy(&semaphore);
}

#endif
