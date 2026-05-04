#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define TRY_NUM 20

// para compilar y correr
// clear && gcc deadlock.c -o ejercicio && ./ejercicio

void t1_sub(void);
void t2_sub(void);

unsigned CONT_GLOBAL = 0;

pthread_mutex_t MUTEX_1;
pthread_mutex_t MUTEX_2;

int main(){
    pthread_t h1;
    pthread_t h2;

    do{
        CONT_GLOBAL = 0;

        pthread_mutex_init(&MUTEX_1, NULL);
        pthread_mutex_init(&MUTEX_2, NULL);    

        pthread_create(&h1, NULL, (void *)t1_sub, NULL);
        pthread_create(&h2, NULL, (void *)t2_sub, NULL);    

        pthread_join(h1, NULL);
        pthread_join(h2, NULL);
    }while(CONT_GLOBAL);

    return 0;
}

void t1_sub(void){
    unsigned cont = TRY_NUM;
    
    do{
        pthread_mutex_lock(&MUTEX_1);
        pthread_mutex_lock(&MUTEX_2);

        CONT_GLOBAL++;
        printf("[t1 : %1.2d] variable global actualizada -> %1.2d\n", cont, CONT_GLOBAL);

        pthread_mutex_unlock(&MUTEX_2);
        pthread_mutex_unlock(&MUTEX_1);
    }while(--cont);
    
    return;
}

void t2_sub(void){
    unsigned cont = TRY_NUM;

    do{
        
        pthread_mutex_lock(&MUTEX_1);
        pthread_mutex_lock(&MUTEX_2);

        CONT_GLOBAL++;
        printf("[t2 : %1.2d] variable global actualizada -> %1.2d\n", cont, CONT_GLOBAL);

        pthread_mutex_unlock(&MUTEX_1);
        pthread_mutex_unlock(&MUTEX_2);
    }while(--cont);

    return;
}
