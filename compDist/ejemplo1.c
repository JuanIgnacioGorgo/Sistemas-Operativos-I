#include <stdio.h>
#include <mpi.h>

// para correr y compilar
// mpicc ejemplo1.c -o test && mpirun ./test
// mpicc ejemplo1.c -o test && mpirun --use-hwthread-cpus -np 4 ./test

void main(int argc, char **argv){
    int num_procs, my_id;

    int val;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    printf("Hello world!, soy el proceso %1.2d/%1.2d\n", my_id + 1, num_procs);

    if(!my_id){
        printf("\nIngrese el valor por mandar:\n\t");
        scanf("%d", &val);
        getchar();
        MPI_Send(&val, 1, MPI_INT, my_id + 1, 0, MPI_COMM_WORLD);
    }else{
        MPI_Recv(&val, 1, MPI_INT, my_id - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("[%1.2d] Recibido %d", my_id, val);
        if(my_id + 1 < num_procs){
            printf(", enviando al siguiente...\n");
            MPI_Send(&val, 1, MPI_INT, my_id + 1, 0, MPI_COMM_WORLD);
        }else
            printf("\n");
    }

    MPI_Finalize();
}