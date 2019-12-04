#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_CREAT | O_RDWR, 00777);
    dup2(fd, 1);
    printf("Escuchame, comprendelo\n");
    close(fd);
    return 0;
}