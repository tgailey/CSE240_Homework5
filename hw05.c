// READ BEFORE YOU START :
// You are given a partially completed program that creates a list of students for a school.
// Each student has the corresponding information: name, gender, class, section, and roll_number.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk failing the automated test cases.
//
// The following will be accepted as input in the following format: "name:gender:standard:roll_number:tuition_fee"
// Example Input: "Tom:M:3rd:10:2000.10" or "Elsa:F:4th:15:2700"
// Valid name: String containing alphabetical letters beginning with a capital letter
// Valid gender: Char value 'M' or 'F'
// Valid standard: String containing alpha-numeric letters beginning with a number
// Valid roll_number: Positive integer value
// Valid tuition fee: Float containing no more than 2 decimal value, for example: 1500.45 or 2000.7 or 2700
// All inputs will be a valid length and no more than the allowed number of students will be added to the list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#pragma warning(disable: 4996)
#define MAX 30 
typedef enum { male = 0, female } gender; // enumeration type gender

struct student {
	char name[30];
	gender genderValue;
	char standard[10];
	int roll_number;
	float tuition_fee;
};
int count = 0; // the number of students currently stored in the list (initialized at 0)

struct student list[MAX]; // initialize list of students

						 // forward declaration of functions
void flush();
void branching(char);
void registration(char);
int add(char*, char*, char*, int, float, struct student*); // 30 points
char* search(char*, int, struct student*); // 10 points
void display();
void save(char* fileName);
void load(char* fileName); // 10 points

int main()
{
	load("Sudent_List.txt"); // load list of students from file (if it exists)

	char ch = 'i';
	printf("Assignment 5: Array of Structs and Enum Types\n\n");
	printf("Student information\n\n");

	do
	{
		printf("Please enter your selection:\n");
		printf("\ta: add a new student to the list\n");
		printf("\ts: search for a student on the list\n");
		printf("\td: display list of students\n");
		printf("\tq: quit and save your list\n");
		ch = tolower(getchar());
		flush();
		branching(ch);
	} while (ch != 'q');

	save("Student_List.txt"); // save list of dogs to file (overwrite if it exists)
	getch();
	return 0;
}

// consume leftover '\n' characters
void flush()
{
	int c;
	do c = getchar(); while (c != '\n' && c != EOF);
}

// branch to different tasks
void branching(char c)
{
	switch (c)
	{
	case 'a':
	case 's': registration(c); break;
	case 'd': display(); break;
	case 'q': break;
	default: printf("Invalid input!\n");
	}
}

// The registration function is used to determine how much information is needed and which function to send that information to.
// It uses values that are returned from some functions to produce the correct ouput.
// There is no implementation needed here, but you should study this function and know how it works.
// It is always helpful to understand how the code works before implementing new features.
// Do not change anything in this function or you risk failing the automated test cases.
void registration(char c)
{
	char input[100];

	if (c == 'a')
	{
		printf("\nPlease enter the student's information in the following format:\n");
		printf("\tname:gender:standard:roll_number:tuition_fee\n");

		fgets(input, sizeof(input), stdin);

		// discard '\n' chars attached to input
		input[strlen(input) - 1] = '\0';

		char* name = strtok(input, ":"); // strtok used to parse string
		char* genderValueString = strtok(NULL, ":");
		char* standard = strtok(NULL, ":");
		int roll_number = atoi(strtok(NULL, ":")); // atoi used to convert string to int
		float tuition_fee = atof(strtok(NULL, ":")); // atof used to convert string to float

		int result = add(name, genderValueString, standard, roll_number, tuition_fee, list);

		if (result == 0)
			printf("\nThat student is already on the list\n\n");
		else
			printf("\nStudent added to list successfully\n\n");
	}
	else // c = 's'
	{
		printf("\nPlease enter the student's information in the following format:\n");
		printf("\tname:roll_number\n");
		fgets(input, sizeof(input), stdin);

		char* name = strtok(input, ":"); // strtok used to parse string
		int roll_number = atoi(strtok(NULL, ":")); // atoi used to convert string to int

		char* result = search(name, roll_number, list);

		if (result == NULL)
			printf("\nThat student is not on the list\n\n");
		else
			printf("\nStandard: %s\n\n", result);
	}
}

