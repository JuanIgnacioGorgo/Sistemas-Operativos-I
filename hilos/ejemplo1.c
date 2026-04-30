#include <stdio.h>
#include <pthread.h>

// para compilar y correr
// gcc -pthread -o ejercicio && ./ejercicio

void * hola(void * a){
    printf("hola mundo\n");
}

int main(){
    
    pthread_t h1;

    pthread_create(&h1, NULL, hola, NULL);

    pthread_join(h1, NULL);

    printf("no soy el hilo\n");

    return 0;
}