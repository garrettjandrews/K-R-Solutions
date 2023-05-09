#include <stdio.h>

void squeeze(char s1[], char s2[]) {
    int i, j;

    for (i = j = 0; s1[i] != '\0'; i++) {
        int remove_flag = 0;
        for (int l = 0; s2[l] != '\0'; l++) {
            if (s1[i] == s2[l]) {
                remove_flag = 1;
                break;
            }
        }
        if (!remove_flag) {
            s1[j++] = s1[i];
        }
    }

    s1[j] = '\0';
}

int main(void) {
    char s[100] = "Pizza";
    squeeze(s, "z");
    printf("%s\n", s);
}