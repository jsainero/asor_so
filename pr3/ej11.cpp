#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;
 int main(){
    sigset_t blk_set, old_set, pend_set;
    sigemptyset(&blk_set);
    sigaddset(&blk_set, SIGINT);
    sigaddset(&blk_set, SIGTSTP);
    sigprocmask(SIG_SETMASK, &blk_set, &old_set);
    sleep(/*atoi(getenv(SLEEP_SECS))*/ 30);
    sigpending(&pend_set);
    if (sigismember(&pend_set,SIGINT)){
        cout<<"ha habido sigint\n";
    }
    else if(sigismember(&pend_set,SIGTSTP)){
        cout<<"ha habido sigtstp\n";
        sigdelset(&blk_set, SIGTSTP);
        sigprocmask(SIG_SETMASK, &blk_set, &old_set);
        sleep(2);
        cout << "el programa termina\n";
    }
    return 0;
 }
