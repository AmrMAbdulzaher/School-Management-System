#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"

int numberOfStudents = 0;
char username[21];
char password[31];
int attemptsCounter = 4;

studentData* start = NULL;

void systemheader(void)
{
    system(CLEAR);
	printf("========================\n");
    printf("\e[1mSchool Management System\033[0m\n");
    printf("========================\n");
}

void free_Students(studentData* start)
{
	studentData* current = start;
    while (current != NULL)
    {
        studentData* temp = current;
        current = current->link;
        free(temp); 
    }
}

void mainMenu(void)
{
	unsigned char mainMenuInput;
	while(1)	
	{
    	systemheader();
    	printf("       \e[1mMain Menu\033[0m\n");
    	printf("========================\n");
    	printf("[1] Login\n");
    	printf("[2] About\n");
    	printf("[3] Exit\n");
    	printf("========================\n");
		
		scanf("%hhu", &mainMenuInput);
		while (getchar() != '\n');
		
		switch (mainMenuInput)
    	 {
    	     case 1:
    	     {
    	         systemheader();
    	         loginPanel(username, password);
				 break;
    	     }
	
    	     case 2:
    	     {
    	         aboutMenu();
    	         break;
    	     }
	
    	     case 3:
    	     {
				free_Students(start);
    	        exitSystem();
				return;
    	     }
	
    	     default:
    	       break;
    	 }
	}
	return;
}

void loginPanel(char *user, char *pass)
{
	while(1)
	{
    	printf("     \e[1mLogin Panel\033[0m\n");
    	printf("========================\n");
    	printf("Username: ");
    	scanf(" %[^\n]%*c", user);
    	printf("Password: ");
    	scanf(" %[^\n]%*c", pass);
		
		// USER IS ADMIN
    	if ( strcmp(username, adminUser) == 0 && strcmp(password, adminPassword) == 0)
    	{
    	    attemptsCounter=4;
    	    adminMenu();
			return;
    	}
    	 // WRONG USERNAME OR PASSWORD
    	else
    	{
    	    loginAgain();
    	}
	}
	
}

void loginAgain(void)
{

    if (attemptsCounter > 1)
    {
        systemheader();
		attemptsCounter--;
        printf("\033[1;31mLogin failed. %d attempts remaining.\n\033[0m", attemptsCounter);
		printf("========================\n");
        return;
    }
    else
    {
        systemheader();
        printf("\033[1;31mToo many failed login attempts.\n\033[0m");
		printf("========================\n");
		printf("Exiting");
    	char plain[] = ".........\n";
    	for (int i = 0; plain[i] != '\0'; i++)
    	{
        	putchar(plain[i]);
        	fflush(stdout);
        	usleep(150000);
    	}
		exit(0);
    }
}

void adminMenu(void)
{
    unsigned char adminMenuInput;
	while(1)
	{
    	systemheader();
    	printf("      \e[1mAdmin Panel\n\033[0m");
    	printf("========================\n");
    	printf("[1] Add Student\n");
    	printf("[2] Edit Student Info\n");
		printf("[3] Search by ID\n");
    	printf("[4] Show Students List\n");
    	printf("[5] Delete Student Info\n");
    	printf("[6] Back to Main Menu\n");
    	printf("[7] Exit\n");
    	printf("========================\n");
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
				free_Students(start);
    	        exitSystem();
				break;
    	    default:
    	        break;
    	}
	}
	return;

}

void addStudent(studentData** start)
{
    unsigned int inputID;
    char inputName[20];
    float inputGPA;
    int scanReturn;
	
	systemheader();
    printf("      \e[1mAdd Student\033[0m\n");
    printf("========================\n");

    printf("Enter Student's ID: ");
    scanReturn = scanf("%u", &inputID);
    while (getchar() != '\n');
	
	//To Handle Invalid Input IDs
    if (inputID < 1 || scanReturn != 1)
    {
        printf("\033[1;31mInvalid Student ID. \033[0m\e[1mPress ENTER to continue.\033[0m");
        getchar();
        adminMenu();
    }
	
	studentData* current= *start;
	while(current != NULL)
	{
		if(current->id == inputID)
		{
    	   	printf("\033[1;31mALREADY ADDED! \033[0m\e[1mPress ENTER to continue.\033[0m");
			getchar();
        	adminMenu();
		}
		current = current->link;
	}
	
	studentData* newStudent = (studentData*)malloc(sizeof(studentData));
	newStudent->id=inputID;
	printf("Enter Student's Full Name: ");
    scanf(" %[^\n]%*c", newStudent->name);
    printf("Enter Student's GPA [Max. 4]: ");
    while (1)
    {
        scanReturn = scanf("%f", &inputGPA);
        while (getchar() != '\n');
        if (inputGPA < 0.0f || inputGPA > 4.0f || scanReturn != 1)
        {
            printf("\033[1;31mInvalid GPA, re-Enter Student's CGPA [MAX. 4]: ");
        }
        else
        {
            break;
        }
    }
    newStudent->gpa = inputGPA;
    newStudent->added = 1;
	newStudent->link = *start;
    *start = newStudent;
	numberOfStudents++;
    printf("\033[1;32mSUCCESSFULLY ADDED! \033[0m\e[1mPress ENTER to continue.\033[0m");
    getchar();
	return;
}

