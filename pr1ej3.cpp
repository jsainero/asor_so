#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

using namespace std;

int main(){
    cout << "ID real: " << getuid() << '\n';
    cout << "ID efectivo: " << geteuid() <<'\n' ;
    /*El setuid se utiliza para dar privilegios elevados 
    en determinados archivos para usuarios que no lo poseen, 
    como por ejemplo en el archivo /etc/bin/passwd para que
    todos puedan cambiar la contraseña pero que no puedan leer 
    ni escribir las otras. Por lo tanto, cuando el uid es 
    distinto del euid tiene el bit setuid activado. */
    passwd *p = getpwuid(getuid());
    printf("Nombre: %s\n", p->pw_name);
    printf("Home: %s\n", p->pw_dir);
    printf("Descripcion: %s\n", p->pw_gecos);

    return 0;
}