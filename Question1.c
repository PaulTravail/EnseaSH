#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    
    int fd = 1;

    //message d'accueil
    const char *message = "Bienvenue dans le Shell ENSEA. \n";
    write(fd, message, strlen(message));
    message = "Pour quitter, taper 'exit'. \n";
    write(fd, message, strlen(message));
    message = "enseash % \n";
    write(fd,message,strlen(message));
}
