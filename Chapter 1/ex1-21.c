#include <stdio.h>

#define TAB 8

int main(void)
{
    int c;
    int curr = 0;
    int entab = 0;
    int whitespace = 0;

    while ((c = getchar()) != EOF) {
        // case where we are not in a series of blanks and tabs
        if (!entab) {

            // hitting a space causes us to enter the entab state
            if (c == ' ') {
                entab = 1;
                ++whitespace;
            }

            // if we hit the newline char, then reset everything
            else if (c == '\n') {
                curr = 0;
                whitespace = 0;
                putchar(c);
            }

            // if we get anything else, then just putchar() as normal
            else {
                putchar(c);
                ++curr;
            }
        }

        // case where we have hit a blank and need to optimize chars
        else {

            // if we get another blank, take note of it and continue on
            if (c == ' ') {
                whitespace++;
                continue;
            }

            // if we hit a tab, calculate the amount of additional whitespace needed
            if (c == '\t') {
                whitespace = whitespace + (TAB - ((curr + whitespace) % TAB));
                continue;
            }

            // if we get anything else, then the entab state has ended and we must optimize
            entab = 0;
            
            int space_to_add = 0;
            while (whitespace > 0) {

                // figure out how much space a tab would add
                space_to_add = TAB - (curr % TAB);

                // if there is sufficient space, we will add a tab
                if (space_to_add >= whitespace) {
                    whitespace = whitespace - space_to_add;
                    putchar('\t');
                    curr = curr + space_to_add;
                }

                //otherwise, add a space
                //todo: optimize by adding spaces until whitespace is gone
                else {
                    putchar(' ');
                    ++curr;
                    --whitespace;
                }
            }

            //now that whitespace is done, print the character that came from the stream
            putchar(c);
            
        }
    }
}