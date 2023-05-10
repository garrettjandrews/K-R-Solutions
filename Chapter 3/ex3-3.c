#include <stdio.h>

#define BUFFER 1000

/* Write a function expand(s1, s2) that expands shorthand notations like a-z in the string s1 into the equivalent 
   complete list abc...xyz in s2.  Allow for letters of either case and digits, and be prepared to handle cases like 
   a-b-c and a-z0-9 and -a-z.  Arrange that a leading or trailing - is taken literally. */

void expand(char s1[], char s2[]) {
    int i, j;
    j = 0;

    for (i = 0; s1[i]!='\0'; i++) {
        if ((i == 0) || (s1[i+1] == '\0')) {
            s2[j++] = s1[i];
            continue;
        }

        if (s1[i] != '-') {
            s2[j++] = s1[i];
            continue;
        }

        char prior = s1[i-1];
        char next = s1[i+1];
        char curr = prior + 1;

        while (curr != next) {
            s2[j++] = curr;
            curr += 1;
        }
    }
}

int main(void) 
{
    char result[BUFFER];
    expand("a-c-g", result);
    printf("%s\n", result);
}