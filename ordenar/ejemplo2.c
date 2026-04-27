#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define n 5

// para compilar
// gcc -o ejemplo2 ejemplo2.c

// este ejemplo generará 2^3 = 8 procesos concurrentes,
// por lo que lo más probable es que no posea salidas
// concurrentes

int main(){

    pid_t pid1 = fork();
    pid_t pid2 = fork();
    pid_t pid3 = fork();

    printf("\ninicio  (%d ; %d ; %d)\n", pid1 ? 1 : 0, pid2 ? 1 : 0, pid3 ? 1 : 0);

    printf("\t(%d ; %d ; %d)\n", pid1 ? 1 : 0, pid2 ? 1 : 0, pid3 ? 1 : 0);

    printf("final   (%d ; %d ; %d)\n", pid1 ? 1 : 0, pid2 ? 1 : 0, pid3 ? 1 : 0);

    return 0;
}