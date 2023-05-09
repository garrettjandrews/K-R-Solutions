#include <stdio.h>

// 110|010|100
// 111|100|100

unsigned invert(unsigned x, int p, int n) {
    // start by creating a mask like // 001110000 where the 1s are n long and in pos p
    unsigned mask = ~0; //1111 1111
    mask = mask << n;   //1111 1000
    mask = ~mask;       //0000 0111
    mask = mask << (p-n+1);   //0111 0000

    return x ^ mask;
}

int main(void)
{
    printf("%u\n", invert(100, 3, 2));
    return 0;
}