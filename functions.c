#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STD_TYPES.h"
#include "appearance.h"
#include "functions.h"


static char username[MAX_USERNAME_LENGTH+1];
static char password[MAX_PASSWORD_LENGTH+1];
static uint32 numberOfStudents = 0;
static uint8 validLogin=0;

uint8 attemptsCounter = MAX_LOGIN_ATTEMPTS;

studentData* start = NULL;

void mainMenu(void)
{
	uint8 mainMenuInput;
	while(1)	
	{
		printMainMenu();
		scanf("%hhu", &mainMenuInput);
		while (getchar() != '\n');
		
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
void aboutMenu(void)
{
	uint8 aboutMenuInput;
	while(1)
	{
    	printAboutMenu();
		
    	scanf("%hhu", &aboutMenuInput);
		while (getchar() != '\n');
		
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

void loginScanAndCheck(char *user, char *pass)
{
		printf("Username: ");
    	scanf(" %[^\n]%*c", user);
    	printf("Password: ");
    	scanf(" %[^\n]%*c", pass);
		
    	if ( 0 == strcmp(username, adminUser)  &&  0 == strcmp(password, adminPassword) )
    	{
    	    attemptsCounter=4;
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

void adminMenu(void)
{
    uint8 adminMenuInput;
	while(1)
	{
    	printAdminMenu();
    	scanf("%hhu", &adminMenuInput);
		while (getchar() != '\n');
		
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
    	        deleteStudent(&start);
    	        break;
			case 6:
				return;
    	    case 7:
    	        exitSystem();
				break;
    	    default:
    	        break;
    	}
	}
}
uint8 scanID(sint32* inputID)
{
	uint8 validiationState = 1;
	sint32 scanReturn;
	
	printf("Enter Student's ID: ");
	scanReturn= scanf("%d", inputID);
	while (getchar() != '\n');
	
    if (*inputID < 1 || scanReturn != 1)
    {
		printInvalidID();
        getchar();
        validiationState = 0;
    }
	
	return validiationState;
}

f32 scanGPA(void)
{
	while (1)
    {
		f32 inputGPA;
		sint32 scanReturn;
        scanReturn = scanf("%f", &inputGPA);
		while (getchar() != '\n');
        if(inputGPA < 0.0f || inputGPA > MAX_GRADE || scanReturn != 1)
		{
			printInvalidGPA();
		}
		else
		{
			return inputGPA;
		}
    }
}

void addInfo(studentData* newStudent)
{
	printf("Enter Student's Full Name: ");
    scanf(" %[^\n]%*c", newStudent->name);
    printf("Enter Student's GPA [Max. %g]: ", MAX_GRADE);
    newStudent->gpa = scanGPA();
}

void addStudent(studentData** start)
{
    sint32 inputID;
	
	printTitle("           Add Student\n");
	
	if(!scanID(&inputID))
	{
		return;
	}
	
	studentData* current= *start;
	while(current != NULL)
	{
		if(current->id == inputID)
		{
			printAlreadyAdded();
			getchar();
        	return;
		}
		current = current->link;
	}
	
	studentData* newStudent = (studentData*)malloc(sizeof(studentData));
	newStudent->id=inputID;
	addInfo(newStudent);
	newStudent->link = *start;
    *start = newStudent;
	numberOfStudents++;
	printAdded();
    getchar();
	return;
}

void editStudent(studentData* start)
{
    sint32 inputID;
	
	printTitle("       Edit Student's Info\n");
	
    if(!scanID(&inputID))
	{
		return;
	}
	
	uint8 found = 0;
    studentData* student = start;

    while (student != NULL)
    {
        if (student->id == inputID)
        {
            addInfo(student);
			printEdited();
            found = 1;
            break;
        }
        student = student->link;
    }

    if (!found)
    {
		printNotFoundID();
    }

    getchar();
	return;
}



void showStudents(studentData* start)
{
	printTitle("          Students List\n");
    
    if (numberOfStudents > 0)
    {
        studentData* student = start;
        
        while (student != NULL)
        {
            if (student->id>0)
            {
				textNormal_B();
                printf("Name:\033[0m %s [\e[1mID:\033[0m%hhu]\n", student->name, student->id);
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

void showStudentByID(studentData* start)
{
	sint32 inputID;
	
	printTitle("           Search by ID\n");
	
    if(!scanID(&inputID))
	{
		return;
	}
	
    uint8 found = 0;
    studentData* student = start;
	
	while (student != NULL)
    {
        if (student->id == inputID)
        {
			printTitle("          Student's Info\n");
			printStudentInfo(student);
			printPressEnter();
			getchar();
			return;
        }
        student = student->link;
    }
	
	printInfoNotFound();
    getchar();
}

void deleteStudent(studentData** start)
{
    sint32 inputID;
	
	printTitle("       Delete Student's Info\n");
	
	if(!scanID(&inputID))
	{
		return;
	}
	
    studentData* student = *start;
	studentData* prevStudent= NULL;

    while (student != NULL)
    {
		if (student->id == inputID)
       	{
			if(NULL == prevStudent)
			{
				*start= student->link;
				
			}
			else
			{
				prevStudent->link= student->link;
			}
       	    free(student);
			numberOfStudents--;
			printDeleted();
			getchar();
			return;
       	}
       	prevStudent = student;
		student= student->link;
    }
	printAlreadyEmpty();
    getchar();
}


void exitSystem(void)
{
	free_Students(start);
    printExiting();
	exit(0);
}

void free_Students(studentData* start)
{
	studentData* currentNode = start;
    while (currentNode != NULL)
    {
        studentData* previousNode = currentNode;
        currentNode = currentNode->link;
        free(previousNode);
    }
}

