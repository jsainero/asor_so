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

#include <time.h>

#define BUF_SIZE 500

int main(int argc, char *argv[])
    {
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;
    ssize_t nread;
    char buf[BUF_SIZE],lahora[BUF_SIZE];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
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
    freeaddrinfo(result);           /* No longer needed */

    /* Aquí ya tenemos el socket en sfd */
time_t tiempo = time(NULL);
struct tm *tm = localtime(&tiempo);

for (;;) {
peer_addr_len = sizeof(struct sockaddr_storage);
nread = recvfrom(sfd, buf, BUF_SIZE, 0,
        (struct sockaddr *) &peer_addr, &peer_addr_len);
if (nread == -1)
    continue;               /* Ignore failed request */

char host[NI_MAXHOST], service[NI_MAXSERV];
if (buf[0]=='t'){
    size_t bytesT = strftime(lahora, BUF_SIZE, "%I:%M:%S %p", tm);
    lahora[bytesT] = '\0';
    sendto(sfd, lahora, bytesT, 0, (struct sockaddr *) &peer_addr, peer_addr_len);
}else if (buf[0]=='d'){
    size_t bytesT = strftime(lahora, BUF_SIZE, "%Y-%m-%d", tm);
    lahora[bytesT] = '\0';
    sendto(sfd, lahora, bytesT, 0, (struct sockaddr *) &peer_addr, peer_addr_len);
}else if(buf[0]=='q'){
    exit(0);
}else printf("Comando no soportado %s\n",buf);

s = getnameinfo((struct sockaddr *) &peer_addr,
                peer_addr_len, host, NI_MAXHOST,
                service, NI_MAXSERV, NI_NUMERICSERV);
if (s == 0)
    printf("Received %ld bytes from %s:%s\n",
                    (long) nread, host, service);
else
    fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));

if (sendto(sfd, buf, nread, 0,
    (struct sockaddr *) &peer_addr,peer_addr_len) != nread)
        fprintf(stderr, "Error sending response\n");
}
}
