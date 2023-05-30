#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int hex_to_int(char *hex) 
{
    int result = 0;
    int len = strlen(hex)-1;

    while (*hex) {
        if (isdigit(*hex)) {
            result += pow(16, len) * (*hex - '0');
        }
        else {
            result += pow(16, len) * (*hex + 10 - 'a');
        }
        ++hex;
        --len;
    }
    return result;
}

void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;
    int result, len, this_hex;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char*); *sval; sval++) {
                    putchar(*sval);
                }
                break;
            // ADDITIONAL code for the exercise
            case '%':
                putchar('%');
                break;
            case 'x':
                sval = va_arg(ap, char*);
                printf("%d", hex_to_int(sval));
        }
    }
    va_end(ap);
}

int main()
{
    // this line tests the pre-exercise functionality
    minprintf("In the year %d I ran %f kilometers in the town of %s.\n", 2022, 321.3, "Atlanta");

    // this line prints the new stuff
    minprintf("The hexadecimal ab5 is equal to %x - at least, I am 99%% sure.\n", "ab5");
}