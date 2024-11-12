/**
 * File: signal_sigaction.c
 * Modified by: John Williams
 * CPE 2600 121
 * Lab 10
 * Brief summary of program: This program waits for SIGUSR1 
 * and, using SA_SIGINFO, prints the PID of the sender process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/**
 * @brief Signal handler for SIGUSR1 that prints the PID of the sender.
 */
void handle_signal(int signum, siginfo_t *info, void *context) {
    if (info != NULL) {
        printf("Received SIGUSR1 from process with PID: %d\n", info->si_pid);
    }
}

int main() {
    struct sigaction sa;
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO; // To receive detailed information about the signal

    // Register the signal handler for SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    // Print the process ID for convenience
    printf("Process running with PID: %d\n", getpid());

    // Infinite loop to keep the program running
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}

