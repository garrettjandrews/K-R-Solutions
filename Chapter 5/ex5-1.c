#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int x);

int getint(int *pn) {
    int c, sign;

    // skip white space
    while (isspace(c = getch())) {
        ;
    }

    if (!isdigit(c) && c!=EOF && c != '+' && c!= '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            ungetch(sign == 1 ? '+' : '-');
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }

    *pn *= sign;

    if (c!=EOF) {
        ungetch(c);
    }
    return c;
}

int main(void) {
    int i, num[BUFSIZE];
	int val;

	for (i = 0; i < BUFSIZE && (val = getint(&num[i])) != EOF; i++)
		printf("num[%d] = %d, \tvalue returned: %d (%s)\n", i, num[i], 
				val, val != 0 ? "number" : "not a number");

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