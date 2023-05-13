#include <stdio.h>

void stringcat(char *s, char *t);

int main(void)
{
    char s[100] = "My name is... ";
    char *t = "Garrett\n";
    stringcat(s, t);
    printf("%s\n", s);
}

void stringcat(char *s, char *t) {
    // advance s until null char found
    while (*++s);

    // copy t onto the end
    while ((*s++ = *t++));
}