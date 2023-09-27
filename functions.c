/**
 * @file functions.c
 * @brief School Management System Functions
 *
 * This file contains the implementation of functions that provide core functionality
 * for the School Management System program.
 *
 * @details This file defines functions used to manage students, courses, and related
 * data in the School Management System. It includes functions for adding, modifying,
 * and deleting student and course records, as well as functions for generating reports
 * and performing various administrative tasks.
 *
 * @authors
 *   - Amr Mohamed Abdulzaher (amrnassareng@gmail.com)
 *   - Mohamed Ahmed Shams (mohamed.ah.shams@gmail.com)
 *
 * @date 26-09-2023
 */

#include "STD_TYPES.h"
#include "appearance.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char username[MAX_USERNAME_LENGTH+1];
static char password[MAX_PASSWORD_LENGTH+1];
static uint32 numberOfStudents = 0;
static uint8 validLogin=0;
uint8 attemptsCounter = MAX_LOGIN_ATTEMPTS;

studentData* start = NULL;	

/**
 * Main Menu
 *
 * Displays the main menu options and handles user input for the main menu.
 */
void mainMenu(void)
{
	uint8 mainMenuInput;
	while(1)	
	{
		printMainMenu();
		scanf("%hhu", &mainMenuInput);
		clearBuffer();
		
		switch (mainMenuInput)
    	 {
    	     case 1:
    	     {
    	         systemHeader();
    	         loginPanel();
				 break;
    	     }
	
    	     case 2:
    	     {
    	         aboutMenu();
    	         break;
    	     }
	
    	     case 3:
    	     {
    	        exitSystem();
				return;
    	     }
	
    	     default:
    	       break;
    	 }
	}
	return;
}
/**
 * About Menu
 *
 * Displays the "About" menu options and handles user input for the "About" menu.
 */
void aboutMenu(void)
{
	uint8 aboutMenuInput;
	while(1)
	{
    	printAboutMenu();
		
    	scanf("%hhu", &aboutMenuInput);
		clearBuffer();
		
    	switch (aboutMenuInput)
    	 {
    	    case 1:
    	    {
    	        printAboutProgram();
				getchar();
				break;
    	    }
    	     case 2:
    	     {
    	        printAboutDevelopers();
				getchar();
				break;
    	     }
			case 3: 
				return;
    	    default:
				break;
		}
	}	
}
/**
 * Login Again
 *
 * Handles login retries and informs the user about too many failed login attempts.
 */
void loginAgain(void)
{

    if (attemptsCounter > 1)
    {
		attemptsCounter--;
        printLoginFailed();
        return;
    }
    else
    {
        printTooManyLogins();
		exit(0);
    }
}
/**
 * Login Scan and Check
 *
 * Prompts the user for username and password, validates the login credentials,
 * and grants access to the admin menu upon successful login.
 *
 * @param user Pointer to store the entered username.
 * @param pass Pointer to store the entered password.
 */
void loginScanAndCheck(char *user, char *pass)
{
		printf("Username: ");
    	scanf(" %[^\n]%*c", user);
    	printf("Password: ");
    	scanf(" %[^\n]%*c", pass);
		
    	if ( 0 == strcmp(username, adminUser)  &&  0 == strcmp(password, adminPassword) )
    	{
    	    attemptsCounter=MAX_LOGIN_ATTEMPTS;
			validLogin=1U;
    	    adminMenu();
			return;
    	}
    	else
    	{
			validLogin=0;
    	    loginAgain();
    	}
}
/**
 * Login Panel
 *
 * Displays the login panel and manages the login process.
 */
void loginPanel(void)
{
	while(1)
	{
    	printLoginTitle();
    	loginScanAndCheck(username,password);
		if(validLogin)
		{
			return;
		}
	}
}
/**
 * Admin Menu
 *
 * Displays the admin menu options and handles user input for the admin menu.
 */
