#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t cpid;
    char buf;

    if (argc < 5)
    {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1)
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
    {   /* Parent writes argv[1] to pipe */
        /* Close unused read end */
        dup2(pipefd[1], 1);
        close(pipefd[0]);
        close(pipefd[1]);
        char *newargs[] = {argv[1], argv[2], NULL};
        execvp(argv[1], newargs);
        wait(NULL); /* Wait for child */
        exit(EXIT_SUCCESS);
    }
}