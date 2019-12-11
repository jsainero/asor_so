#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

int ints, stps;

void hler(int signal){
	if (signal == SIGINT) ints++;
	else if (signal == SIGTSTP) stps++;
}

int main(){
	ints = stps = 0;
	struct sigaction act;
	//sigint
	sigaction(SIGINT, NULL, &act); // Get handler
	act.sa_handler = hler;
	sigaction(SIGINT, &act, NULL); //Set sa_handler
	//Sigtstp
	sigaction(SIGTSTP, NULL, &act); //Get handler
	act.sa_handler = hler;
	sigaction(SIGTSTP, &act, NULL); //Set sa_handler
	sigset_t set;
	sigemptyset(&set);
	while (ints + stps < 10)
		sigsuspend(&set);
	printf("SIGINT capturás: %i\n", ints);
	printf("SIGTSTP capturás: %i\n", stps);
	return 0;
}