void adminMenu(void)
{
    uint8 adminMenuInput;
	while(1)
	{
    	printAdminMenu();
    	scanf("%hhu", &adminMenuInput);
		clearBuffer();
		
    	switch (adminMenuInput)
    	{
    	    case 1:
    	        addStudent(&start);
    	        break;
    	    case 2:
    	        editStudent(start);
    	        break;
			case 3:
				showStudentByID(start);
				break;
    	    case 4:
    	        showStudents(start);
    	        break;
			case 5:
				showStudentsByGender(start);
				break;
    	    case 6:
    	        deleteStudent(&start);
    	        break;
			case 7:
				return;
    	    case 8:
    	        exitSystem();
				break;
    	    default:
    	        break;
    	}
	}
}
/**
 * Scan and Check Student ID
 *
 * Scans and checks if the entered student ID is valid.
 *
 * @param inputID Pointer to store the entered student ID.
 * @return 1 if the ID is valid, 0 otherwise.
 */
uint8 isValidID(sint32* inputID)
{
    uint8 State = 1U;
    sint32 scanReturn;

    printf("Enter Student's ID: ");
    scanReturn = scanf("%d", inputID);
    clearBuffer();
    if (*inputID < 1 || scanReturn != 1)
    {
        printInvalidID();
        printPressEnter();
        getchar();

        State = 0;
    }

    return State; //return 1 if Valid , 0 if Invalid
}
/**
 * Check if a Name is Valid
 *
 * Validates whether a given name contains only alphabetic characters and spaces,
 * and checks if the length is within the allowed limit.
 *
 * @param name The name to be validated.
 * @return 1 if the name is valid, 0 otherwise.
 */
uint8 isValidName(const char *name)
{
    uint8 State = 1U;
    uint8 nameLength = strlen(name);

    if (nameLength < MIN_FULL_NAME_LENGTH || nameLength > MAX_FULL_NAME_LENGTH)
	{
        State = 0;
    } 
	else
	{
        while (*name)
		{
            if (!isalpha(*name) && !isspace(*name))
			{
                State = 0;
                break;
            }
            name++;
        }
    }

    return State; // Return the final State value (1 if valid, 0 if not).
}

/**
 * Check Name Validity
 *
 * Checks the validity of a student's full name and allows multiple attempts
 * within a defined limit.
 *
 * @param fullName Pointer to the full name to be checked.
 * @return 1 if a valid name is entered, 0 if the limit is reached.
 */
uint8 isValidFullName(char* fullName)
{
	uint8 State = 1U;
	uint8 tries = MAX_INVALID_INPUT_ATTEMPTS;
	
	printf("Enter Student's Full Name: ");
	
	while(1)
	{
		scanf(" %[^\n]%*c", fullName);
		if(!isValidName(fullName))
		{
			State=0;
			tries--;
			if(0 == tries)
			{
				tries = MAX_INVALID_INPUT_ATTEMPTS;
				break;
			}
			printInvalidName();
		}
		else
		{
			tries = MAX_INVALID_INPUT_ATTEMPTS;
			State=1U;
			break;
		}
	}
	return State;
}
/**
 * Check Age Validity
 *
 * Checks the validity of a student's age and allows multiple attempts
 * within a defined limit.
 *
 * @param inputAge Pointer to the entered age.
 * @return 1 if a valid age is entered, 0 if the limit is reached.
 */
uint8 isValidAge(sint8* inputAge)
{
	uint8 State = 1U;
	uint8 tries = MAX_INVALID_INPUT_ATTEMPTS;
	uint8 scanReturn;
	
	printf("Enter Student's Age: ");
	
	while (1)
    {
		scanReturn = scanf("%hhd",inputAge);
		clearBuffer();
        if(*inputAge < 0 || scanReturn != 1)
		{
			State=0;
			tries--;
			if(0 == tries)
			{
				tries=MAX_INVALID_INPUT_ATTEMPTS;
				break;
			}
			printInvalidAge();
		}
		else
		{
			tries=MAX_INVALID_INPUT_ATTEMPTS;
			State=1U;
			break;
		}
    }
	
	return State;
}
/**
 * Check Gender Validity
 *
 * Checks the validity of a student's gender (M or F) and allows multiple attempts
 * within a defined limit.
 *
 * @param inputGender Pointer to the entered gender.
 * @return 1 if a valid gender is entered, 0 if the limit is reached.
 */
