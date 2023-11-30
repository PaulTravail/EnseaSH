#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define BUFFSIZE 128

int main(int argc, char *argv[]) {

    //Welcome message
    const char *message = "Bienvenue dans le Shell ENSEA. \n";
    int fd = 1;

    write(fd, message, strlen(message));
    message = "Pour quitter, taper 'exit'. \n";
    write(fd, message, strlen(message));
    message = "enseash % ";
    write(fd,message,strlen(message));
}



