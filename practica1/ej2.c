#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define TEST_FILE "./ejecutable"
#define TEST_NAME "ejecutable"

// prototipos de cada apartado

void ej2a(pid_t pid);
void ej2b(pid_t pid);
void ej2c(pid_t pid);
void ej2d(pid_t pid);

// para compilar y correr
// gcc ej2.c -o ej2 && ./ej2
// gcc ejecutable.c -o ejecutable && gcc ej2.c -o ejercicio && ./ejercicio

int main(){
    pid_t processID = fork();
    // processIDes el identificador del proceso generado por fork 

    if(processID) wait(NULL);           // wait() espera que termina el proceso hijo

    printf("\nSoy el %s (var. pid = %1.5d ; pid = %5.1d ; pid padre = %5.1d)\n", 
            processID  ? "padre" : "hijo",   // desde p. hijo:   pid = 0
            processID,                  // desde p. padre:  pid = identificador del p. hijo
            getpid(),                   // id del p. actual
            getppid());                 // id del p. padre, en el caso de no haber terminado

    // ej2a(processID);
    // ej2b(processID);
    // ej2c(processID);
    // ej2d(processID);
    
    return 0;
}

void ej2a(pid_t pid){
    printf("\nej2a: (desde el %s)\n", pid ? "padre" : "hijo");    
    
    if(!pid)  close(1);
    printf("Este mensaje deberia leerse una unica vez (pid = %d)\n", pid);

    return;
}

void ej2b(pid_t pid){
    printf("\nej2b: (desde el %s)\n", pid ? "padre" : "hijo");

    if(!pid) close(0);

    char lol = 'a';

    printf("Ingrese el caracter deseado: ");
    
    lol = getchar();
    
    printf("El caracter ingresado es %c\n", lol);

    return;
}

void ej2c(pid_t pid){
    printf("\nej2c: (desde el %s)\n", pid ? "padre" : "hijo");

    int newFD;
    newFD = dup(STDOUT_FILENO);

    if(pid){
        close(newFD);
        write(STDOUT_FILENO, "el terminal es accesible, fd copia borrado\n", 43);
        printf("printf internamente emplea el FD original para escribir en el terminal, el hijo no podra usar printf\n");
        return;
    }else{
        close(STDOUT_FILENO);
        write(newFD, "el terminal es accesible, fd original borrado\n", 46);
        printf("este mensaje no podra mostrarse en el terminal");
        return;
    };
}

void ej2d(pid_t pid){
    printf("\nej2c: (desde el %s)\n", pid ? "padre" : "hijo");

    if(pid) {printf("EL id del proceso hijo, incluido en la imagen del proceso, pasa a referenciar al comando ejecutado\n") ; return ;}

    printf("DESDE INVOCADOR (pid = %d)", getpid());

    int fd_out = dup(STDOUT_FILENO);
    
    char buffer[6];
    sprintf(buffer, "%1.5d", fd_out),

    // close(STDOUT_FILENO);

    execl(TEST_FILE, TEST_FILE,  buffer, "33", "77", NULL);

    return;
}