#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int p_h[2];
    int h_p[2];
    pid_t cpid;
    char buf[300],s[300];
    int count = 0;

    if (pipe(p_h) == -1 || pipe(h_p) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0)
    {
        close(p_h[1]);
        close(h_p[0]);
        while (count < 10){
            read(p_h[0],buf,300);
            write(h_p[1],"1",1);
            sleep(1);
            cout << "mensaje numero: " << ++count << " recibido\n";
        }
        write(h_p[1],"q",1);
        close(p_h[0]);
        close(h_p[1]);

        _exit(EXIT_SUCCESS);
    }
    else
    {
        close(p_h[0]);
        close(h_p[1]);
        scanf("%s",s);
        write(p_h[1],s,300);
        read(h_p[0],s,1);
        while(s[0]=='1'){
            scanf("%s",s);
            write(p_h[1],s,300);
            read(h_p[0],s,1);
        }
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}