void editStudent(studentData* start)
{
    unsigned int inputID;
    char inputName[20];
    float inputGPA;
    int scanReturn;
    unsigned char found = 0;
	
	systemheader();
    printf("  \e[1mEdit Student's Info\033[0m\n");
    printf("========================\n");

    printf("Enter Student's ID: ");
    scanReturn= scanf("%u", &inputID);
    while (getchar() != '\n');

    if (inputID < 1 || scanReturn != 1)
    {
        printf("\033[1;31mInvalid Student ID. \033[0m\e[1mPress ENTER to continue.\033[0m");
        getchar();
        return;
    }

    studentData* student = start;

    while (student != NULL)
    {
        if (student->id == inputID)
        {
            printf("ENTER Student's New Full Name: ");
            scanf(" %[^\n]%*c", inputName);
            strcpy(student->name, inputName);

            printf("ENTER Student's New CGPA [MAX. 4]: ");
            while (1)
            {
                scanReturn = scanf("%f", &inputGPA);
                while (getchar() != '\n');
                if (inputGPA < 0.0f || inputGPA > 4.0f || scanReturn != 1)
                {
                    printf("\033[1;31mInvalid GPA, re-Enter Student's New CGPA [MAX. 4]: ");
                }
                else
                {
                    break;
                }
            }
            student->gpa = inputGPA;
            printf("\033[1;32mSUCCESSFULLY EDITED! \033[0m\e[1mPress ENTER to continue.\033[0m");
            found = 1;
            break;
        }
        student = student->link;
    }

    if (!found)
    {
        printf("\033[1;31mID NOT FOUND! \033[0m\e[1mPress ENTER to continue.\033[0m");
    }

    getchar();
	return;
}



void showStudents(studentData* start)
{
    systemheader();
    printf("     \e[1mStudents List\033[0m\n");
    printf("========================\n");

    if (numberOfStudents > 0)
    {
        studentData* student = start;
        
        while (student != NULL)
        {
            if (student->added)
            {
                printf("\e[1mName:\033[0m %s [\e[1mID:\033[0m%hhu]\n", student->name, student->id);
            }
            student = student->link;
        }
		printf("========================\n");
    }
    else
    {
        printf("NO STUDENTS ADDED YET!\n");
    }

    printf("\033[0m\e[1mPress ENTER to continue.\033[0m");
    getchar(); // Wait for user input before returning to admin menu
}

void showStudentByID(studentData* start)
{
	unsigned int inputID;
    unsigned char found = 0;
	int scanReturn;

    systemheader();
    printf("      \e[1mSearch by ID\033[0m\n");
    printf("========================\n");

    printf("Enter Student's ID: ");
    scanReturn= scanf("%u", &inputID);
    while (getchar() != '\n');

    if (inputID < 1 || scanReturn!= 1)
    {
        printf("\033[1;31mInvalid Student ID. \033[0m\e[1mPress ENTER to continue.\033[0m");
        getchar();
        return;
    }

    studentData* student = start;
	
	while (student != NULL)
    {
        if (student->id == inputID)
        {
			systemheader();
			printf("     \e[1mStudent's Info\033[0m\n");
    		printf("========================\n");
            printf("\e[1mName:\033[0m %s\n", student->name);
            printf("\e[1mID:\033[0m %hhu\n", student->id);
			printf("\e[1mCGPA:\033[0m %g\n", student->gpa);
			printf("========================\n");
			printf("\033[0m\e[1mPress ENTER to continue.\033[0m");
			getchar();
			return;
        }
        student = student->link;
    }
	
    printf("\033[1;31mSTUDENT INFO NOT ADDED YET! \033[0m\e[1mPress ENTER to continue.\033[0m");
    getchar();
}

