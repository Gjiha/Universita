/*
Scrivere un programma C che segue le seguenti specifiche.
Il processo eseguito, inizialmente crea un buffer come array di 11 numeri interi, inizializzati a zero. In seguito genera tre thread utilizzando le librerie POSIX secondo le seguenti specifiche:
•  Il primo thread in un ciclo infinito sceglie casualmente una cella del buffer e vi scrive il numero +1, qualsiasi sia il valore presente nella cella.
•  Il secondo thread in un ciclo infinito sceglie casualmente una cella del buffer e vi scrive il numero -1, qualsiasi sia il valore presente nella cella.
•  Il terzo thread in un ciclo infinito controlla se tutte le celle del buffer sono state inizializzate ad un valore diverso da 0. In caso positivo, determina se il numero di celle contenenti un valore pari a +1 è maggiore di quelle con -1 e termina tutti e tre i thread.
•  Mentre un thread ha accesso al buffer, nessun altro thread deve accedervi.
•  Una volta che un thread ha acceduto in lettura o scrittura al buffer, deve attendere un numero di secondi random tra 0 e 3
*/

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define LEN 10
#define TRUE 1

pthread_mutex_t the_mutex;
pthread_cond_t condc;
pthread_t add, rem, cont;

int buffer[LEN] = {0};
int modified;

void printbuffer() {
    printf("[");
    for (int i = 0; i < LEN; i++) {
        printf(", %d", buffer[i]);
    }
    printf("]\n");
}

void *aggiungi(void *ptr) {
    while (TRUE) {
        pthread_mutex_lock(&the_mutex);
        int i = rand() % LEN;

        modified = 1;

        buffer[i] = 1;
        printf("settato ad 1 la posizione %d\n", i);
        printbuffer();

        pthread_cond_signal(&condc);
        pthread_mutex_unlock(&the_mutex);
        sleep(rand() % 3);
    }
}

void *togli(void *ptr) {
    while (TRUE) {
        pthread_mutex_lock(&the_mutex);
        int i = rand() % LEN;

        modified = 1;

        buffer[i] = -1;
        printf("settato a -1 la posizione %d\n", i);
        printbuffer();

        pthread_cond_signal(&condc);
        pthread_mutex_unlock(&the_mutex);
        sleep(rand() % 3);
    }
}

void *controlla(void *ptr) {
    while (TRUE) {
        pthread_mutex_lock(&the_mutex);

        while (modified == 0) {
            pthread_cond_wait(&condc, &the_mutex);
        }

        modified = 0;
        int c = 0;

        for (int i = 0; i < LEN; i++) {
            if (buffer[i] == 0) {
                c++;
            }
        }

        printf("controllando il buffer\n");
        sleep(rand() % 3);

        if (c != 0) {
            pthread_mutex_unlock(&the_mutex);
        } else {
            printf("sparati\n");
            pthread_kill(add, SIGINT);
            pthread_kill(rem, SIGINT);
            pthread_exit(0);
        }
    }
}

int main(int argc, char *argv[]) {

    pthread_mutex_init(&the_mutex, NULL);
    pthread_cond_init(&condc, NULL);

    pthread_create(&add, NULL, aggiungi, NULL);
    pthread_create(&rem, NULL, togli, NULL);
    pthread_create(&cont, NULL, controlla, NULL);

    pthread_join(add, NULL);
    pthread_join(rem, NULL);
    pthread_join(cont, NULL);

    pthread_mutex_destroy(&the_mutex);
    pthread_cond_destroy(&condc);

    return 0;
}
