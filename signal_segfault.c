/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by: John Williams
 * 
 * Brief summary of modifications: added <stdlib.h> and <signal.h>,
 * added a signal handler method, and registered the signal handler 
 * using the signal method
 */


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/**
 * @brief Signal handler for SIGSEGV that prints a message and returns.
 */
void handle_sigsegv(int signum) {
    printf("Segmentation fault detected! SIGSEGV received.\n");
}

int main (int argc, char* argv[]) {
    // Register the signal handler for SIGSEGV
    signal(SIGSEGV, handle_sigsegv);

    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}