//
// EECS2031 team.c
//
// Program for maintaining a personal team.
//
//
// Uses a linked list to hold the team players.
//
// Author: <Your Name Goes Here>
// Student Info: <Your Student Number Goes Here>


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

//**********************************************************************
// Linked List Definitions 
//  Define your linked list node and pointer types
//  here for use throughout the file.
//
//
//   ADD STATEMENT(S) HERE

struct Player {
	char *familyName;
	char *firstName;
	char position;
	int value;
	struct Player *next;
};



//**********************************************************************
// Linked List Function Declarations
// Functions that modify the linked list.
//   Declare your linked list functions here.
//
//   ADD STATEMENT(S) HERE
int printer(struct Player *list);
int print_values(struct Player *head, int value);
//struct Player *add_to_list(struct Player *head, struct Player *currentPlayer);
struct Player *search_list(struct Player *list, struct Player *currentStudent);
struct Player *search_by_last_name(struct Player *head, char *searchName);

//**********************************************************************
// Support Function Declarations
//

void safegets(char s[], int arraySize);        // gets without buffer overflow
void familyNameDuplicate(char familyName[]);   // marker/tester friendly 
void familyNameFound(char familyName[]);       //   functions to print
void familyNameNotFound(char familyName[]);    //     messages to user
void familyNameDeleted(char familyName[]);
void printTeamEmpty(void);
void printTeamTitle(void);
void printNoPlayersWithLowerValue(int value);

//**********************************************************************
// Program-wide Constants
//

const int MAX_LENGTH = 1023;
const char NULL_CHAR = '\0';
const char NEWLINE = '\n';
const char GOALKEEPER = 'G';
const char DEFENDER = 'D';
const char MIDFIELDER = 'M';
const char STRIKER = 'S';


//**********************************************************************
// Main Program
//

