#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main (){
    pid_t pid = getpid();
    pid_t ppid = getppid();
    pid_t pgrp = getpgrp();
    pid_t psid = getsid(0);
    








    return 0;
}
