#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFSIZE 128

int main(int argc, char *argv[]) {

    char command[BUFFSIZE];
    int fd = 1;

    //Welcome message
    const char *message = "Bienvenue dans le Shell ENSEA. \n";


    write(fd, message, strlen(message));
    message = "Pour quitter, taper 'exit'. \n";
    write(fd, message, strlen(message));
    message = "enseash % ";
    write(fd,message,strlen(message));

    while(1) {

        int input = read(fd,command,BUFFSIZE);

        command[input-1]='\0';     //exclude the NULL character at the end of the table to read the command
        if (input!=0) {
            int pid=fork();        //creation of a new processus to do secondary tasks
            if (pid!=0) {
                sleep(1);
            } else {
                execlp(command,command,(char *)NULL);
                exit(EXIT_FAILURE);     //Avoids opening several child processes in parallel
            }
        }
        write(fd,message,strlen(message));
    }
}
