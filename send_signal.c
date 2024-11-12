/**
 * File: send_signal.c
 * Modified by: John Williams
 * CPE 2600 121
 * Brief summary of program: The program sends a SIGUSR1 signal 
 * with a random integer value to a specified process
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <receiver_pid>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t receiver_pid = atoi(argv[1]);

    // Seed the random number generator
    srand(time(NULL));

    // Generate a random integer to send
    int value = rand() % 100;

    // Set up the signal value to send
    union sigval sig_value;
    sig_value.sival_int = value;

    // Send the SIGUSR1 signal with the random value
    if (sigqueue(receiver_pid, SIGUSR1, sig_value) == -1) {
        perror("sigqueue");
        exit(EXIT_FAILURE);
    }

    printf("Sent SIGUSR1 with value %d to process with PID %d\n", value, receiver_pid);

    return 0;
}