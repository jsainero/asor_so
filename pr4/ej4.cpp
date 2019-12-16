#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
using namespace std;

int main(int argc, char* argv[]){
    int fd = open("alf2", O_WRONLY);
    int i = write(fd,argv[1],strlen(argv[1]));
    close(fd);
    return 0;
}
