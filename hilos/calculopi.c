#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define r 10

typedef struct{
    float x;
    float y;
}punto;

int dentro(punto p){
    return (p.x * p.x + p.y * p.y < r * r) ? 1 : 0;
}

void * tirar_dardo(void * arg){
    punto p;

    p.x = random();
    p.y = random();
}

int main(){
    pthread_t h1;
    pthread_t h2;
    pthread_t h3;
    pthread_t h4;


}