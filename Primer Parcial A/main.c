#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "primo.h"

volatile sig_atomic_t terminar = 0;

void handler_usr1(int sig) { terminar = 1; }
void handler_alarm(int sig) { terminar = 1; }

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s n1 n2\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error al crear el proceso hijo");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        printf("Hijo (PID=%d): Números primos entre %d y %d:\n", getpid(), n1, n2);
        for (int i = n1; i <= n2; i++) {
            if (es_primo(i))
                printf("%d ", i);
        }
        printf("\n");
        exit(EXIT_SUCCESS);
    } else {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        signal(SIGUSR1, handler_usr1);
        signal(SIGALRM, handler_alarm);

        wait(NULL);
        printf("Padre (PID=%d)", getpid());
        printf("Padre: Esperando 20 segundos...\n");

        alarm(20);
        while (!terminar)
            pause();
        alarm(0);

        printf("Padre: Finalizando (por señal SIGUSR1 o por tiempo).\n");
    }
    return 0;
}
