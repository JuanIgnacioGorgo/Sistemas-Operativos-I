#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

// gcc señales.c -o ejercicio && ./ejercicio

/*
// ejercicio 8

int denom = 0;

void handler(int s){ write(STDOUT_FILENO, "err: div. x 0\n", 14); denom = 1; }

int main(){

    signal(SIGFPE, handler);
    
    float r;

    r = 2 / denom;

    printf("r = %f\n", r);

    return 0;
}
*/

void inter_handler(int);

int main(){
    signal(SIGINT, inter_handler);
    
    unsigned cond = 0;

    while(++cond){
        printf("[%1.2d]\n", cond);
        sleep(1);
    }

    return 0;
}

void inter_handler(int sig){
    char c;

    signal(SIGINT, SIG_IGN);

    do{
        write(STDOUT_FILENO, " -> desea salir? [y/n] ", 23);
        c = getchar();
        getchar();
    }while(c != 'y' && c != 'n');

    if(c == 'y')
        exit(0);
    
    signal(SIGINT, inter_handler);
}