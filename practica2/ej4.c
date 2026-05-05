#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

volatile int x = 0;
volatile int y = 0;

void * f0 (void * arg) { x = 123 ; y = 1 ; }
void * f1 (void * arg) { while(!y) ; assert(x == 123);  }

int main(){
    pthread_t t0, t1;
    
    unsigned cond = 1;

    do{
        x = 0, y = 0;
        printf("\n%d", ++cond);
        pthread_create(&t0, NULL, f0, NULL);
        pthread_create(&t1, NULL, f1, NULL);    
        pthread_join(t0, NULL);
        pthread_join(t1, NULL);
    
    }while(cond);

    return 0;
}