#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

using namespace std;

int main(){
    /* 
    if (setuid(0) == -1){
	   printf("Error num %d : %s\n",errno, strerror(errno));
	}*/
    for(int i = 1; i<134; ++i){
        printf("Error num %d : %s\n",i, strerror(i));
    }
    return 0;
}