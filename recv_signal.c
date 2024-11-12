/**
 * File: recv_signal.c
 * Modified by: John Williams
 * CPE 2600 121
 * Brief summary of program: The program waits for a 
 * SIGUSR1 signal and prints the sender’s PID and an 
 * integer value sent with the signal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/**
 * @brief Signal handler for SIGUSR1 that prints the received integer data.
 */
void handle_signal(int signum, siginfo_t *info, void *context) {
    if (info != NULL) {
        printf("Received SIGUSR1 with value: %d from process with PID: %d\n", info->si_value.sival_int, info->si_pid);
    }
}

int main() {
    struct sigaction sa;
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO; // To retrieve additional information with the signal

    // Register the signal handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Receiver process running with PID: %d\n", getpid());

    // Infinite loop to keep the program running and waiting for signals
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}