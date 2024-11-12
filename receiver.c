/**
 * File: receiver.c
 * Modified by: John Williams
 * CPE 2600 121
 * Lab 10
 * Brief summary of program: The program waits for a "ball" signal (SIGUSR1), 
 * simulates returning it after a random delay, and sends the signal back to the server.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

// Signal handler for receiving the "ball"
void handle_ball(int signum, siginfo_t *info, void *context) {
    printf("Receiver: Received the ball from Server (PID: %d)!\n", info->si_pid);
    printf("\a"); // Play system bell

    // Simulate waiting time before hitting back (1 to 2 seconds)
    int wait_time = 1 + rand() % 2;
    sleep(wait_time);

    // Send the ball back to the server
    printf("Receiver: Hitting the ball back!\n");
    printf("\a"); // Play system bell
    if (kill(info->si_pid, SIGUSR1) == -1) {
        perror("kill");
        exit(1);
    }
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Print the PID for server reference
    printf("Receiver PID: %d\n", getpid());

    // Set up the SIGUSR1 handler with SA_SIGINFO to access sender information
    struct sigaction sa;
    sa.sa_sigaction = handle_ball;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

    // Wait indefinitely for signals
    while (1) {
        pause();
    }

    return 0;
}