void deleteStudent(studentData** start)
{
    unsigned int inputID;
	int scanReturn;

    systemheader();
    printf("  \e[1mDelete Student's Info\033[0m\n");
    printf("========================\n");

    printf("Enter Student's ID: ");
    scanReturn= scanf("%u", &inputID);
    while (getchar() != '\n');

    if (inputID < 1 || scanReturn !=1)
    {
        printf("\033[1;31mInvalid Student ID. \033[0m\e[1mPress ENTER to continue.\033[0m");
        getchar();
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
				prevStudent= student->link;
			}
       	    free(student);
       	    printf("\033[1;32mSUCCESSFULLY DELETED! \033[0m\e[1mPress ENTER to continue.\033[0m");
       	    numberOfStudents--;
			getchar();
			return;
       	}
       	prevStudent = student;
		student= student->link;
    }
	
	printf("\033[1;31mALREADY EMPTY! \033[0m\e[1mPress ENTER to continue.\033[0m");
    getchar();
}


void aboutMenu(void)
{
	unsigned char aboutMenuInput;
	while(1)
	{
    	systemheader();
		printf("         \e[1mAbout\033[0m\n");
		printf("========================\n");
    	printf("[1] Program\n");
    	printf("[2] Developers\n");
    	printf("[3] Back to Main Menu\n");
    	printf("========================\n");
    	
    	scanf("%hhu", &aboutMenuInput);
		while (getchar() != '\n');
		
    	switch (aboutMenuInput)
    	 {
    	    case 1:
    	    {
    	        systemheader();
    	        printf("     \e[1mAbout Program\033[0m\n");
    	        printf("========================\n");
    	        char plain1[] = {"This C code represents a basic School Management System program with user authentication and student data management features.\nIt allows users, primarily administrators, to log in, add, edit, view, or delete student records.\n"};
    	        int i;
    	        printf("\033[0;36m");
    	        for (i = 0; plain1[i] != '\0'; i++)
    	        {
    	            putchar(plain1[i]);
    	            fflush(stdout);
    	            usleep(10000);
    	        }
				printf("\033[0m========================\n");
    			printf("\033[0m\e[1mPress ENTER to continue.");
    			printf("\033[0m");
    			getchar();
				break;
    	    }
    	     case 2:
    	     {
    	        systemheader();
    	        printf("    \e[1mAbout Developers\033[0m\n");
    	        printf("========================\n");
    	        char amrFullName[] = "Amr Mohamed Abdulzaher";
    	        char amrInfo[] = "\namrnassareng@gmail.com\nwww.linkedin.com/in/amrnassareng\n\n";
				char shamsFullName[] = "Mohamed Ahmed Shams";
    	        char shamsInfo[] = "\nMohamed.Ah.Shams@gmail.com\nwww.linkedin.com/in/mashams\n";
    	        int i;
				 
				//AMR NAME
    	        printf("\033[0m");
    	        for (i = 0; amrFullName[i] != '\0'; i++)
    	        {
    	            putchar(amrFullName[i]);
    	            fflush(stdout);
    	            usleep(30000);
    	        }
				//AMR INFO
				printf("\033[0;32m");
    	        for (i = 0; amrInfo[i] != '\0'; i++)
    	        {
    	            putchar(amrInfo[i]);
    	            fflush(stdout);
    	            usleep(30000);
    	        }
				//SHAMS NAME
				printf("\033[0m");
    	        for (i = 0; shamsFullName[i] != '\0'; i++)
    	        {
    	            putchar(shamsFullName[i]);
    	            fflush(stdout);
    	            usleep(30000);
    	        }
				//SHAMS INFO
    	        printf("\033[0;34m");
    	        for (i = 0; shamsInfo[i] != '\0'; i++)
    	        {
    	            putchar(shamsInfo[i]);
    	            fflush(stdout);
    	            usleep(30000);
    	        }
				printf("\033[0m========================\n");
    			printf("\033[0m\e[1mPress ENTER to continue.");
    			printf("\033[0m");
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

void exitSystem(void)
{
    systemheader();
    printf("Exiting");
    char plain[] = ".........\n";
    for (int i = 0; plain[i] != '\0'; i++)
    {
        putchar(plain[i]);
        fflush(stdout);
        usleep(150000);
    }
	exit(0);
}