int main(void)
{
	const char bannerString[]
		= "Personal Team Maintenance Program.\n\n";
	const char commandList[]
		= "Commands are I (insert), D (delete), S (search by name),\n"
		"  V (search by value), P (print), Q (quit).\n";

	// Declare linked list head.
	//   ADD STATEMENT(S) HERE TO DECLARE LINKED LIST HEAD
	struct Player *head = NULL;

	// announce start of program
	printf("%s", bannerString);
	printf("%s", commandList);

	char response;
	//char input[MAX_LENGTH + 1];
	char input[1024];

	do
	{
		printf("\nCommand?: ");
		safegets(input, MAX_LENGTH + 1);
		// Response is first char entered by user.
		// Convert to uppercase to simplify later comparisons.
		response = toupper(input[0]);

		if (response == 'I')
		{
			// Insert a player entry into the linked list.
			// Maintain the list in correct order (G, D, M, S).
			//   ADD STATEMENT(S) HERE

			// USE THE FOLLOWING PRINTF STATEMENTS WHEN PROMPTING FOR DATA:
			char family[1024];
			char *familyPoint;
			char first[1024];
			char *firstPoint;
			char position[2];
			char value[1024];

			//gets user input and assigns them to pointers 
			printf("  family name: ");
			safegets(family, 1024);
			familyPoint = malloc(strlen(family) +1);
			strcpy(familyPoint, family);

			printf("  first name: ");
			safegets(first, 1024);
			firstPoint = malloc(strlen(first) + 1);
			strcpy(firstPoint, first);

			printf("  position: ");
			safegets(position, 1024);
			printf("  value: ");
			safegets(value, 1024);

			//creates a pointer to location with enough size for player 
			struct Player *currentPlayer;
			currentPlayer = malloc(sizeof(struct Player));

			if (currentPlayer == NULL) {
				printf("Error: malloc failed in add_to_list \n");
				exit(EXIT_FAILURE);
			}

			currentPlayer->familyName = familyPoint;
			currentPlayer->firstName = firstPoint;
			currentPlayer->position = toupper(position[0]);
			currentPlayer->value = atoi(value);
			currentPlayer->next = NULL;



			if (head != NULL) {
					struct Player *tester = search_by_last_name(head, currentPlayer->familyName);
					if (tester == NULL) {
						head = search_list(head, currentPlayer);
				}
					else {
						familyNameDuplicate(currentPlayer->familyName);
					}
			}

			if (head == NULL)
			{
				head = currentPlayer;
				head->next = NULL;
			}
		
		}
		else if (response == 'D')
		{
			// Delete a player from the list.
			char searchName[1024];
			struct Player *deletePlayer;
			printf("\nEnter family name for entry to delete: ");
			safegets(searchName, 1024);
			deletePlayer = search_by_last_name(head, searchName);
			if (deletePlayer == NULL) {
				familyNameNotFound(searchName);
			}
			else {
				if (strcmp(head->familyName, searchName) == 0) {
					deletePlayer = head;
					head = head->next;
					familyNameDeleted(searchName);
					free(deletePlayer);
				}
				else {
					deletePlayer = search_by_last_name(head, searchName);
					if (deletePlayer != NULL) {
						//fix this
						struct Player *deleted = deletePlayer->next;
						deletePlayer->next = deletePlayer->next->next;
						familyNameDeleted(searchName);
						free(deleted->familyName);
						free(deleted->firstName);
						free(deleted);
					}
				}
			}
		}
		else if (response == 'S')
		{
			// Search for a player by family name.
			char searchName[1024];

			printf("\nEnter family name to search for: ");
			safegets(searchName, 1024);
			struct Player *foundPlayer;
			if (head != NULL) {
				if (strcmp(head->familyName, searchName) == 0) {
					foundPlayer = head;
					printer(foundPlayer);
				}

				else {
					foundPlayer = search_by_last_name(head, searchName);
					if (foundPlayer != NULL) {
						printer(foundPlayer->next);
					}
				}
			}
			if (head == NULL || foundPlayer == NULL) {
				familyNameNotFound(searchName);
			}
		}
		else if (response == 'V')
		{
			char valueChar[1024];
			int value;
			printf("\nEnter value: ");
			safegets(valueChar, 1024);
			value = atoi(valueChar);

			print_values(head, value);
		}
		else if (response == 'P')
		{
			struct Player *list;
			if (head == NULL) {
				printTeamEmpty();
			}
			else {
				list = head;
				printTeamTitle();
				for (; list != NULL; list = list->next) {
					printer(list);
				}
			}
		}
		else if (response == 'Q')
		{
			; // do nothing, we'll catch this case below
		}
		else
		{
			// do this if no command matched ...
			printf("\nInvalid command.\n%s\n", commandList);
		}
	} while (response != 'Q');

	struct Player *list;
	struct Player *listOld;

	list = head;
	while (list != NULL) { //frees all of the nodes then prints 
		if (list->next != NULL) {
			listOld = list;
			list = list->next;
			head = list;
			free(listOld->familyName);
			free(listOld->firstName);
			free(listOld);
		}
		else {
			free(list->familyName);
			free(list->firstName);
			free(list);
			list = NULL;
			head = NULL;
		}
	}
		list = head;
		if (head == NULL) {
			printTeamEmpty();
		}
		else {
			list = head;
			printTeamTitle();
			for (; list != NULL; list = list->next) {
				printer(list);
			}
		}


	return 0;
}

//**********************************************************************
// Support Function Definitions

// Function to get a line of input without overflowing target char array.
void safegets(char s[], int arraySize)
{
	int i = 0, maxIndex = arraySize - 1;
	char c;
	while (i < maxIndex && (c = getchar()) != NEWLINE)
	{
		s[i] = c;
		i = i + 1;
	}
	s[i] = NULL_CHAR;
}

// Function to call when user is trying to insert a family name 
// that is already in the book.
void familyNameDuplicate(char familyName[])
{
	printf("\nAn entry for <%s> is already in the team!\n"
		"New entry not entered.\n", familyName);
}

// Function to call when a player with this family name was found in the team.
void familyNameFound(char familyName[])
{
	printf("\nThe player with family name <%s> was found in the team.\n",
		familyName);
}

