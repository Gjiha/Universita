#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syscall.h>
#include <time.h>
#include <unistd.h>

#define MAX 190
#define TRUE 1
#define RD 0
#define WR 1

int randomize(void) {
    int n = rand() % 101;
    return n;
}

int main(int agrc, char *argv[]) {

    // costruzione pipe;
    int odd_pipe[2];
    int even_pipe[2];
    pipe(odd_pipe);
    pipe(even_pipe);
    int buffer;
    int even_pid, odd_pid;

    if ((even_pid = fork()) == 0) {

        srand(time(NULL));
        close(even_pipe[RD]);
        while (TRUE) {
            int n = randomize();
            if ((n % 2) == 0) {
                write(even_pipe[WR], &n, sizeof(int));
            }
        }
    } else if ((odd_pid = fork()) == 0) {

        srand(time(NULL));
        close(odd_pipe[RD]);
        while (TRUE) {
            int n = randomize();
            if ((n % 2) == 1) {
                write(odd_pipe[WR], &n, sizeof(n));
            }
        }
    } else {
        close(even_pipe[WR]);
        close(odd_pipe[WR]);

        int even, odd;

        while (TRUE) {
            buffer = read(even_pipe[RD], &even, sizeof(int));
            buffer = read(odd_pipe[RD], &odd, sizeof(int));
            int final = odd + even;
            printf("%d +  %d = %d\n", even, odd, final);

            if (final >= MAX) {
                printf("%d è maggiore di %d\n", final, MAX);
                kill(odd_pid, SIGTERM);
                kill(even_pid, SIGTERM);
                break;
            }
        }
    }

    return 0;
}
