#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// man fork -> en terminal / manual /

// ps -aux -> permite ver los procesos

// execl -> reeemplazar la imagen y el conjunto de imagenes correspondiente al argumento pasado

int main(void){
    int pid;

    pid = fork();
    int x = 0;

    printf("esto es el principio del programa, siendo: ");

    switch (pid) {
        case -1:
            printf("error");
            exit(0);
        case 0:
            printf("Child is PID %d\n", pid); // esto es ejecutado en el entorno copiado del padre
            
            x = 5;
            
            //for(unsigned idx = 1; idx < 10 ; idx++){
            //    execl("./holamundo.o", "holamundo.o", NULL); // se ejecutará una vez
            //}

            printf("esto lo ejecuto el hijo, x = %d\n", x);
            //exit(0);
        default:
            printf("Father is PID %d\n", pid);
            //wait(0); // bloqueante -> el padre queda bloqueado hasta que termina el proceso del hijo
        }

    printf("si esto %d es 0, lo ejecuto el padre, si es 5 lo ejecuto el hijo\n", x);
    return 0;
}