uint8 isValidGender(char* inputGender)
{
	uint8 State = 1U;
	uint8 tries = MAX_INVALID_INPUT_ATTEMPTS;
	uint8 scanReturn;
	
	printf("Enter Student's Gender [M or F]: ");
	
	while(1)
	{
		scanReturn= scanf(" %c", inputGender);
		clearBuffer();
		*inputGender = toupper(*inputGender);
		if(('M' == *inputGender || 'F' == *inputGender) && 1 == scanReturn)
		{
			tries = MAX_INVALID_INPUT_ATTEMPTS;
			State=1U;
			break;
		}
		else
		{
			State=0;
			tries--;
			if(0 == tries)
			{
				tries = MAX_INVALID_INPUT_ATTEMPTS;
				break;
			}
			printInvalidGender();
		}
	}
	
	return State;
}
/**
 * Check GPA Validity
 *
 * Checks the validity of a student's GPA and allows multiple attempts
 * within a defined limit.
 *
 * @param inputGPA Pointer to the entered GPA.
 * @return 1 if a valid GPA is entered, 0 if the limit is reached.
 */
uint8 isValidGPA(f32* inputGPA)
{
	uint8 State = 1U;
	uint8 tries = MAX_INVALID_INPUT_ATTEMPTS;
	uint8 scanReturn;
	
	printf("Enter Student's GPA [Max. %g]: ", MAX_GRADE);
	
	while (1)
    {	
		scanReturn = scanf("%f",inputGPA);
		clearBuffer();	
        if(*inputGPA < 0.0f || *inputGPA > MAX_GRADE || scanReturn != 1)
		{
			State=0;
			tries--;
			if(0 == tries)
			{
				tries=MAX_INVALID_INPUT_ATTEMPTS;
				break;
			}
			printInvalidGPA();
		}
		else
		{
			tries=MAX_INVALID_INPUT_ATTEMPTS;
			State=1U;
			break;
		}
    }
	
	return State;
}
/**
 * Collect and Validate Student Information
 *
 * This function collects and validates various pieces of student information,
 * such as full name, age, gender, and GPA, and assigns them to a studentData structure.
 *
 * @param newStudent Pointer to the studentData structure where the information will be stored.
 * @return 1 if all information is successfully collected and validated, 0 otherwise.
 */
uint8 collectInfo(studentData* newStudent)
{
    uint8 State = 1U;
    char fullName[MAX_FULL_NAME_LENGTH + 1];
    sint8 inputAge;
    char inputGender;
    f32 inputGPA;
	
    do
    {
        // Prompt the user for the student's full name and validate it.
        if (!isValidFullName(fullName))
        {
			State=0;
            break; // if not valid then break the loop to return from the function
        }

        // Prompt the user for the student's age and validate it.
        if (!isValidAge(&inputAge))
        {
			State=0;
            break;
        }

        // Prompt the user for the student's gender and validate it.
        if (!isValidGender(&inputGender))
        {
			State = 0;
            break;
        }

        // Prompt the user for the student's GPA and validate it.
        if (!isValidGPA(&inputGPA))
        {
			State = 0;
            break;
        }
        // If all inputs are valid, assign the data to the newStudent info
        State = 1U;
        strcpy(newStudent->name, fullName);
        newStudent->age = inputAge;
        (inputGender == 'M') ? strcpy(newStudent->gender, "Male") : strcpy(newStudent->gender, "Female");
        newStudent->gpa = inputGPA;

    } while (0);

    // Return the state of data collection and validation (1 for success, 0 for failure).
    return State;
}
/**
 * Check if Student Exists
 *
 * Checks if a student with the given ID already exists in the list.
 *
 * @param start Pointer to the starting node of the student list.
 * @param id Student ID to check for.
 * @return 1 if the student exists, 0 otherwise.
 */
