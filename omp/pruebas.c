#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ITE_NUM 100000

// para compilar y correr
// gcc -fopenmp pruebas.c -o ejercicio && ./ejercicio

int main(){
    
    int a[ITE_NUM] = {0};

    int cantidad = 0;

    #pragma omp parallel private(a)
    {
        int id = omp_get_thread_num();
        int nt = omp_get_num_threads();
        
        #pragma omp for // reduction (+: cantidad)
        for(unsigned idx = 0; idx < ITE_NUM ; idx++){
            a[idx] = 2 * idx;
            printf("el hilo %d actualizo el valor %d-esimo ; su\n", id, idx);
            //#pragma omp atomic
            cantidad++;
        }

    }


    if(0){
        for(unsigned idx = 0; idx < ITE_NUM ; idx++){
            printf("%c%1.4d", !(idx % 10) ? '\n' : '-', a[idx]);
        }
    } else { printf("\nshalom\n"); }

    printf("\nla suma resultante es %d; hecho\n", cantidad);
    return 0;
}