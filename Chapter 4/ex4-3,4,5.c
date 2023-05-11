#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define MATHLIB 1

int getop(char s[]);
void push(double d);
double pop(void);
int getch(void);
void ungetch(int c);
double peek(void);
void clear(void);

/* reverse Polish calculator */

int main(void)
{
    int type;
    double op1, op2;
    int op1_int, op2_int;
    char s[MAXOP];
    int peeked = 0;
    int lib_function = 0;

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case MATHLIB:
                if (strcmp(s, "pow")) {
                    op2 = pop();
                    op1 = pop();
                    push(pow(op1, op2));
                }
                else if (strcmp(s, "exp")) {
                    push(exp(pop()));
                }
                else if (strcmp(s, "sin")) {
                    push(sin(pop()));
                }
                else {
                    printf("Invalid command");
                }
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) {
                    push(pop()/op2);
                }
                else {
                    printf("Error: zero divisor\n");
                }
                break;
            case '%':
                op2 = pop();
                op1 = pop();

                // implicit type conversion
                op1_int = op1;
                op2_int = op2;

                if ((op1 - op1_int > 0) || (op2 - op2_int > 0)) {
                    printf("Error: modulus not defined for non-integers.\n");
                }
                else{
                    push(op1_int % op2_int);
                }
                break;
            case '?':
                // new case to show top of stack without popping it
                printf("%f\n", peek());
                peeked = 1;
                break;
            case '&':
                // new case to duplicate top of stack
                op1 = pop();
                push(op1);
                push(op1);
                printf("Duplicated the top of the stack.\n");
                peeked = 1;
                break;
            case 's':
                //  's' will swap the top two elements of the stack
                op1 = pop();
                op2 = pop();

                push(op1);
                push(op2);

                printf("Swapped %f and %f.\n", op1, op2);
                peeked  = 1;
                break;
            case 'c':
                clear();
                printf("Stack cleared.\n");
                peeked = 1;
                break;
            case '\n':
                if (!peeked) {
                    printf("\t%.8g\n", pop());
                }
                peeked = 0;
                break;
            default:
                if(!lib_function) {
                    printf("error: unknown command %s\n", s);
                }
                break;
        }
    }
    return 0;
}

#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL) {
        val[sp++] = f;
    }
    else {
        printf("error: stack full\n");
        return;
    }
}

double pop(void)
{
    if (sp > 0) {
        return val[--sp];
    }
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void clear(void) {
    sp = 0;
}

double peek(void)
{
    return val[sp-1];
}

int getop(char s[]) {
    int i, c;
    char next;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    if (isalpha(c)) {
        i = 0;
        while (isalpha(s[++i] = c))
            c = getch();
        s[i-1] = '\0';
        if (c != EOF) {
            ungetch(c);
        }
        return MATHLIB;
    }

    if (!isdigit(c) && c != '.' && c != '-') {
        return c;
    }

    i = 0;
    if (c == '-') {
        c = getch();
        if (!isdigit(c) && c != '.') {
            ungetch(c);
            return '-';
        }
        ungetch(c);
    }

    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }
    return NUMBER;
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    }
    else{
        buf[bufp++] = c;
    }
}