uint8 duplicateStudent(studentData* start, sint32 id)
{
    studentData* current = start;
	uint8 State=0;
    
    while (current != NULL)
    {
        if (id == current->id)
        {
            State= 1U; // Student with the same ID exists.
        }
        current = current->link;
    }
    
    return State; // Student does not exist.
}

/**
 * Insert Student at End
 *
 * Inserts a new student at the end of the student list.
 *
 * @param start Pointer to the starting node of the student list.
 * @param newStudent Pointer to the new student to be inserted.
 */
void insertStudentAtEnd(studentData** start, studentData* newStudent)
{
    if (*start == NULL)
    {
        // If the list is empty, make the new student the first node.
        *start = newStudent;
    }
    else
    {
        studentData* current = *start;
        
        while (current->link != NULL)
        {
            current = current->link;
        }
        
        current->link = newStudent; // Insert the new student at the end.
    }
}
/**
 * Add Student
 *
 * Allows the user to add a new student to the system, including validating student ID
 * and collecting student information.
 *
 * @param start Pointer to the starting node of the student list.
 */
void addStudent(studentData** start)
{
    sint32 inputID;

    printTitle("              Add Student\n");

    if (!isValidID(&inputID))
    {
        return;
    }

    // Check if the student with the same ID already exists
    if (duplicateStudent(*start, inputID))
    {
        printAlreadyAdded();
    }
    else
    {
        studentData* newStudent = (studentData*)malloc(sizeof(studentData));
        if (newStudent == NULL)
        {
            printFailure();
			printPressEnter();
    		getchar();
            return;
        }
        
        newStudent->id = inputID;

        if (!collectInfo(newStudent))
        {
            printFailure();
            free(newStudent);
			printPressEnter();
    		getchar();
            return;
        }

        newStudent->link = NULL;

        // Insert the new student at the end of the list
        insertStudentAtEnd(start, newStudent);
        numberOfStudents++;
        printAdded();
    }

    printPressEnter();
    getchar();
}
/**
 * Edit Student's Information
 *
 * Allows the user to edit a student's information based on their ID.
 *
 * @param start Pointer to the starting node of the student list.
 */
void editStudent(studentData* start)
{
    sint32 inputID;
    studentData* student = start;

    printTitle("          Edit Student's Info\n");

    // Check if the provided ID is valid, return if it's not.
    if (!isValidID(&inputID))
    {
        return;
    }

    // Iterate through the list of students.
    while (student != NULL)
    {
        // Check if the current student's ID matches the input ID.
        if (inputID == student->id)
        {
            // Try to collect and update the student's information.
            if (collectInfo(student))
            {
                //if information is updated.
                printEdited();
            }
            else
            {
                //if information collection fails.
                printFailure();
            }
            printPressEnter();
            getchar();
            return;
        }
        student = student->link;
    }

    // If no student with the specified ID is found, display a message.
    printNotFoundID();
    // Wait for user confirmation.
    printPressEnter();
    getchar();
}
/**
 * Show Students List
 *
 * Displays a list of all students in the system.
 *
 * @param start Pointer to the starting node of the student list.
 */
void showStudents(studentData* start)
{
	studentData* student = start;
	
    printTitle("             Students List\n");
	
    // Check if there are any students in the system.
    if (numberOfStudents > 0)
    {
        printNumberOfStudents();
		
        // Iterate through the list of students.
        while (NULL != student)
        {
            // Check if valid student
            if (student->id > 0)
            {
                // Display the student information
                printStudents(student);
            }
            student = student->link;
        }
        printLine();
    }
    else
    {
        printf("NO STUDENTS ADDED YET!\n");
    }
    printPressEnter();
    getchar();
}

