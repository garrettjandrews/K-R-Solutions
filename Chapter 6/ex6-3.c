#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// takes a document and tells you all the lines where each word occurs.

#define BUFFER 100
#define MAXWORD 100
#define MAX_COUNT 100

// define structure of group
typedef struct word_counter {
    char *word;
    int lines[MAX_COUNT]; // todo: refactor to make this dynamic
    int curr_count;
} word_counter;

// forward declarations
char getch();
void ungetch(char c);
char getword(char *word, int maxlen);
int word_found(char *new_word, word_counter **wordlist);

int main(int argc, char *argv[])
{
    char word[MAXWORD];

    // initialize a double word pointer
    word_counter **wordlist = (word_counter **) malloc(sizeof(word_counter));
    word_counter **init_pointer = wordlist;
    int curr_line = 1;

    while (getword(word, MAXWORD) != EOF) {
        if (word[0] == '\n') {
            curr_line++;
            continue;
        }

        if (word_found(word, init_pointer) == -1) {
            *wordlist = (word_counter *) malloc(sizeof(word_counter));
            (*wordlist)->word = (char *) malloc(sizeof(char *));
            strcpy((*wordlist)->word, word);
            (*wordlist)->lines[0] = curr_line;
            (*wordlist)->curr_count = 1;
            ++wordlist;
        }
        else {
            (*(init_pointer + word_found(word, init_pointer)))->lines[(*(init_pointer + word_found(word, init_pointer)))->curr_count] = curr_line;
            (*(init_pointer + word_found(word, init_pointer)))->curr_count += 1;
        }
    }

    // ADD alphabetize
    //quicksort(wordlist, 0, curr_word_count-1);

    // PRINT list of groups and members
    while (*init_pointer) {
        printf("%s: ", (*init_pointer)->word);
        fflush(stdout);
        for (int i = 0; i < (*init_pointer)->curr_count; i++) {
            if (i == (*init_pointer)->curr_count - 1) {
                printf("%i.\n", (*init_pointer)->lines[i]);
            }
            else {
                printf("%i, ", (*init_pointer)->lines[i]);
            }
            fflush(stdout);
        }
        ++init_pointer;
    }
}

// function that returns -1 if no match, otherwise gives the position of the match, which can be used with pointer arithmetic
int word_found(char *new_word, word_counter **word_list)
{
    int i = 0;
    while (*word_list) {
        if (strcmp(((*word_list)->word), new_word) == 0) {
            return i;
        }
        ++word_list;
        ++i;
    }
    return -1;
}

char getword(char *word, int maxlen)
{
    char c;
    int i = 0;
    // skip over non-letters
    while ((c =  getch()) != EOF && !isalpha(c) && c != '\n');

    // we went one too far, so ungetch
    if (c == EOF) {
        return EOF;
    }
    else if (c == '\n') {
        word[0] = '\n';
        word[1] = '\0';
        return c;
    }
    else {
        ungetch(c);
    }

    // keep getting characters until we get something that isn't a letter
    while ((c = getch()) != EOF && isalpha(c)) {
        word[i++] = c;
    }
    word[i] = '\0'; // make sure to terminate string with null character

    // at this point, we got something other than a letter
    // push it back to the input
    if (c != EOF) {
        ungetch(c);
    }
    return word[0];
}

char buffer[BUFFER];
int buffer_position = 0; /* next free position in buffer */

char getch()
{
    if (buffer_position > 0) {
        return buffer[--buffer_position];
    }
    return getchar();
}

void ungetch(char c) {
    buffer[buffer_position++] = c;
}