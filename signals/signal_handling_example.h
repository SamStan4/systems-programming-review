#ifndef SIGNAL_HANDLING_EXAMPLE_H
#define SIGNAL_HANDLING_EXAMPLE_H

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

/**
 * Function created for handling the SIGTSTP signal
 */
static void handle_sigtstp(int sig) {
    printf("\n\ninside the handler function for SIGTSTP\n\n");
}

static void handle_sigcont(int sig) {
    printf("\n\ninput number: ");
}


void run_signal_handling_example() {

    /**
     *  signal action structure
     */
    struct sigaction sa;

    /**
     * Give the pointer to the function we want envoked when the signal is recieved
     */
    sa.sa_handler = &handle_sigtstp;


    /**
     * Here we specify that this signal structure is incharge of handling
     * SIGTSTP signals that are recieved
     */
    sigaction(SIGTSTP, &sa, NULL);


    sa.sa_flags = SA_RESTART;


    int x = 0;
    printf("Input number: ");
    scanf("%d", &x);
    int result = x * 5;
    printf("Result %d * 5 = %d\n", x, result);
}

#endif