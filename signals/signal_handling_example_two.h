#ifndef SIGNAL_HANDLING_EXAMPLE_TWO_H
#define SIGNAL_HANDLING_EXAMPLE_TWO_H

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

static void handle_sigtstp_two(int sig) {
    printf("\n\ninside the handler function for SIGTSTP\n\n");
}

void run_signal_handling_example() {

    signal(SIGTSTP, &handle_sigtstp_two);

    int x = 0;
    printf("Input number: ");
    scanf("%d", &x);
    int result = x * 5;
    printf("Result %d * 5 = %d\n", x, result);
}

#endif