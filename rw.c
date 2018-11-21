#include <stdio.h>
#define LENGTH 10

int initSquare(char rowCol[LENGTH][LENGTH]) { //initializes the array full of . characters
    int i, j;

    for(i = 0; i < 10; i++) {
        for(j =0; j < 10; j++) {
            rowCol[i][j] = '.';
        }
    }   
    return 0;
}

int printSquare(char rowCol[LENGTH][LENGTH]) { //prints out the result of the random walk
    int i, j;

    for(i = 0; i < 10; i++) {
        for(j =0; j < 10; j++) {
		    printf("%c", rowCol[i][j]);
            printf(" ");
        }
	    printf("\n");
    }   
    return 0;
}

int main(void) {
    
    int x = 0, y = 0;
    int random, seed;
    char rowCol[LENGTH][LENGTH];
    char movingLetter = 'A';


    seed = (int) time(NULL);    //set seed
    srand(seed);             //iinitlialize random seed
    random = rand();        // range betweem 0 and rand_max

    initSquare(rowCol);
    rowCol[x][y] = movingLetter;
    movingLetter++;

    while(movingLetter < 91) { //this will loop until Z is reached
        random = rand() % 4; //random number
        switch(random){
            case 0 : // Case where we go up
                if(x != 0 && rowCol[x -1][y] == '.') {
                x--;
                rowCol[x][y] = movingLetter;
                movingLetter++;
                }
            break;
            case 1 : // Case where we go down
                if(x != 9 && rowCol[x + 1][y] == '.') {
                x++;
                rowCol[x][y] = movingLetter;
                movingLetter++;
                }
            break;
            case 2 : //Case where we go left
                if(y != 0 && rowCol[x][y - 1] == '.') {
                y--;
                rowCol[x][y] = movingLetter;
                movingLetter++;
                }
            break;
            case 3 : //Case where we right
                if(y != 9 && rowCol[x][y + 1] == '.') {
                y++;
                rowCol[x][y] = movingLetter;
                movingLetter++;
                }
            break;
        }
        //if statement that ends the program if there is no possible move
        if ((x == 0 || rowCol[x - 1][y] != '.' ) && (x == 9 || rowCol[x + 1][y] != '.' ) && (y == 0 || rowCol[x][y - 1] != '.' ) && (y == 9 || rowCol[x][y + 1] != '.' )) {
            printSquare(rowCol); 
            return 0;
        }
    //printf("this ran and intLetter is: %d\n", intLetter);
    }
    printSquare(rowCol); 
return 0;
}