// Function to call when a player with this family name was not found in the team.
void familyNameNotFound(char familyName[])
{
	printf("\nThe player with family name <%s> is not in the team.\n",
		familyName);

}

// Function to call when a family name that is to be deleted
// was found in the team.
void familyNameDeleted(char familyName[])
{
	printf("\nDeleting player with family name <%s> from the team.\n",
		familyName);
}

// Function to call when printing an empty team.
void printTeamEmpty(void)
{
	printf("\nThe team is empty.\n");
}

// Function to call to print title when whole team being printed.
void printTeamTitle(void)
{
	printf("\nMy Team: \n");
}

// Function to call when no player in the team has lower or equal value to the given value
void printNoPlayersWithLowerValue(int value)
{
	printf("\nNo player(s) in the team is worth less than or equal to <%d>.\n", value);
}

//**********************************************************************
// Add your functions below this line.

int printer(struct Player *list) {
	printf("%s \n", list->familyName);
	printf("%s \n", list->firstName);
	printf("%c \n", list->position);
	printf("%d \n", list->value);
	printf("\n");
	return 0;
}

int print_values(struct Player *head, int value) { //checks for values and calls printer function if it finds a match
	int counter = 0;
	struct Player *list;
	list = head;



	for (; list != NULL; list = list->next) {
		if (list->value <= value) {
			printer(list);
			counter++;
		}

	}
	if (counter == 0) {
		printNoPlayersWithLowerValue(value);
	}
	return 0;
}

struct Player *search_by_last_name(struct Player *head, char *searchName) {
	//use for search and delete, possible value 
	struct Player *list;
	list = head;

	for (; list != NULL; list = list->next) { //loops through the linked list 
		if (head->next == NULL) {
			if (strcmp(head->familyName, searchName) == 0) { // if the last name is head it returns head 
				return head;
			}
			else {
				return NULL;
			}
		}
		if (list->next != NULL) {
			if (strcmp(list->next->familyName, searchName) == 0) { //if there is a match it returns list 
				return list;
			}
		}
	}
	return NULL;//returns null 
}

struct Player *search_list(struct Player *head, struct Player *currentPlayer) { //searches for where to insert the node and changes the next values so that it can be placed there
	struct Player *list;
	list = head;

	for (; list != NULL; list = list->next) {
		//case for G, if the current position is G it goes into this if statement
		if (currentPlayer->position == 'G') {
			if (head->position != 'G') {//if the head is not g, g will be made into the head 
				currentPlayer->next = head;
				head = currentPlayer;
				return head;
			}
			if (head->next == NULL || list->next == NULL || list->next->position != 'G') { //G is put in after all G's 
				currentPlayer->next = list->next;
				list->next = currentPlayer;
				break;
			}
		}

		//case for D
		if (currentPlayer->position == 'D') {
			if (head->position != 'G' && head->position != 'D') { //if the head is not g or d, d will be made into the head 
				currentPlayer->next = head;
				head = currentPlayer;
				return head;
			}
			if (head->next == NULL || list->next == NULL || list->next->position != 'G' && list->next->position != 'D') { //D is put in after all G's and D's
				currentPlayer->next = list->next;
				list->next = currentPlayer;
				break;
			}
		}
		//case for M
		if (currentPlayer->position == 'M') {
			if (head->position == 'S') { //if the head is S, then M will be mae into head 
				currentPlayer->next = head;
				head = currentPlayer;
				return head;
			}
			if (head->next == NULL || list->next == NULL || list->next->position != 'G' && list->next->position != 'D' && list->next->position != 'M') { //M is placed after everything except S
				currentPlayer->next = list->next;
				list->next = currentPlayer;
				break;
			}
		}

		//case for S
		if (currentPlayer->position == 'S') { 
			if (head->next == NULL || list->next == NULL) {//s is put in only if the last value or head is null 
				list->next = currentPlayer;
				break;
			}
		}

	}
	return head;
}