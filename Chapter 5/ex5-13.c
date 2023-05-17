#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN 5000
#define MAXLINES 1000
#define DEFAULT_N 10

int get_line(char *s, int lim);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines, int n);
void afree(char *p);
char *alloc(int n);
int process_args(int argc, char **argv);

static char allocbuf[MAXLEN];
static char *allocp = allocbuf;

int main(int argc, char **argv) 
{
    char *linepointer[MAXLINES];
    int nlines;
    int n = process_args(argc, argv);

    if (n < 0) {
        printf("Error.\n");
        return -1;
    }

    if ((nlines = readlines(linepointer, MAXLINES)) >= 0) {
        writelines(linepointer, nlines, n);
        return 0;
    }
    else {
        printf("Error: input too big\n");
        return -1;
    }
}

int process_args(int argc, char **argv)
{
    if (argc > 2) {
        printf("Error: too many arguments entered.\n");
        return -1;
    }
    if (argc == 1) {
        return DEFAULT_N;
    }

    // otherwise, we got a real argument
    ++argv;

    // check that the argument was long enough
    if (strlen(*argv) < 2 || (*argv)[0] != '-') {
        printf("Error: invalid argument.\n");
        return -1;
    }

    // check that the argument was valid
    int arglength = strlen(*argv);
    for (int i = 1; i < arglength; i++) {
        if (!isdigit((*argv)[i])) {
            printf("Error: must enter digits as an argument, preceded by a -.\n");
            return -1;
        }
    }

    // now that we know we have something valid, we can return the real value
    return atoi(*argv)*-1;
}

void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + MAXLEN) {
        allocp = p;
    }
}

char *alloc(int n)
{
    if (allocbuf + MAXLEN - allocp >= n) {
        allocp += n;
        return allocp - n;
    }
    else{
        return 0;
    }
}

void writelines(char *lineptr[], int nlines, int n)
{
    int i = nlines - n;

    if (i < 0) {
        i = 0;
    }

    for (; i < nlines; i ++) {
        printf("%s\n", lineptr[i]);
    }
}

int get_line(char *s, int lim) {
    int c, i;

    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c!= '\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

int readlines(char *lineptr[], int maxlines) 
{
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;

    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines == maxlines || (p = alloc(len)) == NULL) {
            return -1;
        }
        else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}