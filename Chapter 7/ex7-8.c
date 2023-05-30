#include <stdio.h>

int main(int argc, char **argv)
{
    int curr_page = 1;
    char c;
    FILE *fp;

    if (argc < 2) {
        printf("You must provide a set of files!\n");
        return  -1;
    }

    while (*++argv) {
        fp = fopen(*argv, "r");
        printf("\n  %s  Page: %i  \n", *argv, curr_page);
        while ((c = getc(fp)) != EOF) {
            putchar(c);
        }
        putchar('\f');
        curr_page++;
    }
}