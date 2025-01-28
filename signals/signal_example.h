#ifndef SIGNAL_EXAMPLE_H
#define SIGNAL_EXAMPLE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

void run_signal_example() {

    int pid = fork();

    if (pid == -1) {
        return;
    }

    if (pid == 0) {
        // this would be the child process

        // Create an infinite IO loop in the child process
        while (1) {
            printf("repeated message\n");
            usleep(50000); // sleep for 50,000 micro seconds
        }

    } else {
        // this would be the parent process

        sleep(1);

        // send sigkill to the child process
        kill(pid, SIGKILL);
        wait(NULL);
    }
}

#endif