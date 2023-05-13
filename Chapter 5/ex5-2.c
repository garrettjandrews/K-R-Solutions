#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int x);

// important note:
// the c that is returned tells you what kind of result was found, but *pn is the thing being edited
double getfloat(double *pn) {
    int c, sign;

    // skip white space
    while (isspace(c = getch())) {
        ;
    }

    // handle non-numbers
    if (!isdigit(c) && c!=EOF && c != '+' && c!= '-' && c != '.') {
        ungetch(c);
        return 0;
    }

    // if there is a leading -, then we have a negative number, else we don't
    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') { 
        c = getch();
        if (!isdigit(c)) {
            ungetch(sign == 1 ? '+' : '-');
            return 0;
        }
    }

    // read until a non digit is found
    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0'); //this mystifying line is found directly in K&R.  Ex to illustrate: 123*10 = 1230 + c
    }
    
    // check if we have a decimal
    if (c == '.') {

        // if decimal is found, continue adding on digits until a non-digit is found
        c = getch();
        for (int i = 1; isdigit(c); c = getch(), i++) {
            *pn = *pn + (c - '0') / pow(10, i);
        }
    }

    *pn *= sign;

    if (c!=EOF) {
        ungetch(c);
    }
    return c;
}

int main(void) {
    int i;
    double num[BUFSIZE];
	int val;

	for (i = 0; i < BUFSIZE && (val = getfloat(&num[i])) != EOF; i++) {
        printf("num[%d] = %f, \tvalue returned: %d (%s)\n", i, num[i], 
				val, val != 0 ? "number" : "not a number");
    }
	return 0;
}

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    }
    else {
        buf[bufp++] = c;
    }
}