#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main()
{
    umask(0132);
    open("fichy", O_CREAT, 0777);
    return 0;
}