#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

// para compilar y correr
// gcc ej10.c -o ejercicio && ./ejercicio

typedef struct sigaction sig_act;

pid_t SON_ID;
pid_t PAR_ID;

void sub_par (pid_t process_id);
void sub_son (pid_t process_id);

void han_par (int);
void han_son (int);

int main(int argc, char * argv[]){
    
    SON_ID = fork();

    if(SON_ID){
        PAR_ID = getpid();
        sub_par(SON_ID);
    }else{
        PAR_ID = getppid();
        sub_son(PAR_ID);
    }
    return 0;
}

void sub_par (pid_t des_process_id){
    sig_act act_par;
    
    act_par.sa_handler = han_par;
    sigemptyset(&act_par.sa_mask);
    act_par.sa_flags = SA_RESTART;
    
    sigaction(SIGUSR1, &act_par, NULL);
    sleep(1);

    unsigned cont = 0;

    kill(des_process_id, SIGUSR2);

    while(++cont){
        sleep(1);
        printf("[%d] padre esperando...\n", cont);
    }
}

void sub_son (pid_t des_process_id){
    sig_act act_son;

    act_son.sa_handler = han_son;
    sigemptyset(&act_son.sa_mask);
    act_son.sa_flags = SA_RESTART;

    sigaction(SIGUSR2, &act_son, NULL);
    sleep(1);

    unsigned cont = 0;

    while(++cont){
        sleep(1);
        printf("[%d] hijo esperando...\n", cont);
    }
}

void han_par(int sig){
    write(STDOUT_FILENO, "padre recibio, enviando a hijo...\n", 34);
    sleep(1);
    kill(SON_ID, SIGUSR2);
}

void han_son(int sig){
    write(STDOUT_FILENO, "hijo recibio, enviando a padre...\n", 34);
    sleep(1);
    kill(PAR_ID, SIGUSR1);
}