#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// para compilar y correr:
//  clear && gcc -pthread jardinConFlag.c -o ejercicio && ./ejercicio 2000

//  VARIABLES DE TESTING
unsigned TEST_NUM = 20;
unsigned BADT_NUM = 0;
unsigned CPM1_NUM = 0;
unsigned CPM2_NUM = 0;

//  VARIABLES DE PROGRAMACION
unsigned ING_NUM;
unsigned TOT_NUM;

//  FLAGS
unsigned LOCK_FLAG = 0;


void molinete1(void);
void molinete2(void);

int main(int argc, char * argv[]){
    if(argc < 2)
        return 1;

    TOT_NUM = atoi(argv[1]);

    do{
        ING_NUM = 0;

        pthread_t h1, h2;

        pthread_create(&h1, NULL, (void *)molinete1, NULL);
        pthread_create(&h2, NULL, (void *)molinete2, NULL);    

        pthread_join(h1, NULL);
        pthread_join(h2, NULL);    

        printf("La cantidad total de ingresantes fue %d/%d\n", ING_NUM, TOT_NUM);

        if(ING_NUM != TOT_NUM) BADT_NUM++;
    }while(TEST_NUM--);

    printf("Fallaron %d tests, se perdieron %d ciclos\n", BADT_NUM, CPM1_NUM + CPM2_NUM);

    return 0;
}

void molinete1(void){
    for(unsigned idx = TOT_NUM / 2; idx ; usleep(100), --idx){
        while(LOCK_FLAG){ ++CPM1_NUM; }
        LOCK_FLAG = 1;
        printf("[M1] Ingreso n°%d\n", ++ING_NUM);
        LOCK_FLAG = 0;
    }

    return;
}
void molinete2(void){
    for(unsigned idx = TOT_NUM / 2; idx ; usleep(100), --idx){
        while(LOCK_FLAG){ ++CPM2_NUM; }
        LOCK_FLAG = 1;
        printf("[M2] Ingreso n°%d\n", ++ING_NUM);
        LOCK_FLAG = 0;
    }

    return;
}