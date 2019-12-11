#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
using namespace std;

int main (){
    pid_t pid = getpid();
    pid_t ppid = getppid();
    pid_t pgrp = getpgrp();
    pid_t psid = getsid(0);
    char buf[300];
    getcwd(buf,300);
    struct rlimit rlim;
    getrlimit(RLIMIT_NOFILE,&rlim);
    cout << "Identificador del proceso: " << pid << '\n';
    cout << "Identificador del proceso padre: " << ppid << '\n';
    cout << "Identificador del grupo: " << pgrp << '\n';
    cout << "Identificador de sesion: " << psid << '\n';
    printf("Numero maximo de archivos: %d\n",rlim.rlim_max);
    printf("Directorio de trabajo actual: %s\n",buf);









    return 0;
}
