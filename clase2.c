#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

/*
int denom = 0;

void handler(int s){
    printf("ouch!\n");
    denom = 1;
}

int main(){
    int r;

    signal(SIGFPE, handler);

    // no va a funcionar porque no cambia el valor del registro ya cargado en el procesador
    // cuando rip vuelve a apuntar a dicha instruccion tras fallar

    r = 1 / denom;

    printf("r = %d\n", r);
    
    return 0;
}
*/

/*
void handler(int s){
    printf("señal recibida! lolololol\n");
}

int main(){
    // el handler debe ser registrado previamente al fork, para que sea posible accerder al mismo desde el proceso hijo
    signal(SIGTERM, handler);           // signal : señal a capturar + funcion conductora
    
    pid_t pid = fork();

    if(pid > 0){        // caso padre
        kill(pid, SIGTERM);             // kill : ID del proceso + señal capturable -> enviará la señal dada al proceso del ID dado.
        wait(0);
    }else{              // caso hijo
        exit(0);
    }
}
*/

void handler(){
    int rc;
    struct sigaction sigact = {
        .sa_handler = SIG_IGN,
    };
    
    rc = sigaction(SIGTERM, &sigact, NULL);
    
    printf("handler ejecutado\n");

    if(rc < 0){
        exit(-1);
    }
}

int main(){
    handler();

    pid_t pid = fork();

    if(pid > 0){
        printf("padre inicio\n");
        kill(pid, SIGTERM);
        wait(0);
        printf("padre termino\n");
    }else{
        printf("hijo inicio\n");
        printf("hijo final\n");
        exit(0);
    }

    return 0;
}