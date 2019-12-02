#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(int argc, char ** argv){
    char *node = argv[1];
    struct addrinfo hints;
    struct addrinfo *res;
    hints.ai_family = AF_UNSPEC;
    getaddrinfo(node,NULL,&hints,&res);
    while(res != NULL){
        char host[300];
        char serv[300];
        int l=getnameinfo(res->ai_addr,res->ai_addrlen,host,300,serv,300,NI_NUMERICHOST);
        printf("Host: %s\t Protocol: %d\t Tipo: %d\n",host,res->ai_family,res->ai_socktype);
        res=res->ai_next;
    }
    return 0;
}
