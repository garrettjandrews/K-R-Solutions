#include <stdio.h>
#include <string.h>

// strncpy, strncat, strncmp implementation

void string_n_copy(char *s, char *t, int n) {
    // very important that the n condition is checked first, otherwise assignment occurs and then
    // n is checked.
    while ((n>0) && (*s++ = *t++)) {
        --n;
    }

    // must terminate the string with a \0
    *s = '\0';
}

void string_n_cat(char *s, char *t, int n) {
    while (*++s);
    while ((n-- > 0) && (*s++ = *t++));
}

int string_n_cmp(char *s, char *t, int n) {
    for (; *s == *t; s++, t++, n--) {
        if (*s == '\0' || n == 1) {
            return 0;
        }
    }
    return *s - *t;
}



int main(void)
{
    char s[100] = "banana ";
    char *t = "apple";
    string_n_cat(s, t, 3);
    printf("%s\n", s);

    printf("\n%i\n", string_n_cmp("apple", "application", 4));
}