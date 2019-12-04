#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Numero de argumentos no valido\n";
        return -1;
    }

    struct stat *buf;
    cout << argv[1] << '\n';

    if (stat(argv[1], buf) == -1)
    {
        cout << "Error al comprobar el fichero\n";
        perror("error");
        return -1;
    }

    if (!S_ISDIR(buf->st_mode))
    {
        cout << "El archivo especificado no es un fichero\n";
        return -1;
    }

    DIR *dir = opendir(argv[1]);
    struct dirent *ent = readdir(dir);
    int tam = 0;
    while (ent != NULL)
    {
        switch (ent->d_type)
        {
        case DT_DIR:
            printf("%s/\n", ent->d_name);
            break;
        case DT_LNK:
            char nom[250];
            readlink(ent->d_name, nom, 250);
            printf("%s->%s\n", ent->d_name, nom);
            tam += ent->d_reclen;
            break;
        case DT_REG:

            printf("%s\n", ent->d_name);
            tam += ent->d_reclen;
            break;
        default:
            break;
        }
        ent = readdir(dir);
    }
    cout << tam << '\n';
    return 0;
}