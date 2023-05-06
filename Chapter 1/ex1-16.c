#include <stdio.h>

#define MAXLINE 25

int getLine(char s[], int maxLen);
void copy(char from[], char to[]);

int main(void)
{
    int currLen = 0;
    int maxLen = 0;
    char currentLine[MAXLINE];
    char maxLine[MAXLINE];

    while ((currLen = getLine(currentLine, MAXLINE)) > 0) {
        if (currLen > maxLen) {
            maxLen = currLen;
            copy(currentLine, maxLine);
        }
    }

    if (maxLen > 0) {
        printf("The maximum length was %i.\n", maxLen);
        printf("%s\n", maxLine);
    }
}

// function that copies characters from one array to another
void copy(char from[], char to[]) {
    int i = 0;
    while (from[i] != '\0') {
        to[i] = from[i];
        ++i;
    }
}

// function that grabs all input on the current line and stops when the newline char is found
int getLine(char s[], int maxLen) {
    int c, i;
    i = 0;
    while (((c = getchar()) != '\n') && (c != EOF)) {
        if (i < maxLen) {
            s[i] = c;
        }
        else if (i == maxLen) {
            s[i] = '\0';
        }
        ++i;
    }
    return i;
}
