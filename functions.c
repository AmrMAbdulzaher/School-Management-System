#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include "functions.h"

int numberOfStudents = 0;
char username[20];
char password[30];
int attempsCounter = 4;

studentData student[MAXSTUDENTS];

void printExiting(void)
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
	return;
}

void mainMenu(void)
{
	char mainMenuInput;
	
	for (int i = 0; i < MAXSTUDENTS; i++)
    {
        student[i].id = 0;
    }
	
	systemheader();
	printf("Main Menu\n");
    printf("========================\n");
    printf("[1] Login\n");
    printf("[2] About\n");
    printf("[3] Exit\n");
    printf("========================\n");
	scanf(" %c", &mainMenuInput);
	switch (mainMenuInput)
     {
         case '1':
         {
             systemheader();
             loginPanel(username, password);
			 break;
         }

         case '2':
         {
             printAbout();
             break;
         }

         case '3':
         {
            printExiting();
			break;
         }

         default:
            mainMenu();
     }
	return;
}


void systemheader(void)
{
    system(CLEAR);
    printf("School Management System\n");
    printf("========================\n");
}

void loginPanel(char *user, char *pass)
{
    printf("Login Panel\n");
    printf("========================\n");
    printf("Username: ");
    scanf("%19s", user);
    printf("Password: ");
    scanf("%29s", pass);
	// USER IS ADMIN
    if (!(strcmp(username, adminUser) || strcmp(password, adminPassword)))
    {
		attempsCounter=4;
        adminPanel(student);
    }

    // WRONG USERNAME OR PASSWORD
    else
    {
        loginAgain();
    }
}

void loginAgain(void)
{
	
    if (attempsCounter != 0)
    {
        systemheader();
		attempsCounter--;
        printf("\033[1;31mWRONG User or Password! %d attempts left.\n\033[0m", attempsCounter);
        loginPanel(username, password);
    }
    else
    {
        systemheader();
        printf("\033[1;31mYou have been kicked out of the system due to too many wrong attempts.\nPress any key to continue.\033[0m\n");
		getchar();
		getchar();
		
    }
}

void addStudent(studentData student[])
{
    int scanReturn;
    unsigned char inputID;

    systemheader();
    printf("Add Student\n");
    printf("========================\n");

    printf("Enter Student's ID [from 1 to %d]: ", MAXSTUDENTS);
    scanReturn = scanf("%hhu", &inputID);

    if (inputID < 1 || inputID > MAXSTUDENTS || scanReturn != 1)
    {
        printf("\033[1;31mInvalid Student ID. Press any key to continue.\033[0m\n");
        getchar();
		getchar();
        adminPanel(student);
    }

    if (student[inputID - 1].id == 0)
    {
        student[inputID - 1].id = inputID;
        printf("Enter Student's Full Name: ");
        scanf(" %[^\n]%*c", student[inputID - 1].name);
        printf("Enter Student's CGPA [MAX. 4]: ");
        float gpa;
        while (1)
        {
            scanReturn = scanf("%f", &gpa);
            if (gpa < 0.0 || gpa > 4.0 || scanReturn != 1)
            {
                printf("Invalid GPA, re-Enter Student's CGPA [MAX. 4]: ");
                while (getchar() != '\n'); // Clear input buffer
            }
            else
            {
                break;
            }
        }
        student[inputID - 1].gpa = gpa;
        numberOfStudents++;
        printf("\033[1;31mSUCCESSFULLY ADDED!, Press any key to continue.\033[0m\n");
    }
    else
    {
        printf("\033[1;31mALREADY ADDED!, Press any key to continue.\033[0m\n");
    }
    getchar();
	getchar();
	adminPanel(student);
}

void editStudent(studentData student[])
{
    unsigned char inputID;

    systemheader();
    printf("Edit Student's Info\n");
    printf("========================\n");
    printf("Enter Student's ID [from 1 to %d]: ", MAXSTUDENTS);
    scanf("%hhu", &inputID);

    if (inputID < 1 || inputID > MAXSTUDENTS || student[inputID - 1].id == 0)
    {
        printf("\033[1;31mInvalid Student ID. Press any key to continue.\033[0m\n");
        getchar();
        getchar();
        adminPanel(student);
    }

    printf("Enter Student's New Full Name: ");
    scanf(" %[^\n]%*c", student[inputID - 1].name);
    printf("Enter Student's New CGPA [MAX. 4]: ");
    float gpa;
    while (1)
    {
        int scanReturn = scanf("%f", &gpa);
        if (gpa < 0.0 || gpa > 4.0 || scanReturn != 1)
        {
            printf("Invalid GPA, re-Enter Student's New CGPA [MAX. 4]: ");
            while (getchar() != '\n'); // Clear input buffer
        }
        else
        {
            break;
        }
    }
    student[inputID - 1].gpa = gpa;
    printf("\033[1;31mSUCCESSFULLY EDITED!, Press any key to continue.\033[0m\n");
    getchar();
    getchar();
	adminPanel(student);
}

