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
uint8 scanID(sint32* inputID)
{
	uint8 State = 1;
	sint32 scanReturn;
	
	printf("Enter Student's ID: ");
	scanReturn= scanf("%d", inputID);
	while (getchar() != '\n');
	
    if (*inputID < 1 || 1 != scanReturn)
    {
		printInvalidID();
		printPressEnter();
        getchar();
        State = 0;
    }
	
	return State;
}

uint8 isValidName(const char *name)
{
	uint8 State=1;
	uint8 nameLength= strlen(name);
    while (*name)
	{
    	if ((!isalpha(*name) && !isspace(*name))||nameLength>60)
		{
			State=0;
    	    break;
    	}
    	name++;
    }
    return State;;
}
uint8 Check_Name(char* fullName)
{
	uint8 State = 1U;
	uint8 tries = MAX_INVALID_INPUT_ATTEMPTS;
	while(1)
	{
		if(!isValidName(fullName))
		{
			State=0;
			tries--;
			if(tries == 0)
			{
				tries = MAX_INVALID_INPUT_ATTEMPTS;
				break;
			}
			printInvalidName();
			scanf(" %[^\n]%*c", fullName);
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

uint8 Check_Age(sint8* inputAge,uint8* scanReturn)
{
	uint8 State = 1U;
	uint8 tries = MAX_INVALID_INPUT_ATTEMPTS;
	
	while (1)
    {		
        if(*inputAge < 0 || *scanReturn != 1)
		{
			State=0;
			tries--;
			if(tries == 0)
			{
				tries=MAX_INVALID_INPUT_ATTEMPTS;
				break;
			}
			printInvalidAge();
			*scanReturn = scanf("%hhd",inputAge);
			while (getchar() != '\n');
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

uint8 Check_Gender(char* inputGender,uint8* scanReturn)
{
	uint8 State = 1U;
	uint8 tries = MAX_INVALID_INPUT_ATTEMPTS;
	while(1)
	{
		if(('M' == *inputGender || 'F' == *inputGender) && 1 == *scanReturn  )
		{
			tries = MAX_INVALID_INPUT_ATTEMPTS;
			State=1U;
			break;
		}
		else
		{
			State=0;
			tries--;
			if(tries == 0)
			{
				tries = MAX_INVALID_INPUT_ATTEMPTS;
				break;
			}
			printInvalidGender();
			*scanReturn= scanf(" %c", inputGender);
			while (getchar() != '\n');
			*inputGender= toupper(*inputGender);
		}
	}
	return State;
}

uint8 Check_GPA(f32* inputGPA,uint8* scanReturn)
{
	uint8 State = 1U;
	uint8 tries = MAX_INVALID_INPUT_ATTEMPTS;
	while (1)
    {		
        if(*inputGPA < 0.0f || *inputGPA > MAX_GRADE || *scanReturn != 1)
		{
			State=0;
			tries--;
			if(tries == 0)
			{
				tries=MAX_INVALID_INPUT_ATTEMPTS;
				break;
			}
			printInvalidGPA();
			*scanReturn = scanf("%f",inputGPA);
			while (getchar() != '\n');
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

uint8 Scan_Check_Info(studentData* newStudent)
{
	uint8 State=1U;
	uint8 scanReturn;
	do
	{
		
		//SCAN AND CHECK NAME
		char fullName[MAX_FULL_NAME_LENGTH+1];
		printf("Enter Student's Full Name: ");
		scanf(" %[^\n]%*c", fullName);
		State = Check_Name(fullName);
		if(0 == State)
		{
			break;
		}
		
		//SCAN AND CHECK AGE
		sint8 inputAge;
		printf("Enter Student's Age: ");
		scanReturn = scanf("%hhd",&inputAge);
		while (getchar() != '\n');
    	State = Check_Age(&inputAge,&scanReturn);
		if(0 == State)
		{
			break;
		}
		
		//SCAN AND CHECK GENDER
		char inputGender;
		printf("Enter Student's Gender [M or F]: ");
		scanReturn = scanf(" %c", &inputGender);
		while (getchar() != '\n');
		inputGender= toupper(inputGender);
    	State = Check_Gender(&inputGender,&scanReturn);
		if(0 == State)
		{
			break;
		}
		
		//SCAN AND CHECK GPA
		f32 inputGPA;
		printf("Enter Student's GPA [Max. %g]: ", MAX_GRADE);
		scanReturn= scanf("%f",&inputGPA);
		while (getchar() != '\n');
    	State = Check_GPA(&inputGPA,&scanReturn);
		if(0 == State)
		{
			break;
		}
		
		//VALID INPUTS
		State=1U;
		strcpy(newStudent->name,fullName);
		newStudent->age=inputAge;
		if('M' == inputGender)
		{
			strcpy(newStudent->gender,"Male");
		}
		else if ('F' == inputGender )
		{
			strcpy(newStudent->gender,"Female");
		}
		newStudent->gpa=inputGPA;
	}while(0);
	
	return State;
}

void addStudent(studentData** start)
{
    sint32 inputID;

    printTitle("              Add Student\n");

    if (!scanID(&inputID))
    {
        return;
    }

    if (NULL == *start)
    {
        studentData* newStudent = (studentData*)malloc(sizeof(studentData));
        newStudent->id = inputID;
        uint8 validProcess = Scan_Check_Info(newStudent);
        if (!validProcess)
        {
            printFailure();
            free(newStudent);
            printPressEnter();
            getchar();
            return;
        }
        newStudent->link = NULL;
        *start = newStudent;
    }
    else
    {
        studentData* current = *start;
        while (NULL != current)
        {
            if (inputID == current->id)
            {
                printAlreadyAdded();
                printPressEnter();
                getchar();
                return;
            }
            current = current->link;
        }

        studentData* newStudent = (studentData*)malloc(sizeof(studentData));
        newStudent->id = inputID;
        uint8 validProcess = Scan_Check_Info(newStudent);
        if (!validProcess)
        {
            printFailure();
            free(newStudent);
            printPressEnter();
            getchar();
            return;
        }
        current = *start;
        while (current->link != NULL)
        {
            current = current->link;
        }

        newStudent->link = NULL;
        current->link = newStudent;
    }
    numberOfStudents++;
    printAdded();
    printPressEnter();
    getchar();
    return;
}


void editStudent(studentData* start)
{
    sint32 inputID;

    printTitle("          Edit Student's Info\n");

    if (!scanID(&inputID))
    {
        return;
    }

    uint8 found = 0;
    studentData* student = start;

    while (student != NULL)
    {
        if (inputID == student->id)
        {
            uint8 validProcess = Scan_Check_Info(student);
            if (!validProcess)
            {
                printFailure();
                printPressEnter();
                getchar();
                return;
            }
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
    printPressEnter();
    getchar();
    return;
}

void showStudents(studentData* start)
{
	printTitle("             Students List\n");
    
    if (numberOfStudents > 0)
    {
		printNumberOfStudents();
        studentData* student = start;
        
        while (NULL != student)
        {
            if (student->id>0)
            {
              	showStudentsFormat();
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

void showStudentsByGender(studentData* start)
{
	printTitle("        Students List By Gender\n");
    
    if (numberOfStudents > 0)
    {
		char inputGender;
		uint8 scanReturn;
		uint8 State;
		printNumberOfStudents();
		printf("Enter Student's Gender [M or F]: ");
		scanReturn = scanf(" %c", &inputGender);
		inputGender=toupper(inputGender);
		while (getchar() != '\n');
		State= Check_Gender(&inputGender,&scanReturn);
		if(0 == State)
		{
			printPressEnter();
			getchar();
			return;
		}
		printLine();
        studentData* student = start;
		uint8 foundGender=0;
        while (NULL != student)
        {
            if (student->id > 0 && inputGender == (student->gender)[0] )
            {
				foundGender=1;
				showStudentsByGenderFormat();
			}
            student = student->link;
        }
		
		if(!foundGender)
		{
			if('M' == inputGender)
			{
				printf("No Male Students Added Yet!\n");
			}
			else
			{
				printf("No Female Students Added Yet!\n");
			}
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
	
	printTitle("              Search by ID\n");
	printNumberOfStudents();
    if(!scanID(&inputID))
	{
		return;
	}
	
    uint8 found = 0;
    studentData* student = start;
	
	while (NULL != student)
    {
        if (inputID ==student->id)
        {
			printTitle("             Student's Info\n");
			printStudentInfo(student);
			printPressEnter();
			getchar();
			return;
        }
        student = student->link;
    }
	
	printInfoNotFound();
	printPressEnter();
    getchar();
}

void deleteStudent(studentData** start)
{
    sint32 inputID;
	
	printTitle("          Delete Student's Info\n");
	
	if(!scanID(&inputID))
	{
		return;
	}
	
    studentData* student = *start;
	studentData* prevStudent= NULL;

    while (student != NULL)
    {
		if (inputID == student->id)
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
			printPressEnter();
			getchar();
			return;
       	}
       	prevStudent = student;
		student= student->link;
    }
	printAlreadyEmpty();
	printPressEnter();
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
    while (NULL != currentNode)
    {
        studentData* previousNode = currentNode;
        currentNode = currentNode->link;
        free(previousNode);
    }
}

