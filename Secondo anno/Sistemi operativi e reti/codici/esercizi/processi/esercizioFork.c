#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FD_READ 0
#define FD_WRITE 1

int generate(void);

int main() {
    srand(time(NULL));
    pid_t pari_pid, disp_pid;
    int fd_pari[2], fd_disp[2];
    pipe(fd_disp);
    pipe(fd_pari);
    ssize_t buffer;

    if ((pari_pid = fork()) == 0) {
        close(fd_pari[FD_READ]);
        while (1) {
            int n = generate();
            if ((n % 2) == 0) {
                write(fd_pari[FD_WRITE], &n, sizeof(int));
            }
        }
    } else if ((disp_pid = fork()) == 0) {
        close(fd_disp[FD_READ]);
        while (1) {
            int t = generate();
            if ((t % 2) != 0) {
                write(fd_disp[FD_WRITE], &t, sizeof(int));
            }
        }
    } else {
        close(fd_disp[FD_WRITE]);
        close(fd_disp[FD_WRITE]);
        int n, t;

        while (1) {
            buffer = read(fd_disp[FD_READ], &n, sizeof(int));
            buffer = read(fd_pari[FD_READ], &t, sizeof(int));
            int m = n + t;
            printf("%d\n", m);
            if (m > 190) {
                kill(pari_pid, SIGTERM);
                kill(disp_pid, SIGTERM);
                break;
            }
        }
    }

    return 0;
}

int generate() {
    int n = rand() % 101;
    return n;
}
