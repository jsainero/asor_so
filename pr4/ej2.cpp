#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int p_h[2];
    int h_p[2];
    pid_t cpid;
    char buf;

    if (argc < 5)
    {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

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
        dup2(pipefd[0], 0);
        close(pipefd[0]);
        close(pipefd[1]);
        char *newargs[] = {argv[3], argv[4], NULL};
        execvp(argv[3], newargs);

        _exit(EXIT_SUCCESS);
    }
    else
    {
        char buf[100];
        scanf("%s", buf);
        dup2(pi);
        close(pipefd[0]);
        close(pipefd[1]);
        char *newargs[] = {argv[1], argv[2], NULL};
        execvp(argv[1], newargs);
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}