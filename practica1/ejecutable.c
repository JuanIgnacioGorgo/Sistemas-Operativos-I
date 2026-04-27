#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// para compilar
// gcc ejecutable.c -o ejecutable

int main(int argc, char * argv[]){
    if(argc == 1) {
        printf("\nNUEVO EJECUTABLE: (process-id : %d ; parent-id : %d)\n", getpid(), getppid());    
        return 0;
    }
    
    int fd_out, a, b;

    fd_out =    atoi(argv[1]);
    a =         atoi(argv[2]);
    b =         atoi(argv[3]);

    // printf("\n%d, %d, %d\n", fd_out, a, b);

    printf("\nNUEVO EJECUTABLE: la suma es %d (process-id : %d ; parent-id : %d)\n", a + b, getpid(), getppid());
    write(fd_out, "\nse conservan los FD\n", 21);

    return 0;
}