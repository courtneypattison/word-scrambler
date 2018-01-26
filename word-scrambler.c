/* Creator: Courtney Pattison
 * Description: CIS1500 Assignment 2 Scrambled Words 
 * Due: November 29, 2015 */

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void getFilename(char *filename);
int fileExist(FILE *fp);
void processText(char *filename);
void scrambleWord(char *word, int wordLen);
void getScrambleRange(char *word, int wordLen, int *scrambleBegin, int *scrambleEnd);

int main(void)
{
    char filename[30]; 

    getFilename(filename);
    processText(filename); 
    
    return 0;
}

/* getFilename: gets filename from user
 * In: char *filename
 * Out: none
 * Post: user is asked for filename and filename is stored */
void getFilename(char *filename)
{
    printf("Enter the filename: ");
    scanf("%s", filename);

    return;
}

/* fileExist: checks if file exists  
 * In: FILE *fp
 * Out: int
 * Post: program continues or is exited */
int fileExist(FILE *fp)
{
    if (fp == NULL)
    {
        printf("Sorry, file does not exist.\n");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}

/* processText: opens file and processes text
 * In: char *filename
 * Out: none
 * Post: file is opened, text is processed, and file is closed */
void processText(char *filename)
{
    FILE *fp; 
    char word[30];
    int wordLen;
    srand(time(NULL));
 
    fp = fopen(filename, "r"); 
    fileExist(fp);

    while (fscanf(fp, "%s", word) != EOF)
    {
        wordLen = strlen(word);

        /* Scramble words that have enough letters to be scrambled */
        if (wordLen > 3)
        {
            scrambleWord(word, wordLen);
        }

        printf("%s ", word); 
    }
    printf("\n"); 

    fclose(fp);

    return;
}

/* scrambleWord: scrambles letters from a word, except for the first and last
 * In: char *word, int wordLen
 * Out: none
 * Post: words are scrambled; punctuation is preserved */
void scrambleWord(char *word, int wordLen)
{
    int i, j, k;
    int scrambleBegin, scrambleEnd, randIndex, midwordPunct;

    char unscrambledWord[30];
    char toScramble[28]; // Letters that must be scrambled
    char emptyWord[30]; // Word without toScramble characters
    const char EMPTY = ' ';

    scrambleBegin = 1; // The first letter is not scrambled
    scrambleEnd = wordLen - 2; // The last letter is not scrambled
    getScrambleRange(word, wordLen, &scrambleBegin, &scrambleEnd);

    i = 0;
    strcpy(unscrambledWord, word);
    midwordPunct = 0; // Assume no midword punctuation
    /* Don't scramble three letter words with punctuation */
    if (scrambleBegin != scrambleEnd)
    {
        for (j = scrambleBegin; j <= scrambleEnd; j++)
        {
            if (isalnum(word[j]))
            {
                /* Copy all letters that should be scrambled to an new array */
                toScramble[i] = word[j];
                /* Empty letters that should be scrambled from original array so
                 * letters from the copied array can be randomly placed into word[]*/
                word[j] = EMPTY;
                i++;
            } 
            else
            {
                midwordPunct++;
            }
        } 
        toScramble[scrambleEnd - scrambleBegin + 1 - midwordPunct] = '\0';
        strcpy(emptyWord, word);

        /* Scramble words that have enough different characters to scramble */
        if ((strlen(toScramble) == 2) && (toScramble[0]) == toScramble[1])
        {
            strcpy(word, unscrambledWord);
        }
        else if (strlen(toScramble) > 1)
        {
            do
            {
                strcpy(word, emptyWord);
                for (k = scrambleBegin; k <= scrambleEnd - midwordPunct; k++)
                {
                    /* Randomly replace empty spaces with characters from toScramble */ 
                    do
                    {
                        randIndex = ((rand() % (scrambleEnd) + 1));
                    } while (word[randIndex] != EMPTY);
                    word[randIndex] = toScramble[k - scrambleBegin];
                }
            /* Ensure the randomly replaced characters are different from before */
            } while (strcmp(unscrambledWord, word) == 0);
        }
    }

    return;
}

/* getScrambleRange: gets the scramble range
 * In: char *word, int wordLen, int *scrambleBegin, int *scrambleEnd
 * Out: none
 * Post: scrambleBegin and scrambleEnd are updated based on punctuation */
void getScrambleRange(char *word, int wordLen, int *scrambleBegin, int *scrambleEnd)
{
    int alnumIndices[30];
    int i, j, k;
    
    /* Store the indices for alphanumeric characters */
    i = 0;
    for (j = 0; j < wordLen; j++)
    {
        if (isalnum(word[j]))
        {
            alnumIndices[i] = j;
            i++;
        } 
    } 

    /* Determine when punctuation is at the beginning/end of a word and update
     * the scramble range accordingly */ 
    for (k = 0; k < wordLen; k++)
    {
        if (k < alnumIndices[0] && ispunct(word[k]))
        {
            *scrambleBegin = *scrambleBegin + 1;
        }
        if (k > alnumIndices[i - 1] && ispunct(word[k]))
        {
            *scrambleEnd = *scrambleEnd - 1;
        }
    }

    return;
}

