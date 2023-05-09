#include <stdio.h>

unsigned rightrot(unsigned x, int n) {
    // set up a mask to determine if the rightmost bit is 1
    unsigned mask = ~0; //1111 1111
    mask = mask << 1;   //1111 1110
    mask = ~mask;       //0000 0001

    unsigned replacement = ~0;      //1111 1111
    replacement = replacement >> 1; //0111 1111
    replacement = ~replacement;     //1000 0000

    int is_one = 0;
    while (n > 0) {
        // check if final bit of x is 1
        if ((mask & x) == 1) {
            is_one = 1;
        }

        // shift right 1
        x = x >> 1;

        // replace first bit with 1 if needed
        if (is_one) {
            x = x | replacement;
        }

        // reset is_one and decrement n
        is_one = 0;
        --n;
    }

    return x;
}

int main(void)
{
    printf("%u\n", rightrot(25, 3));
    return 0;
}