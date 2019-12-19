#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //Memset,
#include <sys/types.h> //getaddrinfo, socket, bind
#include <sys/socket.h> //getaddrinfo, socket, bind
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h> //getaddrinfo,
#include <sys/select.h>
#include <time.h>

#define BUF_SIZE 500

int main(int argc, char *argv[])
    {
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;
    struct sockaddr_storage addr;
    socklen_t addrlen;
    ssize_t nread;
    char buf[BUF_SIZE],serv[BUF_SIZE],host[BUF_SIZE];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    /* getaddrinfo() returns a list of address structures.
        Try each address until we successfully bind(2).
        If socket(2) (or bind(2)) fails, we (close the socket
        and) try the next address. */
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */

        close(sfd);
    }

    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(result);
    listen(sfd,5);
    while (1) {
        int c;
        int clisd = accept(sfd, (struct sockaddr *) &addr, &addrlen);
        getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST,
            serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
        printf("Conexión desde %s:%s\n", host, serv);
        while (c = recv(clisd, buf, 80, 0)) { // Comprobar mensaje!
            buf[c] = '\0';
            send(clisd, buf, c, 0);
        }
    }
    return 0;
}
