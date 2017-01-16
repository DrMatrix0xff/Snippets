#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define clear_buf(buf) do { \
    int i__; \
    for (i__ = 0; i__ < 1024; i__++) \
        buf[i__] = '\0'; \
} while (0)

#define string_len(buf, l) do { \
    int i__ = 0; \
    while (buf[i__] != '\0') \
    i__ += 1; \
    l = i__; \
} while (0)

char line[1024] = { 0 };

int main(int argc, char *argv[]) {
    int fd;
    int len;
    fd = open("./lele.txt", O_RDWR|O_CREAT|O_TRUNC, 0666);
    close(1);
    (void) dup(fd);
    while (fgets(line, 1024, stdin) != NULL) {
        string_len(line, len);
        write(1, line, len);
        clear_buf(line);
    }

    return 0;

}
