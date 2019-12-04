#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{

    char hard[300];
    char soft[300];
    char result[300];
    struct stat buf;

    stat(argv[1], &buf);
    if (S_ISREG(buf.st_mode))
    {
        strcpy(hard, argv[1]);
        strcpy(soft, argv[1]);
        strcat(hard, ".hard");
        strcat(soft, ".sym");
        link(argv[1], hard);
        symlink(argv[1], soft);
    }

    return 0;
}