/**
 * Show Students List by Gender
 *
 * Displays a list of students in the system based on their gender (M or F).
 *
 * @param start Pointer to the starting node of the student list.
 */
void showStudentsByGender(studentData* start)
{
    char inputGender;
    uint8 foundGender = 0;
    studentData* student = start;
    
    printTitle("        Students List By Gender\n");
	printNumberOfStudents();
	
    // Check if there are no students added.
    if (numberOfStudents == 0)
    {
        printf("NO STUDENTS ADDED YET!\n");
        printPressEnter();
        getchar();
        return;
    }
		
    // Get a valid gender input from the user, return if it's invalid.
    if (!isValidGender(&inputGender))
    {
        printPressEnter();
        getchar();
        return;
    }
	
	printLine();
	
    // Iterate through the list of students.
    while (student != NULL)
    {
        // Check if the student's gender matches the input gender.
        if (student->id > 0 &&  toupper(student->gender[0]) == inputGender)
        {
            foundGender = 1;
            printStudentsByGender(student);
        }
        student = student->link;
    }

    // If no students of the specified gender were found, display a message.
    if (!foundGender)
    {
        printf("No %s Students Added Yet!\n", ('M' == inputGender) ? "Male" : "Female");
    }

    printLine();
    printPressEnter();
    getchar();
}

/**
 * Show Student Information by ID
 *
 * Allows the user to search for a student by their ID and displays the student's
 * information if found.
 *
 * @param start Pointer to the starting node of the student list.
 */
void showStudentByID(studentData* start)
{
    sint32 inputID;
    uint8 found = 0;
    studentData* student = start;

    printTitle("              Search by ID\n");
    printNumberOfStudents();

    // Prompt the user for a valid student ID.
    if (!isValidID(&inputID))
    {
        return;
    }

    // Iterate through the list of students to find the matching ID.
    while (NULL != student)
    {
        if (inputID == student->id)
        {
			//if found
            printTitle("             Student's Info\n");
            printStudentInfo(student);
            printPressEnter();
            getchar();
            return;
        }
        student = student->link;
    }
    // If the student with the specified ID is not found
    printInfoNotFound();
    printPressEnter();
    getchar();
}
/**
 * Delete Student Information
 *
 * Allows the user to delete a student's information from the system based on their ID.
 *
 * @param start Pointer to the starting node of the student list.
 */
void deleteStudent(studentData** start)
{
    sint32 inputID;
	
    printTitle("          Delete Student's Info\n");
	
    // Validate the input ID, and return if it's not valid.
    if (!isValidID(&inputID))
    {
        return;
    }
	
    studentData* student = *start;
    studentData* prevStudent = NULL;

    while (student != NULL)
    {
        if (inputID == student->id)
        {
            // If the input ID matches a student's ID, remove the student from the list.
            if (prevStudent == NULL)
            {
                // If the student to be deleted is the first one, update the start pointer.
                *start = student->link;
            }
            else
            {
                // If the student to be deleted is not the first one, update the previous student's link.
                prevStudent->link = student->link;
            }
            free(student);
            numberOfStudents--;
            printDeleted();
            break;
        }
        prevStudent = student;
        student = student->link;
    }

    if (student == NULL)
    {
        // If the loop finishes without finding the student, print a message indicating no match.
        printAlreadyEmpty();
    }
    printPressEnter();
    getchar();
}
/**
 * Exit System
 *
 * Frees memory and exits the program gracefully.
 */
void exitSystem(void)
{
	free_Students(start);
    printExiting();
	exit(0);
}
/**
 * Free Students
 *
 * Frees the allocated memory for student data.
 *
 * @param start Pointer to the starting node of the student list.
 */
void free_Students(studentData* start)
{
	studentData* currentNode = start;
    while (NULL != currentNode)
    {
        studentData* previousNode = currentNode;
        currentNode = currentNode->link;
        free(previousNode);
    }
}

