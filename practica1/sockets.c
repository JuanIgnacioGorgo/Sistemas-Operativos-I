#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MSG_MAX_LEN 20

// para compilar y correr
// gcc sockets.s -o ejercicio && ./ejercicio

unsigned FD_READ ;
unsigned FD_WRITE;

pid_t PAR_ID;
pid_t CHI_ID;

void sub_par(pid_t);
void sub_chi(pid_t);

int main(int arg, char * argv[]){
    unsigned socket_fd[2];

    if(socketpair(AF_LOCAL, SOCK_DGRAM, 0, socket_fd))
        return -1;

    FD_READ     = socket_fd[0];
    FD_WRITE    = socket_fd[1];

    printf("canales: (lectura : %d ; lectura : %d)\n", FD_READ, FD_WRITE);

    CHI_ID = fork();

    if(CHI_ID){
        PAR_ID = getpid();
        sub_par(CHI_ID);
    }else{
        PAR_ID = getppid();
        sub_chi(PAR_ID);
    }

    return 0;
}

// el padre recibirá los mensajes

void sub_par (pid_t child_id){
    close(FD_WRITE);

    char msg[20];
    unsigned n, cont = 0;

    do{
        printf("\n[%1.2d]padre esperando...\n", cont);
        if(n = read(FD_READ, msg, MSG_MAX_LEN)){
            msg[n - 1] = '\0';
            printf("\tmensaje recibido: %s\n", msg);
        }

    }while(++cont && strcmp("salir", msg));

    printf("\nproceso del padre terminado\n");

    return;
}

// el hijo enviará los mensajes

void sub_chi (pid_t parent_id){
    char msg[20];
    unsigned cont = 0;

    close(FD_READ);

    do{
        sleep(1);
        printf("[%1.2d] Ingrese el mensaje -> ", cont);
        fgets(msg, MSG_MAX_LEN, stdin);
        write(FD_WRITE, msg, strlen(msg));
    }while(++cont && strcmp("salir\n", msg));
    
    printf("\nproceso del hijo terminado\n");

    return;
}