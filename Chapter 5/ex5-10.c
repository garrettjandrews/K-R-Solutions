#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void push(double d);
double pop(void);
double peek(void);
/* reverse Polish calculator */

int main(int argc, char *argv[])
{
    char *input;
    double op1;
    float float_input;

    while (*++argv) {
        input = *argv;
        printf("%s\n", input);
        if (!strcmp(input, "+")) {
            push(pop() + pop());
        }
        else if (!strcmp(input, "-")) {
            op1 = pop();
            push(pop() - op1);
        }
        else if (!strcmp(input, "*")) {
            push(pop() * pop());
        }
        else if (!strcmp(input, "/")) {
            op1 = pop();
            push(pop() / op1);
        }
        else {
            float_input = atof(input);
            push(float_input);
        }
    }
    printf("Result: %f\n", pop());
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