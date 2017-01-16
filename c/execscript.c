#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    extern int errno;
    pid_t pid;
    if ((pid = fork()) < 0) {
        perror(strerror(errno));
        exit(-1);
    } else if (pid == 0) {
        if (execl("simawk", "./simawk", (char *)0) < 0) {
            perror(strerror(errno));
            exit(-1);
        }
    } else {
        if (waitpid(pid, NULL, 0) != pid) {
            perror(strerror(errno));
            exit(-1);
        }
        sleep(3);
    }
    return 0;
}
