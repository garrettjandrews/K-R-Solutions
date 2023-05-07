#include <stdio.h>

#define CUTOFF 15

int main(void) {
    int c;
    int curr = 0;
    int prior;

    while ((c = getchar()) != EOF) {
        curr++;
        if (curr == CUTOFF) {
            if (c == ' ') {
                putchar(c);
                putchar('\n');
                curr = 0;
            } 
            else if (prior == ' '){
                putchar(' ');
                putchar('\n');
                putchar(c);
                curr = 1;
            }
            else {
                putchar('-');
                putchar('\n');
                putchar(c);
                curr = 1;
            }
        }
        else {
            putchar(c);
        }
        prior = c;
    }
}