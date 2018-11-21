#include <stdio.h>

int main(void) {
    #define LENGTH 256 //length of array
    int shift, i, j, temp;
    char input[LENGTH] = "";


    printf("Enter message to be encrypted: ");
    fgets( input, sizeof( input ), stdin ); //takes message input

    printf("Enter shift amount (1-25): ");
    scanf("%d", &shift); // takes in a shift amount

    if(shift > 25 || shift < 0) { // returns error message if shift is outside of the range
        printf("Invalid shift amount, shift must be between: 1-25 inclusive. \n");
	return 0;
    }

    if( (sizeof (input) / sizeof (input[0]) ) > 256) { //if the char amount is bigger than array size it returns an error
        printf("The input must be less than 256 characters \n");
        return 0;
    }

    for(i=0; i <  sizeof (input) / sizeof (input[0]); i++) { //runs for the size of input 
        temp = input[i];
        if(temp >= 97 && temp <= 122) { //shifts lower case characters
            temp += shift;
            if(temp > 122) { //goes back 26 characters to account for looping around
              temp -= 26;
            }
        input[i] = temp;
        }
        else if(temp >= 65 && temp <= 90) { //shifts upper case characters 
            temp += shift;
            if(temp > 90) { //goes back 26 characters to account for looping around
                temp -= 26; 
            }
            input[i] = temp;
        }
    } 
    for(i=0; i <  sizeof (input) / sizeof (input[0]); i++) { // prints out the shifted result
        printf("%c", input[i]);
    }
}
