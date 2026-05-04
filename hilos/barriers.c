#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void * subrut_thread ( void * arg);
pthread_barrier_t barrier;

int main(int argc, char * argv[]){
    pthread_t threads[3];
    pthread_barrier_init(&barrier, NULL, 3);

    for (unsigned idx ; idx < 3 ; idx++){
        pthread_create(threads[idx] = )
    }
    
    return 0;
}

void * subrut_thread ( void * arg){
    printf("Hilo %d")
}