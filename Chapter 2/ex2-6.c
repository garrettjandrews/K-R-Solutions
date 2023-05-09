#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    if (n == 0) {
        return x;
    }

    unsigned mask = ~0;
    mask = mask << n;
    mask = ~mask;

    y = y & mask;
    y = y << p;
    mask = mask << p;
    mask = ~mask;

    x = x & mask;

    x = x | y;

    return x;
}

int main(void) {
    
    return 0;
}