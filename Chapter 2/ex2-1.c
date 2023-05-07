#include <stdio.h>
#include <limits.h>
#include <float.h>

// char, short, int, long, both unsigned and signed

int power(int x, int y) {
    int res=1;
    while (y > 0) {
        res *= x;
        --y;
    }
    return res;
}

long longpower(long x, long y) {
    long res=1;
    while (y > 0) {
        res *= x;
        --y;
    }
    return res;
}

int main(void) {
    printf("\n");
    printf("### Printing ranges from standard headers. ###\n");
    printf("Unsigned Char range: %i to %i.\n", 0, UCHAR_MAX);
    printf("Signed Char range: %i to %i.\n", SCHAR_MIN, SCHAR_MAX);
    printf("Unsigned Short range: %i to %i.\n", 0, USHRT_MAX);
    printf("Signed Short range: %i to %i.\n", SHRT_MIN, SHRT_MAX);
    printf("Unsigned Int range: %i to %u.\n", 0, UINT_MAX);
    printf("Signed Int range: %i to %i.\n", INT_MIN, INT_MAX);
    printf("Unsigned Long range: %i to %li.\n", 0, ULONG_MAX);
    printf("Signed Long range: %li to %li.\n", LONG_MIN, LONG_MAX);

    printf("\n");
    printf("### Printing ranges from computation. ###\n");
    printf("Unsigned Char range: %i to %i.\n", 0, power(2, 8)-1);
    printf("Signed Char range: %i to %i.\n", -power(2, 7), power(2, 7)-1);
    printf("Unsigned Short range: %i to %i.\n", 0, power(2, 16)-1);
    printf("Signed Short range: %i to %i.\n", -power(2, 15), power(2, 15)-1);
    printf("Unsigned Int range: %i to %u.\n", 0, power(2, 16)-1);
    printf("Signed Int range: %i to %i.\n", -power(2, 16), power(2, 16)-1);
    printf("Unsigned Long range: %i to %li.\n", 0, longpower(2, 32)-1);
    printf("Signed Long range: %li to %li.\n", -longpower(2, 31), longpower(2, 31)-1);
}