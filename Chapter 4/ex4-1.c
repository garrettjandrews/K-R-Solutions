#include <stdio.h>

// helper function
int strLength(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        ++i;
    }
    return i+1;
}

int strrindex(char s[], char t) {

    // iterate starting at the end of s
    for (int i = strLength(s)-1; i >= 0; i--) {
        // if a match is found, return the position
        if (s[i] == t) {
            return i;
        }
    }

    // no match, so return -1
    return -1;
}

int main(void) 
{
    printf("%i\n", strrindex("Hello", 'l'));
}