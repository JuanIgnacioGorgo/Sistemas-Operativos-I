#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    
    printf("hola\n");

    for(unsigned idx = 0 ; idx < 5 ; idx++){
        int pid = fork();

        printf("(pid = %d ; idx = %d)\n", pid, idx);

        if(pid){
            wait(0);
        }else{
            //printf("hijo");
            //execl("./holamundo.o", "holamundo.o", NULL);   
        }
    }

    printf("chau");
}