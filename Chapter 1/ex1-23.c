#include <stdio.h>

int main(void) {
    int open_comment_1 = 0;
    int close_comment_1 = 0;
    int open_comment_2 = 0;
    int close_comment_2 = 0;
    int c;

    while ((c = getchar()) != EOF) {

        /* if we have not yet entered into a comment*/
        if (!open_comment_1 && !open_comment_2) {
            /* check if we could potentially be entering into a comment*/
            if (c == '/') {
                open_comment_1 = 1;
                continue;
            }

            // if not entering into a comment, putchar and continue
            putchar(c);
            continue;
        }

        if (open_comment_1 && !open_comment_2) {
            if (c == '*') {
                open_comment_2 = 1;
                continue;
            }

            // if we did not hit a *, then the / was not part of a comment and therefore we must print it and the current char
            open_comment_1 = 0;
            putchar('/');
            putchar(c);
            continue;
        }

        // if we make it this far, then it is guaranteed that we will be inside a comment!
        if (!close_comment_1) {

            // if we hit a *, it's possible that we are reaching the end of the comment.
            if (c == '*'){
                close_comment_1 = 1;
                continue;
            }

            continue;
        }

        // if we make it this far, then we have potentially found the end of a comment
        if (!close_comment_2) {

            // if we foudn the end of the comment, then reset everything and go to next comment
            if (c == '/') {
                open_comment_1 = 0;
                open_comment_2 = 0;
                close_comment_1 = 0;
                continue;
            }

            // otherwise reset just close_comment_1 and keep checking 
            close_comment_1 = 0;
            putchar('*');
            putchar(c);
            continue;
        }
    }
}