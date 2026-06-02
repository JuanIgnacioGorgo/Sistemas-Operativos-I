#include <stdio.h>
#include <mpi.h>

// para correr y compilar
// mpicc ejemplo2.c -o test && mpirun ./test
// mpicc ejemplo2.c -o test && mpirun --use-hwthread-cpus -np 4 ./test

void main(int argc, char **argv){
    int num_procs, my_id, value;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    //printf("Hello world!, soy el proceso %1.2d/%1.2d\n", my_id + 1, num_procs);

    if(!my_id){
        printf("ingrese el valor\n\t");
        scanf("%d", &value);
    }

    MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("[%d] recibido %d\n", my_id, value);

    MPI_Finalize();
}