// Q1 : add (30 points)
// This function is used to insert a new student into the list.
// Your list should be sorted alphabetically by name, so you need to search for the correct index to add into your list.
// If a student already exists with the same name, then those students should be sorted by roll_number.
// Do not allow for the same student to be added to the list multiple times. (same name and same roll_number(same roll number cannot happen)).
// If the student already exists on the list, return 0. If the student is added to the list, return 1.
//
// NOTE: You must convert the string "genderValueString to an enum type and store it in the list. This will be tested.
// (You must store all of the required information correctly to pass all of the test cases)
// NOTE: You should not allow for the same student to be added twice, you will lose points if you do not account for this.
// (That means that dogs on the list are allowed to have the same name but not same roll number).
// You are not required to use pointer operations for your list but you may do so if you'd like. 
// 'list' is passed to this function for automated testing purposes only, it is global.
int add(char* name, char* genderValueString, char* standard, int roll_number, float tuition_fee, struct student* list)
{
	//To keep place in the list
	int i = 0;
	//Where the students will be added
	int spot = -1;
	//If there is no one in the list, the spot is the first part of the array
	if (count == 0) {
		spot = 0;
	}
	else {
		//If the given name is less than or equal to the first name of the list
		if (strcmp(name, list[0].name) <= 0) {
			//If the names are the same
			if (strcmp(name, list[0].name) == 0) {
				//If the given roll number is less than the roll number of the first student in the list
				if (roll_number < list[0].roll_number) {
					//Spot is the first place
					spot = 0;
				}
				//Else if the roll numbers and names are the same
				else if (roll_number == list[0].roll_number) {
					//Return zero because the student already exists
					return 0;
				}
			}
			//Else if the names are not the same
			else if (strcmp(name, list[0].name) != 0) {
				//Spot is the first spot
				spot = 0;
			}
		}
		//While a spot cannot be found
		while (spot == -1) {
			//If the name is the same or comes after
			if (strcmp(name, list[i].name) >= 0) {
				//If the name is the same
				if (strcmp(name, list[i].name) == 0) {
					//If the roll number comes after the listed roll number
					if (roll_number > list[i].roll_number) {
						//Set spot to the next space
						spot = i + 1;
					}
					//If the roll number is also the same, return 0 as student is already in the list
					else if (roll_number == list[i].roll_number) {
						return 0;
					}
				}
				//If the name is not the same, set spot to the next space
				else if (strcmp(name, list[i].name) != 0) {
					spot = i+1;
				}
			}
			//Move the spot in the list to the next space
			i++;
		}
	}
	i = count;
	//Move everything in the list after spot one spot up in the array
	while (spot != i) {
		list[i].genderValue = list[i - 1].genderValue;
		strcpy(list[i].name, list[i - 1].name);
		list[i].roll_number = list[i - 1].roll_number;
		strcpy(list[i].standard, list[i - 1].standard);
		list[i].tuition_fee = list[i - 1].tuition_fee;
		i--;
	}
	//Find the gender given to be added by comparing strings.
	gender addedGender;
	if (strcmp(genderValueString, "M") == 0) {
		addedGender = male;
	}
	else {
		addedGender = female;
	}
	//Set the lists spot value to the given values
	list[spot].genderValue = addedGender;
	strcpy(list[spot].name, name);
	list[spot].roll_number = roll_number;
	strcpy(list[spot].standard, standard);
	list[spot].tuition_fee = tuition_fee;

	//Add one to count and let the method know it has been completed successfully by returning 1
	count++;
	return 1;
}

// Q2 : search (10 points)
// This function is used to search for a student on the list and returns the standard of that student
// You will need to compare the search keys: name and roll_number, with the stored name and roll_number.
// If the student exists in the list, return a String containing the standard of the requested dog.
// If the student does not exist on the list, return NULL
char* search(char* name, int roll_number, struct student* list)
{
	int i = 0;
	//transverse the list from 0 to count (amount of students in list)
	while (i != count) {
		//If the names are the same
		if (strcmp(name, list[i].name) == 0) {
			//If the roll numbers are the same
			if (roll_number == list[i].roll_number) {
				return list[i].standard;
			}
		}
		i++;
	}
	//If no student has been found and returned, return NULL
	return NULL;
}
// This function displays the list of students and the information for each one. It is already implemented for you.
// It may be helpful to trace through this function to help you complete other sections of this assignment.
void display()
{
	char* genderValue = "Male";
	int i;
	if (count == 0)
		printf("\nThere are no students on this list!\n\n");
	else {
		for (i = 0; i < count; i++)
		{
			printf("\nName: %s\n", list[i].name);

			if (list[i].genderValue == male)
				genderValue = "Male";
			else if (list[i].genderValue == female)
				genderValue = "Female";

			printf("Standard: %s\n", list[i].standard);
			printf("Gender: %s\n", genderValue);
			printf("Roll No: %d \n", list[i].roll_number);
			printf("Tuition Fee: $ %.2f \n", list[i].tuition_fee);
		}
		printf("\n");
	}
}

// This function saves the array of structures to file. It is already implemented for you.
// You should understand how this code works so that you know how to use it for future assignments.
void save(char* fileName)
{
	FILE* file;
	int i;
	file = fopen(fileName, "wb");

	fwrite(&count, sizeof(count), 1, file);
	for (i = 0; i < count; i++)
	{
		fwrite(list[i].name, sizeof(list[i].name), 1, file);
		fwrite(list[i].standard, sizeof(list[i].standard), 1, file);
		fwrite(&list[i].genderValue, sizeof(list[i].genderValue), 1, file);
		fwrite(&list[i].roll_number, sizeof(list[i].roll_number), 1, file);
		fwrite(&list[i].tuition_fee, sizeof(list[i].tuition_fee), 1, file);
	}
	fclose(file);
}

// Q3:  Load file (10 points)
// This function loads data from file and build the the array of structures. 
// Use the save function given above as an example on how to write this function.
void load(char* fileName)
{
	FILE* file;
	int i;
	//Opens a file buffer for reading in binary mode with the given filename 
	file = fopen(fileName, "rb");

	//If the file can be found, read the items of the list
	if (file != NULL) {
		fread(&count, sizeof(count), 1, file);
		for (i = 0; i < count; i++) {
			fread(list[i].name, sizeof(list[i].name), 1, file);
			fread(list[i].standard, sizeof(list[i].standard), 1, file);
			fread(&list[i].genderValue, sizeof(list[i].genderValue), 1, file);
			fread(&list[i].roll_number, sizeof(list[i].roll_number), 1, file);
			fread(&list[i].tuition_fee, sizeof(list[i].tuition_fee), 1, file);
		}
		//Close the opened file buffer
		fclose(file);
	}
}
