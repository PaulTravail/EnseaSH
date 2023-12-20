#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFSIZE 128
#define fd 1
#define ERROR_INPUT "Erreur dans la commande !\nUsage: <program> <host> <file>\n"
#define ERROR_ADRESS "Erreur lors de la résolution de l'adresse.\n"
#define ERROR_SOCKET "Erreur lors de la création du socket.\n"
#define ERROR_CONNECT "Erreur lors de l'établissement de la connexion.\n"
#define CONNECT_SUCCESS "Connecté au réseau.\n"

struct addrinfo hints, *result, *rp;
int status;
void *addr;
char adress[BUFSIZE];
char adress_str[BUFSIZE];

void prompt(char *message){
    write(fd, message, strlen(message));
}

void return_adress(char *host){

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    // Host information
    status = getaddrinfo(host, "tftp", &hints, &result);
    if (status != 0) {
        prompt(ERROR_ADRESS);
        exit(EXIT_FAILURE);
    }
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        if (rp->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
            addr = &(ipv4->sin_addr);
        }else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
            addr = &(ipv6->sin6_addr);
        }
        // Convert adress to string
        inet_ntop(rp->ai_family, addr, adress_str, sizeof(adress_str));
        sprintf(adress,"Address: %s\n", adress_str);
        prompt(adress);
    }
}
void create_socket(){

    int client_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (client_socket == -1) {
        prompt(ERROR_SOCKET);
        exit(EXIT_FAILURE);
    }
    // Connection
    status = connect(client_socket, result->ai_addr, result->ai_addrlen);
    if (status == -1) {
        prompt(ERROR_CONNECT);
        close(client_socket);
        exit(EXIT_FAILURE);
    } else {
        //Send message
        prompt(CONNECT_SUCCESS);
        send(client_socket,CONNECT_SUCCESS,strlen(CONNECT_SUCCESS),0);
    }
}

int main(int argc, char* argv[]){

    char *host = argv[1];
    char *file = argv[2];

    // Command verification
    if(argc != 3){
        write(fd, ERROR_INPUT, strlen(ERROR_INPUT));
        exit(EXIT_FAILURE);
    }

    return_adress(host);
    create_socket();
    freeaddrinfo(result);

    return 0;
}
