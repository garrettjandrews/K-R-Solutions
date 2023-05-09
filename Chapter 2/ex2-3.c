#include <stdio.h>
#include <string.h>
#include <ctype.h>

int htoi(char s[]);
int power(int x, int y);

int main(void) {
    int i = htoi("a1fe");
    printf("%i\n", i);

    return 0;
}

int power(int x, int y) {
    int result = 1;

    while (y > 0) {
        result = result * x;
        --y;
    }

    return result;
}

int htoi(char s[]) {
    int i = 0;
    int result = 0;
    int string_length = strlen(s);

    /* check if we have a hex starting with 0x */
    if (string_length > 1 && s[0] == '0' && tolower(s[1]) == 'x') {
        string_length = string_length - 2;
        i = 2;
    }

    while (string_length > 0) {
        if (isdigit(s[i])) {
            result += (s[i]-'0') * power(16, (string_length-1));
        }
        else {
            result += (s[i] + 10 - 'a') * power(16, (string_length-1));
        }
        --string_length;
        ++i;
    }

    return result;
}