#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]){
    char *buf[4];
    buf[0]= "sh";
    buf[1]="-c";
    buf[2]= argv[1];
    buf[3]= (char *)0;

    pid_t id;
    id=fork();
    if(id==0){
        /*hijo*/
        sleep(10);
        setsid();
        char dir[300];
        getcwd(dir,300);
        strcat(dir,"/tmp");
        chdir(dir);
        int fd1 = open("/tmp/daemon.out", O_CREAT | O_RDWR, 00777);
        int fd2 = open("/tmp/daemon.err", O_CREAT | O_RDWR, 00777);
        int fd0 = open("/dev/null", O_CREAT | O_RDWR, 00777);
        dup2(fd2, 2);
        dup2(fd1, 1);
        dup2(fd0, 0);
        close(fd0);
        close(fd1);
        close(fd2);
        execvp("/bin/sh",buf);
        cout << "El comando termino de ejecutarse\n";

        _exit(0);
    }
    else{
        sleep(20);

    }
  
    return 0;

}
