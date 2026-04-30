#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

// para compilar y correr:
// gcc -pthread competenciaPorStdout.c -o ejercicio && ./ejercicio hola como va

typedef struct{
    unsigned    len;
    char *      msg;
}arg;

arg * crear_argumento(char * msg);

void sub_hilo(arg * a);

int main(int argc, char * argv[]){
    if(argc < 3)
        return 1;
    
    setbuf(stdout, NULL);

    pthread_t h1, h2;

    printf("lista de argumentos:\n");
    
    for(unsigned idx = 1; idx < argc ; idx++){
        printf("\t[%d] -> %s\n", idx, argv[idx]);
    }

    arg * arg1, * arg2;
    arg1 = crear_argumento(argv[1]);
    arg2 = crear_argumento(argv[2]);

    if(pthread_create(&h1, NULL, (void *)sub_hilo, arg1))
        return 1;
    if(pthread_create(&h2, NULL, (void *)sub_hilo, arg2))
        return 1;

    pthread_join(h1, NULL);
    pthread_join(h2, NULL);

    free(arg1);
    free(arg2);

    return 0;
}

arg * crear_argumento(char * msg){
    arg * out = malloc(sizeof(arg));

    out -> len = strlen(msg);
    out -> msg = msg;

    return out;
}

void sub_hilo(arg * a){
    for(unsigned idx = 0 ; idx < a -> len ; idx++){
        usleep(100);
        putc((a -> msg)[idx], stdout);
    }
}