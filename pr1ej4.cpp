#include <iostream> 
#include <time.h>
#include <sys/time.h>
#include <stdio.h>

using namespace std;

int main(){
    tm *aux;
    const time_t t= time(NULL);
    /*Ej2 
    cout << time(NULL) << '\n';
    */
    /*Ej3 
    timeval t1,t2;
   
    gettimeofday(&t1,NULL);
    for(int i =0; i< 1000000;++i);
    gettimeofday(&t2,NULL);
    int sol = t2.tv_usec-t1.tv_usec;
    cout << sol << '\n';*/
    
    
    aux= localtime(&t);
    //cout << aux->tm_year + 1900 <<'\n';

    char *s;

    strftime(s,200,"%A, %d de %B de %Y, %H:%M\n",aux);
    printf("%s",s);
    return 0;
}