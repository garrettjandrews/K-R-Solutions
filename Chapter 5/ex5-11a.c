#include <stdio.h>
#include <stdlib.h>

// detab
// how to use (using clang compiler on mac):
// run "clang ex5-11a.c -o detab"
// next run "./detab a b c...>"
// enter lines with tabs

// I think this solution is inelegant, but it gets the job done

#define DEFAULT 8

void insertSpaces(int n) {
    int i = 0;
    while (i < n) {
        putchar(' ');
        ++i;
    }
}

int main(int argc, char **argv)
{
    int c;
    int curr = 0;
    int args_exhausted = 0;

    // increment argv to the first real argument
    ++argv;

    while ((c = getchar()) != EOF) {

        // always check if nothing was passed in the arg list
        if (argc == 1) {
            args_exhausted = 1;
        }

        // if we hit a new line, enter the new line character and reset curr to 0
        if (c == '\n') {
            putchar('\n');
            curr = 0;
            args_exhausted = 0;
            argv -= (argc-1);
            continue;
        }

        // if args are exhausted, use detab as normal
        if (args_exhausted) {
            if (c == '\t') {
                insertSpaces(DEFAULT - (curr % DEFAULT));
                curr = curr + (DEFAULT - (curr % DEFAULT));
            }
            else {
                putchar(c);
                ++curr;
            }
        }

        // otherwise we have to look through args until we find one we can use
        else {
            while (curr >= atoi(*argv)) {
                ++argv;
                if (!(*argv)) {
                    args_exhausted = 1;
                    break;
                }
            }

            // it is possible that we ran out of argumetns without realizing
            if (args_exhausted) {
                if (c == '\t') {
                    insertSpaces(DEFAULT - (curr % DEFAULT));
                    curr = curr + (DEFAULT - (curr % DEFAULT));
                }
                else {
                    putchar(c);
                    ++curr;
                }
                continue;
            }

            if (c == '\t') {
                insertSpaces(atoi(*argv) - curr);
                curr += (atoi(*argv) - curr);
            }
            else {
                putchar(c);
                ++curr;
            }
        }
    }
}