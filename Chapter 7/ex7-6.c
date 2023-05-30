#include <stdio.h>

int main(int argc, char **argv)
{
    FILE *fp1, *fp2;
    char c1, c2;
    int curr_line = 1;
    
    if (argc != 3) {
        printf("Invalid arg count.  Must enter 2 filenames.\n");
        return -1;
    }

    ++argv;
    fp1 = fopen(*argv++, "r");
    fp2 = fopen(*argv, "r");

    while (1) {
        c1 = getc(fp1);
        c2 = getc(fp2);

        if (c1 == EOF && c2 == EOF) {
            printf("Files match.\n");
            return 0;
        }

        if (c1 != c2) {
            printf("Files don't match on line %i.\n", curr_line);
            return 0;
        }

        if (c1 == '\n') {
            curr_line++;
        }
    }

}