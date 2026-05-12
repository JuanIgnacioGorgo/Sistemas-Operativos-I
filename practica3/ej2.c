#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;

void h1_subr();
void h2_subr();

int main(){
    pthread_t h1, h2;

    pthread_create(&h1, NULL, (void *)h1_subr, NULL);
    pthread_create(&h2, NULL, (void *)h2_subr, NULL);    
    
    return 0;
}

void h1_subr(){
    pthread_mutex_lock(&lock);
    printf("a1\n");
    pthread_cond_signal(&cond);
    pthread_cond_wait(&cond, &lock);
    printf("a2\n");

    pthread_mutex_unlock(&lock);
    
    return;
}
void h2_subr(){
    pthread_cond_wait(&cond, &lock);
    printf("b1\n");
    pthread_cond_signal(&cond);
    pthread_cond_wait(&cond, &lock);
    printf("b2\n");

    return;
}