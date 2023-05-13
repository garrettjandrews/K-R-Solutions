#include <stdio.h>
#include <string.h>


/* Exercise 5-4. Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s,
and zero otherwise. */

int stringend(char *s, char *t) {
    if (strlen(t) > strlen(s)) {
        return 0;
    }

    s += (strlen(s)-strlen(t)-1);

    if (strcmp(s, t)) {
        return 1;
    }

    return 0;
}

int main(void) {
    printf("%s\n", stringend("Hello World!", "Hello World!!") ? "\nt was found at the end of s\n":"\nt was NOT found at the end of s\n");
}

