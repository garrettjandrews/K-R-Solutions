#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char **argv)
{
    int c;

    while ((c = getchar()) != EOF) {
        if (strcmp(*argv,"./upper")==0) {
            putchar(toupper(c));
        }
        else {
            putchar(tolower(c));
        }
    }

    return 0;
}