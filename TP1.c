#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define BUFFSIZE 128
#define fd 1
#define WELCOME "Bienvenue dans le Shell ENSEA. \nPour quitter, taper 'exit'.\nenseash % "
#define GOODBYE "Bye Bye ... \n"


void prompt(char *message){
    write(fd, message, strlen(message));
}

void return_code(void){
    int status;
    wait(&status);
    char code_exit[BUFFSIZE];
    if (WIFEXITED(status)) {
        sprintf(code_exit, "enseash [exit:%d] %% ", WEXITSTATUS(status));
        write(fd,code_exit,strlen(code_exit));

    } else if (WIFSIGNALED(status)) {
        sprintf(code_exit, "enseash [sign:%d] %% ", WTERMSIG(status));
        write(fd,code_exit,strlen(code_exit));
    }
}

int main(int argc, char *argv[]) {

    char command[BUFFSIZE];

    //Welcome message

    prompt(WELCOME);


    while(1) {

        int input = read(fd,command,BUFFSIZE);

        command[input-1]='\0';     //exclude the NULL character at the end of the table to read the command

        if (input!=0) {
            if (strcmp(command,"exit")==0) {

                prompt(GOODBYE);
                exit(EXIT_SUCCESS);}
            else {
                int pid = fork();        //creation of a new processus to do secondary tasks

                if (pid != 0) {
                    sleep(1);
                } else {
                    execlp(command, command, (char *) NULL);
                    exit(EXIT_FAILURE);     //Avoids opening several child processes in parallel
                }
                return_code();
            }
        }
    }
}