void showStudents(studentData student[])
{
    systemheader();
    printf("Students List\n");
    printf("========================\n");

    if (numberOfStudents > 0)
    {
        for (int i = 0; i < MAXSTUDENTS; i++)
        {
            if (student[i].id != 0)
            {
                printf("ID: %hhu\tName: %s\tCGPA: %g\n", student[i].id, student[i].name, student[i].gpa);
            }
        }
    }
    else
    {
        printf("NO STUDENTS ADDED YET!\n");
    }

    printf("\033[1;31mPress any key to continue.\033[0m\n");
    getchar();
    getchar();
	adminPanel(student);
}

void deleteStudent(studentData student[])
{
    unsigned char inputID;

    systemheader();
    printf("Delete Student Info\n");
    printf("========================\n");

    if (numberOfStudents != 0)
    {
        printf("Enter Student's ID [from 1 to %d]: ", MAXSTUDENTS);
        scanf("%hhu", &inputID);

        if (inputID < 1 || inputID > MAXSTUDENTS || student[inputID - 1].id == 0)
        {
            printf("\033[1;31mInvalid Student ID. Press any key to continue.\033[0m\n");
            getchar();
            getchar();
            adminPanel(student);
        }

        student[inputID - 1].id = 0;
        printf("\033[1;31mSUCCESSFULLY DELETED!, Press any key to continue.\033[0m\n");
        numberOfStudents--;
    }
    else
    {
        printf("NO STUDENTS ADDED YET!\n");
        printf("\033[1;31mPress any key to continue.\033[0m\n");
    }

    getchar();
    getchar();
	adminPanel(student);
}

void adminPanel(studentData student[])
{
    char choiceChar;
    unsigned char inputID;
    systemheader();
	printf("Admin Panel\n");
	printf("========================\n");
    printf("[1] Add Student\n");
    printf("[2] Edit Student Info\n");
    printf("[3] Show Students List\n");
    printf("[4] Delete Student Info\n");
	printf("[5] Main Menu\n");
    printf("[6] Logout\n");
    printf("[7] Exit\n");
    printf("========================\n");
    scanf(" %c", &choiceChar);

    switch (choiceChar)
    {
        case '1':
            addStudent(student);
            break;
        case '2':
            editStudent(student);
            break;
        case '3':
            showStudents(student);
            break;
        case '4':
            deleteStudent(student);
            break;
		case '5':
			mainMenu();
			break;
        case '6':
			systemheader();
            loginPanel(username, password);
			break;
        case '7':
            printExiting();
			break;
        default:
            // Handle invalid input
            adminPanel(student);
    }
	return;
	
}

void printAbout(void)
{
    systemheader();
    printf("[1] Program\n");
    printf("========================\n");
    printf("[2] Developers\n");
    printf("========================\n");
    char aboutMenuInput;
	scanf(" %c", &aboutMenuInput);
	switch (aboutMenuInput)
     {
        case'1':
        {
            systemheader();
            printf("About Program\n");
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
            printf("\033[1;31mPress any key to continue.\n");
            printf("\033[0m");
            getchar();
            getchar();
            mainMenu();
        }
         case '2':
         {
            systemheader();
            printf("About Developers\n");
            printf("========================\n");
            puts("\033[1;31m\t\t\t\t\t\t     ===================\n");
            char plain[] = "\t\t\t\tAmr Mohamed Abdulzaher\t\t\tMohamed Ahmed Shams\n";
            char email1[] = "\t\t\t\tamrnassareng@gmail.com";
            char email2[] = "\t\t\tMohamed.Ah.Shams@gmail.com\n";
            int i;
            printf("\033[0m");
            for (i = 0; plain[i] != '\0'; i++)
            {
                putchar(plain[i]);
                fflush(stdout);
                usleep(100000);
            }
            printf("\033[0;32m");
            for (i = 0; email1[i] != '\0'; i++)
            {
                putchar(email1[i]);
                fflush(stdout);
                usleep(100000);
            }
            printf("\033[0;34m");
            for (i = 0; email2[i] != '\0'; i++)
            {
                putchar(email2[i]);
                fflush(stdout);
                usleep(100000);
            }
            puts("\033[1;31m\n\t\t\t\t\t\t     ===================");
            printf("\033[1;31mPress any key to continue.\n");
            printf("\033[0m");
            getchar();
            getchar();
            mainMenu();
         }
         default:  printAbout();

     }
}






