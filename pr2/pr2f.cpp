#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_CREAT | O_RDWR, 00777);
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();
    fcntl(fd, F_GETLK, &lock);
    if (lock.l_type == F_UNLCK)
    {
        lock.l_type = F_WRLCK;
        fcntl(fd, F_SETLK, &lock);
        time_t tim = time(NULL);
        struct tm *tm = localtime(&tim);
        char buffer[1024];
        sprintf(buffer, "Hora: %d:%d\n", tm->tm_hour, tm->tm_min);
        write(fd, &buffer, strlen(buffer));
        sleep(30);
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        close(fd);
    }
    else
    {
        cout << "nope\n";
    }

    return 0;
}