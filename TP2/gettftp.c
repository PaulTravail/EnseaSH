#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define fd 1
#define ERROR_MESSAGE "Erreur dans la commande !\n"

int main(int argc, char* argv[]){

    char *host = argv[1];
    char *file = argv[2];

    // Command verification
    if(argc != 3){
        write(fd, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
        exit(EXIT_FAILURE);
    }
    return 0;
}