#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define APROX_RADIUS        1
#define APROX_MULTIPLIER    1
#define CANT_LANZAMIENTOS   10000

// para compilar y correr
// gcc -pthread montecarlo.c -o ejercicio && ./ejercicio

// area_circulo = 4 * pi * r ^ 2
// r = 1
// pi = area_circulo / 4

typedef struct{
    unsigned thread_id;
    unsigned cant_lanzamientos;    
    unsigned cant_aciertos;
}lanzar;

lanzar * crear_lanzar(unsigned id, unsigned mult);

lanzar * subrut_hilo(lanzar * status);

int main(){
    pthread_t   h1, h2, h3, h4;
    lanzar      * l1, * l2, * l3, * l4;
    unsigned    aciertos;

    l1 = crear_lanzar(1, APROX_MULTIPLIER);
    l2 = crear_lanzar(2, APROX_MULTIPLIER);
    l3 = crear_lanzar(3, APROX_MULTIPLIER);
    l4 = crear_lanzar(4, APROX_MULTIPLIER);    

    if(pthread_create(&h1, NULL, (void *)subrut_hilo, l1))
        return 1;
    if(pthread_create(&h2, NULL, (void *)subrut_hilo, l2))
        return 1;
    if(pthread_create(&h3, NULL, (void *)subrut_hilo, l3))
        return 1;
    if(pthread_create(&h4, NULL, (void *)subrut_hilo, l4))
        return 1;

    pthread_join(h1, NULL);
    pthread_join(h2, NULL);
    pthread_join(h3, NULL);
    pthread_join(h4, NULL);    

    aciertos = l1 -> cant_aciertos + l2 -> cant_aciertos + l3 -> cant_aciertos + l4 -> cant_aciertos;

    printf("\naprox. PI = (%1.6lf)", aciertos * 1.0 / (CANT_LANZAMIENTOS * APROX_MULTIPLIER));

    free(l1);
    free(l2);
    free(l3);
    free(l4);

    return 0;
}

lanzar * crear_lanzar(unsigned id, unsigned mult){
    lanzar * out = malloc(sizeof(lanzar));

    out -> thread_id            = id;
    out -> cant_lanzamientos    = CANT_LANZAMIENTOS * mult;
    out -> cant_aciertos        = 0;

    return out;
}

lanzar * subrut_hilo(lanzar * status){
    double x, y;

    for(unsigned idx = status -> cant_lanzamientos ; idx ; idx--){
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        if(x * x + y * y <= APROX_RADIUS * APROX_RADIUS)
            (status -> cant_aciertos)++;
    }

    printf("(L. totales = %1.2d | L. acertados = %1.2d)\n", status -> cant_lanzamientos, status -> cant_aciertos);

    return status;
}