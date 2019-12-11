#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]){
    char *buf[4];
    buf[0]= "sh";
    buf[1]="-c";
    buf[2]= argv[1];
    buf[3]= (char *)0;
    execvp("/bin/sh",buf);
    cout << "El comando termino de ejecutarse\n";
    return 0;

}
