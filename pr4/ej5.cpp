#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <fcntl.h>
#include <string.h>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    int err1 = mkfifo("tub1", 0777);
    int err2 = mkfifo("tub2", 0777);

    if (err1 == -1 || err2 == -1)
    {
        printf("Ha ocurrido un error: %s", strerror(errno));
    }

    char buf[257];

    int fd1 = open("tub1", O_NONBLOCK);
    int fd2 = open("tub2", O_NONBLOCK);

    if (fd1 == -1 || fd2 == -1)
    {
        cout << "Ha ocurrido un error durante la apertura\n";
    }

    fd_set *leer_fd;

    while (true)
    {
        FD_ZERO(leer_fd);
        FD_SET(fd1, leer_fd);
        FD_SET(fd2, leer_fd);

        int may = max(fd1, fd2);
        ++may;
        cout << "Vamos a sel\n";
        int retval = select(may, leer_fd, NULL, NULL, NULL);

        int selfd, aux;
        if (retval <= 0)
            continue;

        cout << "sel listo\n";
        if (FD_ISSET(fd1, leer_fd))
        {
            aux = 1;
            selfd = fd1;
            cout << "sel a 1\n";
        }
        else if (FD_ISSET(fd2, leer_fd))
        {
            aux = 2;
            selfd = fd2;
            cout << "sel a 1\n";
        }
        int tam = read(selfd, buf, 256);
        while (tam > 0)
        {
            cout << "leyendo\n";
            buf[tam] = '\0';
            printf("(%d) %s", aux, buf);
            tam = read(selfd, buf, 256);
        }
        cout << "sal del leido\n";
        close(selfd);
        if (aux == 1)
        {
            fd1 = open("tub1", O_NONBLOCK);
            if (fd1 == -1)
            {
                close(fd2);
                break;
            }
        }
        else
        {
            fd2 = open("tub2", O_NONBLOCK);
            if (fd2 == -1)
            {
                close(fd1);
                break;
            }
        }
    }

    return 0;
}
