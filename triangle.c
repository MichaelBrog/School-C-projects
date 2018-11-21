#include <stdio.h>
int main(void)
{
    int rows, i, j, k, rowminus, rowpluser; 
    printf("Enter the number of rows in the triangle: ");
    scanf("%d", &rows);
    if(rows > 20 || rows < 1) { //checks for valid int input
        printf("Please insert an integer between: 1-20 inclusive. \n");
        return 0;
    }
        rowminus = rows; //rowminus serves as an indicator of how many spaces we need before the first astrisk
        for(i=1; i <= rows; i++) {
            for(k=1; k < rowminus; k++) {
                printf(" ");//prints out the spaces before the first astrisk
            }
            rowminus--;//as the rows go down the spaces before the first astrisk must go down
            if(i == 1){
                printf("*\n");//prints the tip of the triangle with no spaces inside
            }
            else { //if we are not doing the tip, we are doing everything else
                printf("*");
            for(j=1; j < i + rowpluser; j++) {
                if(i < rows) printf(" "); //prings out the spaces between the astrisks
                else printf("*"); //prints out *'s instead of spaces for the last line
            }
            rowpluser++;//as the rows go down we print more spaces/astrisks inside
            printf("*\n");
            }
        }
}