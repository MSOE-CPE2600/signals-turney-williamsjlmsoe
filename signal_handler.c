/**
 * John Williams
 * CPE 2600 121
 * Lab 10
 * @file signal_handler.c
 * @brief Sets a signal handler for SIGINT, the handler prints a message and then quits
 */

/**
 * Modified by:
 * 
 * Brief summary of modifications:
 */


#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Signal handler for SIGINT - prints a message and exits
 */
void handle_signal(int sigNum) {
    printf("Received a SIGINT signal\n");
}

int main() {

    // Register for the signal
    signal(SIGINT, handle_signal);

    // Print the PID so you can use it to kill from another terminal
    printf("Program running with PID: %d\n", getpid());

    // Wait until a signal is received
    while(1) {
        printf("Sleeping\n");
        sleep(1);
    }

    return 0;
}