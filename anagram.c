#include <stdio.h>
#include <ctype.h> 

int main(void) {
    #define LENGTH 256
    int k, temp;
    int input1Chars[26] = { 0 }; // an array to count letters
    int input2Chars[26] = { 0 }; // an array to count letters
    char ch;


    printf("Enter the first word: "); //checks the first word
    while( (ch = getchar()) != '\n') {
        if(isalpha(ch)) { //only runs if the char is a letter
            ch = tolower(ch) - 'a'; //looks at lower string and gets a value of where a would be in the array
            input1Chars[ch]++; //adds 1 to array location
        }
    }

    printf("Enter the second word: "); //checks the second word
    while( (ch = getchar()) != '\n') {
        if(isalpha(ch)) { //only runs if the char is a letter
            ch = tolower(ch) - 'a'; //looks at lower string and gets a value of where a would be in the array
            input2Chars[ch]++; //adds 1 to array location
        }
    }

    for(k=0; k < 26; k++) { //compares the 2 input arrays to check if they are the same
        if(input1Chars[k] != input2Chars[k]) { //exits if the arrays do not match
            printf("The words are not anagrams.\n");
            return 0;
        }
    }
    printf("The words are anagrams. \n"); //if array reached the end and the words match then return true
    return 0;
}