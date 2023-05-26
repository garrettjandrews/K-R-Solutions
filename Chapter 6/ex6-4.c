#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// takes a document and tells you all the lines where each word occurs.

#define BUFFER 100
#define MAXWORD 100
#define MAX_COUNT 100

// define structure of group
typedef struct {
    char *word;
    int curr_count;
} word_counter;

// forward declarations
char getch();
void ungetch(char c);
char getword(char *word, int maxlen);
int word_found(char *new_word, word_counter **wordlist);

void quicksort(word_counter **wordlist, int left, int right)
{
    int i, last;
    void swap(word_counter **wordlist, int i, int j);

    if (left >= right) {
        return;
    }

    swap(wordlist, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if ((*(wordlist+i))->curr_count > (*(wordlist+left))->curr_count) {
            swap(wordlist, ++last, i);
        }
    }
    swap(wordlist, left, last);
    quicksort(wordlist, left, last-1);
    quicksort(wordlist, last+1, right);
}

void swap(word_counter **wordlist, int i, int j)
{
    word_counter *temp = *(wordlist+i);
    *(wordlist+i) = *(wordlist+j);
    *(wordlist+j) = temp;
}

int main(int argc, char *argv[])
{
    char word[MAXWORD];
    int curr_distinct_words = 0;

    // initialize a double word pointer
    word_counter **wordlist = (word_counter **) malloc(100 * sizeof(word_counter));
    word_counter **init_pointer = wordlist;

    while (getword(word, MAXWORD) != EOF) {
        if (word_found(word, init_pointer) == -1) {
            *wordlist = (word_counter *) malloc(sizeof(word_counter));
            (*wordlist)->word = (char *) malloc(sizeof(char *));
            strcpy((*wordlist)->word, word);
            (*wordlist)->curr_count = 1;
            ++wordlist;
            ++curr_distinct_words;
        }
        else {
            (*(init_pointer + word_found(word, init_pointer)))->curr_count += 1;
        }
    }

    // ADD alphabetize
    quicksort(init_pointer, 0, curr_distinct_words-1);

    // PRINT list of groups and members
    while (*init_pointer) {
        printf("%s: %i\n", (*init_pointer)->word, (*init_pointer)->curr_count);
        fflush(stdout);
        
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
    while ((c =  getch()) != EOF && !isalpha(c));

    // we went one too far, so ungetch
    if (c == EOF) {
        return EOF;
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