#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000
#define MAXLEN 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void q_sort(void *v[], int left, int right, int(*comp)(void*, void*, int), int reverse);
int numcmp(char*, char*, int reverse);
int string_compare(char *s, char *t, int reverse);
char *alloc(int n);
int get_line(char *s, int lim);

static char allocbuf[MAXLEN];
static char *allocp = allocbuf;

int main(int argc, char **argv)
{
    int nlines;
    int numeric = 0; //1 if numeric sort
    int reverse = 0;  //1 if reverse sort

    // use a loop to check args
    for(int arg_counter = 1; arg_counter < argc; arg_counter++){
        if (!strcmp(argv[arg_counter], "-n")) {
            numeric = 1;
        }
        if (!strcmp(argv[arg_counter], "-r")) {
            reverse = 1;
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        q_sort((void **) lineptr, 0, nlines-1, (int (*)(void*,void*,int))(numeric ? numcmp : string_compare), reverse);
        writelines(lineptr, nlines);
        return 0;
    }
    else {
        printf("Input too big to sort.\n");
        return 1;
    }

}

void q_sort(void *v[], int left, int right, int(*comp)(void*, void*, int), int reverse) {
    int i, last;
    void swapp(void *v[], int, int);

    if (left >= right)
        return;
    swapp(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if ((*comp)(v[i], v[left], reverse)<0) {
            swapp(v, ++last, i);
        }
    }
    swapp(v, left, last);
    q_sort(v, left, last-1, comp, reverse);
    q_sort(v, last+1, right, comp, reverse);
}

int numcmp(char *s1, char *s2, int reverse) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) {
        return reverse ? 1 : -1;
    }
    else if (v1 > v2) {
        return reverse ? -1 : 1;
    }
    else {
        return 0;
    }
}

void swapp(void *v[], int i, int j) {
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int string_compare(char *s, char *t, int reverse) {
    for (; *s == *t; s++, t++) {
        if (*s == '\0') {
            return 0;
        }
    }
    return reverse ? *t - *s : *s - *t;
}

void writelines(char *lineptr[], int nlines)
{
    for (int i = 0; i < nlines; i ++) {
        printf("%s\n", lineptr[i]);
    }
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