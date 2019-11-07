#include <sys/utsname.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(){
    utsname buf;
    uname(&buf);
    printf("sistema: %s\n", buf.sysname);
    printf("Version: %s\n", buf.version);
    printf("Release: %s\n", buf.release);
    printf("Maquina: %s\n", buf.machine);
    printf("Nodo: %s\n", buf.nodename);

    cout << "Longitud maxima de los argumentos: " << sysconf(_SC_ARG_MAX) <<'\n';
    cout << "Numero maximo de hijos: " << sysconf(_SC_CHILD_MAX) <<'\n';
    cout << "Numero maximo de ficheros abiertos: " << sysconf(_SC_OPEN_MAX) <<'\n';
    cout << "Numero máximo de enlaces: " << pathconf("/",_PC_LINK_MAX) << '\n';
    cout << "Tamano maximo de una ruta: " << pathconf("/",_PC_PATH_MAX) << '\n';

    return 0;
}