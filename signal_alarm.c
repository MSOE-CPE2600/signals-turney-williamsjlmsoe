/**
 * File: signal_alarm.c
 * Modified by: John Williams
 * CPE 2600 121
 * Brief summary of program: The program sets an alarm to trigger after 5 seconds 
 * and prints a message when the signal is received.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/**
 * @brief Signal handler for SIGALRM that prints a message when the alarm is received.
 */
void handle_alarm(int signum) {
    printf("Alarm signal received!\n");
}

int main() {
    // Register the signal handler for SIGALRM
    signal(SIGALRM, handle_alarm);

    // Schedule the alarm to go off after 5 seconds
    alarm(5);

    // Wait indefinitely for the signal to be handled
    printf("Waiting for alarm...\n");
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}