#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
	FILE *fp;
	FILE *fpnew;
	int shiftNum = 0;
	char FILE_NAME[1000];
	char FILE_NAME_OUT[105];
	char ch;

	if (argc < 3) { //checks for 3 parameters 
		printf("Insuficient parameters. \n");
		return 0;
	}


	//creates the path 
	strcpy(FILE_NAME, "./");
	strcat(FILE_NAME, argv[1]);
	strcpy(FILE_NAME_OUT, "./");
	strcat(FILE_NAME_OUT, argv[1]);
	strcat(FILE_NAME_OUT, ".enc");



	if (argv[2][1] > 0) {
		shiftNum = (argv[2][0] - 48) * 10 + (argv[2][1] - 48);
	}
	else {
		shiftNum = argv[2][0] - 48;
	}

	if (shiftNum > 25 || shiftNum < 0) { // returns error message if shift is outside of the range
		printf("Invalid shift amount, shift must be between: 1-25 inclusive.");
		return 0;
	}

	fp = fopen(FILE_NAME, "r");
	fpnew = fopen(FILE_NAME_OUT, "w");

	if (fp == NULL) { //checks if it can open the file 
		printf("Can't open %s\n", FILE_NAME);
		exit(EXIT_FAILURE);
	}

	while (!feof(fp)) //goes until the file is finished 
	{
		while((ch = fgetc(fp)) != '\n') {//goes until the line is finished 
			if(feof(fp)) { //if end of file leave loops
				break;
			}
			if (isalpha(ch)) {
				int temp = ch;
				if (temp >= 97 && temp <= 122) { //shifts lower case characters
					temp += shiftNum;
					if (temp > 122) { //goes back 26 characters to account for looping around
						temp -= 26;
					}
					ch = temp;
					}
				else if (temp >= 65 && temp <= 90) { //shifts upper case characters
					temp += shiftNum;
					if (temp > 90) { //goes back 26 characters to account for looping around
						temp -= 26;
					}
					ch = temp;
				}
			}

			fprintf(fpnew, "%c", ch); //prints out a character to a new file 
	    }
		if (!feof(fp)) {
			fprintf(fpnew, "\n");
		}
	}
		fclose(fp);
		fclose(fpnew);
	return 0;
}
