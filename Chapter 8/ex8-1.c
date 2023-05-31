#include <stdio.h>
#include "unistd.h"
#include <fcntl.h>

/* cat using read, write, open and close rather than stdlib */
int main(int argc, char **argv)
{
    int fd, n;
    char buf[BUFSIZ];

    if (argc < 2) {
        printf("cat usage: concatenate contents of files to std output.\n");
        return -1;
    }

    while (*++argv) {
        fd = open(*argv, O_RDONLY, 0);
        if (fd == -1) {
            printf("Error: file %s not found.", *argv);
        }
        while ((n = read(fd, buf, BUFSIZ)) > 0) {
            write(1, buf, n);
        }
    }
    return 0;
}