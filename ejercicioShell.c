#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    while(1){
        fgets();
        strtok();       
        
        pid_t id = fork();

        if(id == 0){
            execl("./holamundo.o", "holamundo.o", NULL);
            exit(0);
        }else
            wait(0);
    }
}