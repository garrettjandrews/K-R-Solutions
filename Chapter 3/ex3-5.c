#include <stdio.h>
#include <math.h>

#define MAXLINE 100

void itob(int n, char s[], int b) {
    if (n == 0) {
        s[0] = 0;
        return;
    }

    int i = 0;
    int y = 0;
    int a;

    // calculate largest power of b to include
    while (pow(b, y) < n) {
        ++y;
    }

    // overcounted by one in the loop above
    y -= 1;

    // iterate down through the powers of b
    for (; y >= 0; y--) {
        a = 0;
        while ((a < (b-1)) && (((a+1)*pow(b,y)) <= n)) {
            ++a;
        }

        n -= a*pow(b,y);

        if (a <= 9) {
            s[i++] = a + '0';
        }
        else {
            s[i++] = (a-10) + 'a';
        }
    }

    s[i] = '\0';
}

int main(void)
{
    char s[MAXLINE];
    itob(81235, s, 16);
    printf("%s\n", s);
}
