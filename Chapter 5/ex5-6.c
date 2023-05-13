#include <stdio.h>

#define MAXLINE 1000

void reverse(char *s) {
    // copy s into t
    char t[MAXLINE];
    int i = 0;
    while (*s) {
        t[i++] = *s;
        ++s;
    }

    // terminate t and decrement i
    t[i] = '\0';
    i -= 1;

    // bring s back to the beginning
    s -= i+1;
    for (; i >= 0; i--) {
        *s = t[i];
        ++s;
    }
    *s = '\0';
}

int main(void) {
    char s[MAXLINE] = "12345";
    reverse(s);
    printf("\n%s\n", s);
}