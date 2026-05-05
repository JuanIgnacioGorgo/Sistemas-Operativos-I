#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM 200

unsigned sum = 0;           // variable global para la suma
pthread_mutex_t SUM_LOCK;   // lock para proteger los accesos a la variable global suma

unsigned arr[NUM];

typedef struct{
    unsigned inf;
    unsigned sup;
}_rango;

typedef _rango * rango;

void * sum_tk (rango arg){
    for(unsigned idx = arg -> inf ; idx < arg -> sup ; idx++){
        pthread_mutex_lock      (&SUM_LOCK);
        sum += arr[idx];
        pthread_mutex_unlock    (&SUM_LOCK);

        printf("sumado el elemento: %d\n", arr[idx]);
    }

    return NULL;
}

int main(){
    pthread_t t1, t2;
    
    for(unsigned idx = 0 ; idx < NUM ; arr[idx] = idx, idx++); // INICIADOR DEL ARREGLO COMPARTIDO

    pthread_mutex_init(&SUM_LOCK, NULL);                // INICIADOR DEL LOCK PROTECTOR DE LA SUMA

    rango r1, r2;

    r1 = malloc(sizeof(_rango));
    r2 = malloc(sizeof(_rango));

    r1 -> inf = 0;
    r1 -> sup = NUM / 2;
    r2 -> inf = NUM - (NUM / 2); 
    r2 -> sup = NUM;

    pthread_create(&t1 , NULL, (void *)sum_tk, r1);
    pthread_create(&t2 , NULL, (void *)sum_tk, r2);

    pthread_join(t1, NULL);    
    pthread_join(t2, NULL);

    printf("La suma de los elementos del arreglo es: %d\n", sum);

    free(r1);
    free(r2);    

    return 0;
}