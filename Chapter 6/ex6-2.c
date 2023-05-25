#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// this program takes a C file as input, sorts each variable/keyword into a group where the first N letters match (N is either
// 6 by default or can be added as a user arg), then alphabetically sorts these groups and prints the result.

#define BUFFER 100
#define DEFAULT_MATCH 6
#define MAXWORD 100
#define MAXPATTERNS 500

// define structure of group
struct group {
    char pattern[MAXWORD];
    char *words[MAXPATTERNS];
    int wordcount;
};

// forward declarations
char getch();
void ungetch(char c);
char getword(char *word, int maxlen);
void handle_comment(), handle_quote();
void get_pattern(char *word, char *result, int pattern_length);
void quicksort(struct group grouplist[], int left, int right);
int result_in_list(char *result, struct group grouplist[], int curr_num_patterns);

int main(int argc, char *argv[])
{
    // determine  pattern size
    int pattern_size;
    if (argc > 1) {
        pattern_size = atoi(*++argv);
    }
    else {
        pattern_size =  DEFAULT_MATCH;
    }

    char word[MAXWORD];
    struct group grouplist[MAXPATTERNS];  // this will hold the various group structs
    int curr_pattern_count = 0;

    // this while loop will add all words to groups, at the end we have a pointer to an array of pointers to structs
    while (getword(word, MAXWORD) != EOF) {
        char result[pattern_size+1];
        get_pattern(word, result, pattern_size);

        if (result_in_list(result, grouplist, curr_pattern_count)) {
            // find the word list
            int i = 0;
            while (strcmp(grouplist[i].pattern, result) != 0) {
                ++i;
            };
            grouplist[i].words[grouplist[i].wordcount] = malloc(sizeof(char *));
            strcpy(grouplist[i].words[grouplist[i].wordcount], word);
            grouplist[i].wordcount += 1;
        }
        else {
            strcpy((grouplist[curr_pattern_count]).pattern, result);
            grouplist[curr_pattern_count].words[0] = malloc(sizeof(char *));
            strcpy(grouplist[curr_pattern_count].words[0], word);
            grouplist[curr_pattern_count].wordcount = 1;
            curr_pattern_count++;
        }
    }

    // ADD alphabetize
    quicksort(grouplist, 0, curr_pattern_count-1);

    // PRINT list of groups and members
    for (int i = 0; i < curr_pattern_count; i++) {
        printf("PATTERN: %s\n", grouplist[i].pattern);
        for (int j = 0; j < grouplist[i].wordcount; j++) {
            printf("--- Word %i: %s\n", j+1, grouplist[i].words[j]);
        }
    }
}

void quicksort(struct group grouplist[], int left, int right)
{
    int i, last;
    void swap(struct group grouplist[], int i, int j);

    if (left >= right) {
        return;
    }

    swap(grouplist, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if (strcmp(grouplist[i].pattern, grouplist[left].pattern) < 0) {
            swap(grouplist, ++last, i);
        }
    }
    swap(grouplist, left, last);
    quicksort(grouplist, left, last-1);
    quicksort(grouplist, last+1, right);
}

void swap(struct group grouplist[], int i, int j)
{
    struct group temp;
    temp = grouplist[i];
    grouplist[i] = grouplist[j];
    grouplist[j] = temp;
}

int result_in_list(char *result, struct group grouplist[], int curr_num_patterns)
{
    if (curr_num_patterns == 0) {
        return 0;
    }

    for (int i = 0; i < curr_num_patterns; i++) {
        if (strcmp(result,(grouplist[i]).pattern)==0) {
            return 1;
        }
    }
    return 0;
}

void get_pattern(char *word, char *result, int pattern_length)
{
    int i;
    for (i = 0; i < pattern_length; i++) {
        *result++ = *word++;
    }
    *result = '\0';
}

void handle_quote()
{
    char c;
    while ((c = getchar()) != EOF && c != '"');
}

void handle_comment()
{
    char old_char = '/';
    char c = getch();

    // if we don't get another slash or a star, we don't have a comment, so ungetch and return
    if (c != '/' && c != '*') {
        ungetch(c);
        return;
    }

    char prev, curr;
    prev = '/';
    curr = c;

    if (curr == '*') {
        while (1) {
            prev = curr;
            curr = getch();

            if (curr == EOF) {
                return;
            }

            if (prev ==  '*' && curr == '/') {
                return;
            }
        }
    }
    else {
        while (1) {
            curr = getch();

            if (curr == EOF) {
                return;
            }

            if (curr  == '\n') {
                return;
            }
        }
    }
}

char getword(char *word, int maxlen)
{
    char c;
    int i = 0;
    // skip over non-letters
    while ((c =  getch()) != EOF && !isalpha(c)) {
        // handle comments and quotes
        if (c == '/') handle_comment();

        // if a quote then handle that
        if (c == '"') handle_quote();
    }

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