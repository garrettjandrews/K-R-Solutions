#include <stdio.h>

#define TAB 8

// tab - (count % tab)

void insertSpaces(int numSpaces);

int main(void)
{
    int c;
    int curr = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            putchar('\n');
            curr = 0;
        }
        else {
            if (c == '\t') {
                insertSpaces(TAB - (curr % TAB));
                curr = curr + (TAB - (curr % TAB));
            }
            else {
                putchar(c);
                ++curr;
            }
        }
    }
}

void insertSpaces(int numSpaces) {
    for (int i = 0; i < numSpaces; ++i) {
        putchar(' ');
    }
}