/*
Exercise 1-18 solution from Kernighan & Ritchie's The C Programming Language, 2nd edition.
General idea here:
1. Create character arrays to store the current line and the reversed line.
2. Read in the current line and get its length.
3. Reverse it using the reverse() function.
4. Print reversed line.
5. Clear out the reversed line by setting all elements equal to '\0', which is necessary because we need to reuse that array for future lines.
*/

#include <stdio.h>

#define MAXLINE 1000

void reverse(char from[], char to[], int maxLen); /* forward declaration of the reverse() function*/
int stringLength(char s[]);
int getLine(char s[], int maxLen);
void clearLine(char s[]);

int main(void)
{
    char currentLine[MAXLINE];
    char reversedLine[MAXLINE];
    int c, len;

    while ((len = getLine(currentLine, MAXLINE)) > 0) {
        reverse(currentLine, reversedLine, MAXLINE);
        printf("%s\n", reversedLine);
        clearLine(reversedLine);
    }
}

void reverse(char from[], char to[], int maxLen) {
    int j = 0;
    for (int i = stringLength(from)-1; i >= 0; --i) {
        to[j] = from[i];
        ++j;
    }

    to[stringLength(from)] = '\0';
}

int stringLength(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        ++i;
    }
    return i;
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

void clearLine(char s[]) {
    for (int i = 0; i < stringLength(s); ++i) {
        s[i] = '\0';
    }
}