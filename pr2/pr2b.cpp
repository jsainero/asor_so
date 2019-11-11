#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

int main()
{
    char name[100];

    cout << "Introduzca el nombre del fichero: ";
    scanf("%s", name);
    struct stat *buf;

    stat(name, buf);

    printf("Major: %d\n", major(buf->st_dev));
    printf("Minor: %d\n", minor(buf->st_dev));
    printf("Inodo: %lu\n", buf->st_ino);
    printf("Tipo: %d\n", buf->st_mode);
    printf("Ultimo acceso: %ld\n", buf->st_atim.tv_sec);
}