#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;

int pan = 0;
int manteca = 0;

void h1_subr(void);
void h2_subr(void);

int main(){
    pthread_t h1, h2;

    pthread_create(&h1, NULL, (void *)h1_subr, NULL);
    pthread_create(&h2, NULL, (void *)h2_subr, NULL);    

    pthread_join(h1, NULL);
    pthread_join(h2, NULL);

    return 0;
}

void h1_subr(){ // prepara el desayuno
    pthread_mutex_lock(&lock);

    pan = 1;

    pthread_cond_signal(&cond);

    manteca = 1;

    pthread_mutex_unlock(&lock);

    return;
}

void h2_subr(){ // se levanta a comer

    pthread_mutex_lock(&lock);

    while(!(pan && manteca))
        pthread_cond_wait(&cond, &lock);

    if(pan && manteca)
        printf("yum yum\n");
    else
        printf("rompo todo\n");

    return;
}