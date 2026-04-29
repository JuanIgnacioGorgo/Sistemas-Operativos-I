#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// para compilar y correr
// gcc pipes.c -o ejercicio && ./ejercicio

#define MAX_SIZE 20

int FD_READ ;
int FD_WRITE;

void rut_parent(pid_t child_id);
void rut_child(pid_t parent_id);

int main(){
    unsigned pipe_fd[2];

    pipe(pipe_fd);

    printf("canales del pipe: (lectura : %d ; escritura : %d)\n", pipe_fd[0], pipe_fd[1]);
    
    FD_READ     = pipe_fd[0];
    FD_WRITE    = pipe_fd[1]; 

    pid_t process_id = fork();
    if(process_id)
        rut_parent(process_id);
    else
        rut_child(getppid());

    return 0;
}

// por propositos didacticos, el child sera quien escribira y el parent sera quien leera

void rut_parent(pid_t child_id){
    printf("desde el padre: (%d : %d)\n", FD_READ, FD_WRITE);
    close(FD_WRITE);

    unsigned n, cont = 0;
    char msg[MAX_SIZE];

    while(++cont){
        if(n = read(FD_READ, msg, MAX_SIZE)){
            msg[n] = '\0';
            printf("\tel hijo le dijo al padre: %s", msg);
        }
    }
    return;
}

void rut_child(pid_t parent_id){
    printf("desde el hijo (%d : %d)\n", FD_READ, FD_WRITE);
    close(FD_READ);

    unsigned cont = 0;
    char msg[MAX_SIZE];

    while(++cont){
        sleep(1);
        printf("[%1.2d] Ingrese el mensaje -> ", cont);
        fgets(msg, MAX_SIZE, stdin);
        write(FD_WRITE, msg, strlen(msg));
    }

    return;
}
