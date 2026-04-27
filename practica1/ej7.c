#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/wait.h>

#define FILE_NAME "./ejecutable"
#define ARG_CAN     6
#define ARG_LEN     10
#define COM_LEN     ARG_CAN * ARG_LEN

// para compilar y correr
// gcc ej7.c -o ejercicio && ./ejercicio

void proceso_hijo();

int main(int argc, char * argv[]){
    unsigned cond;
    unsigned status;

    pid_t process_id = fork();

    wait(&status);

    if(!process_id)
        proceso_hijo();
    else{
        if(WEXITSTATUS(status) == 'y'){
            do{
                printf("\nsegurx que desea salir? [y/n]\t");
                cond = getchar();
                getchar();
            }while(cond != 'y' && cond != 'n');

            if(cond == 'y'){
                printf("Hasta luego!\n");
                return 0;
            }
        }
        
        execl("./ejercicio", "./ejercicio", NULL);
    }
    return 0;
}

void proceso_hijo(){
    char    com[COM_LEN];
    char *  arg[ARG_CAN];

    printf("Ingrese el comando deseado\n\t-> ");
    fgets(com, COM_LEN, stdin);                     // captura del comando
    com[strcspn(com, "\n")] = '\0';                 // eliminacion salto de linea
        
    if(!strcmp(com, "salir"))
        exit('y');

    unsigned idx = 0;        
    arg[idx] = strtok(com, " ");
    for( ; arg[idx] && idx < ARG_CAN - 1; arg[++idx] = strtok(NULL, " "));

    execl(arg[0], arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], NULL);
}