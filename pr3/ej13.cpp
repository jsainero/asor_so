#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

void hler(int signal){
    sigset_t blk_set;
    sigemptyset(&blk_set);
    sigaddset(&blk_set, SIGUSR1);
    sigsuspend(&blk_set);
}

int main (int argc, char *argv[]){
    struct sigaction act;
	sigaction(SIGUSR1, NULL, &act);
	act.sa_handler = hler;
	sigaction(SIGUSR1, &act, NULL);

    sleep(atoi(argv[1]));
    unlink(argv[0]);
    return 0;
}
