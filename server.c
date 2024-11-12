/**
 * File: server.c
 * Modified by: John Williams
 * CPE 2600 121
 * Lab 10
 * Brief summary of program: The program starts a signal-based game by sending a "ball" 
 * signal (SIGUSR1) to the receiver, tracking the number of exchanges,
 * and ending the game after 10 volleys.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define MAX_EXCHANGES 10

typedef struct {
    pid_t receiver_pid;
    int exchange_count;
} game_data_t;

// Signal handler for receiving the "ball"
void handle_ball(int signum, siginfo_t *info, void *context) {
    game_data_t *game_data = (game_data_t *)context;

    printf("Server: Received the ball from Receiver (PID: %d)!\n", info->si_pid);
    printf("\a"); // Play system bell

    // Increment the exchange count
    game_data->exchange_count++;
    if (game_data->exchange_count >= MAX_EXCHANGES) {
        printf("Server: Game over after %d exchanges!\n", game_data->exchange_count);
        exit(0); // Exit the program after reaching the maximum exchanges
    }

    // Simulate waiting time before hitting back (1 to 2 seconds)
    int wait_time = 1 + rand() % 2;
    sleep(wait_time);

    // Send the ball back to the receiver
    printf("Server: Hitting the ball back!\n");
    printf("\a"); // Play system bell
    if (kill(game_data->receiver_pid, SIGUSR1) == -1) {
        perror("kill");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <receiver_pid>\n", argv[0]);
        exit(1);
    }

    // Set up game data
    game_data_t game_data;
    game_data.receiver_pid = atoi(argv[1]);
    game_data.exchange_count = 0;

    // Seed the random number generator
    srand(time(NULL));

    // Print the PID for reference
    printf("Server PID: %d\n", getpid());

    // Set up the SIGUSR1 handler with SA_SIGINFO to access custom data
    struct sigaction sa;
    sa.sa_sigaction = handle_ball;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

    // Serve the initial ball to the receiver
    printf("Server: Serving the ball to Receiver (PID: %d)!\n", game_data.receiver_pid);
    printf("\a"); // Play system bell
    if (kill(game_data.receiver_pid, SIGUSR1) == -1) {
        perror("kill");
        exit(1);
    }

    // Wait indefinitely for signals
    while (1) {
        pause();
    }

    return 0;
}