#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"

int numberOfStudents = 0;
char username[21];
char password[31];
int attempsCounter = 4;

studentData student[MAXSTUDENTS];

void systemheader(void)
{
    system(CLEAR);
	printf("========================\n");
    printf("\e[1mSchool Management System\033[0m\n");
    printf("========================\n");
}

void mainMenu(void)
{
	unsigned char mainMenuInput;

	for (int i = 0; i < MAXSTUDENTS; i++)
    {
        (student+i)->id = 0;
    }

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
            exitSystem();
			break;
         }

         default:
            mainMenu();
     }
	return;
}

void loginPanel(char *user, char *pass)
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
        attempsCounter=4;
        adminMenu(student);
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
        printf("\033[1;31mYou have been kicked out of the system due to too many wrong attempts.\nPress ENTER to continue.\033[0m");
		getchar();
    }
}

void adminMenu(studentData student[])
{
    unsigned char adminMenuInput;
    systemheader();
    printf("      \e[1mAdmin Panel\n\033[0m");
    printf("========================\n");
    printf("[1] Add Student\n");
    printf("[2] Edit Student Info\n");
    printf("[3] Show Students List\n");
    printf("[4] Delete Student Info\n");
	printf("[5] Logout\n");
    printf("[6] Back to Main Menu\n");
    printf("[7] Exit\n");
    printf("========================\n");
    scanf("%hhu", &adminMenuInput);
	while (getchar() != '\n');
	
    switch (adminMenuInput)
    {
        case 1:
            addStudent(student);
            break;
        case 2:
            editStudent(student);
            break;
        case 3:
            showStudents(student);
            break;
        case 4:
            deleteStudent(student);
            break;
		case 5:
			systemheader();
            loginPanel(username, password);
			break;	
		case 6:
			mainMenu();
			break;

        case 7:
            exitSystem();
			break;
        default:
            // Handle invalid input
            adminMenu(student);
    }
	return;

}

void addStudent(studentData student[])
{
    unsigned char inputID;
	int scanReturn;

    systemheader();
    printf("      \e[1mAdd Student\033[0m\n");
    printf("========================\n");

    printf("ENTER Student's ID [from 1 to %d]: ", MAXSTUDENTS);
    scanf("%hhu", &inputID);
	while (getchar() != '\n');

    if (inputID < 1 || inputID > MAXSTUDENTS)
    {
        printf("\033[1;31mInvalid Student ID. Press ENTER to continue.\033[0m");
        getchar();
        adminMenu(student);
    }

    if ((student+INDEX)->id == 0)
    {
        (student+INDEX)->id = inputID;
        printf("ENTER Student's Full Name: ");
        scanf(" %[^\n]%*c", (student+INDEX)->name);
        printf("ENTER Student's CGPA [MAX. 4]: ");
        float gpa;
        while (1)
        {
            scanReturn= scanf("%f", &gpa);
			while (getchar() != '\n');
			
            if (gpa < 0.0f || gpa > 4.0f || scanReturn != 1 )
            {
                printf("Invalid GPA, re-Enter Student's CGPA [MAX. 4]: ");
            }
            else
            {
                break;
            }
        }
        (student+INDEX)->gpa = gpa;
        numberOfStudents++;
        printf("\033[1;31mSUCCESSFULLY ADDED!, Press ENTER to continue.\033[0m");
    }
    else
    {
        printf("\033[1;31mALREADY ADDED!, Press ENTER to continue.\033[0m");
    }
    getchar();
	adminMenu(student);
}

void editStudent(studentData student[])
{
    unsigned char inputID;
	int scanReturn;
	
    systemheader();
    printf("  \e[1mEdit Student's Info\033[0m\n");
    printf("========================\n");
	
    printf("ENTER Student's ID [from 1 to %d]: ", MAXSTUDENTS);
    scanf("%hhu", &inputID);
	while (getchar() != '\n');
	
    if (inputID < 1 || inputID > MAXSTUDENTS || (student+INDEX)->id == 0)
    {
        printf("\033[1;31mInvalid Student ID. Press ENTER to continue.\033[0m");
        getchar();
        adminMenu(student);
    }

    printf("ENTER Student's New Full Name: ");
    scanf(" %[^\n]%*c", (student+INDEX)->name);
    printf("ENTER Student's New CGPA [MAX. 4]: ");
    float gpa;
    while (1)
    {
        scanReturn= scanf("%f", &gpa);
		while (getchar() != '\n');
		
        if (gpa < 0.0f || gpa > 4.0f || scanReturn != 1)
        {
            printf("Invalid GPA, re-Enter Student's New CGPA [MAX. 4]: ");
        }
        else
        {
            break;
        }
    }
    (student+INDEX)->gpa = gpa;
    printf("\033[1;31mSUCCESSFULLY EDITED!, Press ENTER to continue.\033[0m");
    getchar();
    adminMenu(student);
}

void showStudents(studentData student[])
{
    systemheader();
    printf("     \e[1mStudents List\033[0m\n");
    printf("========================\n");

    if (numberOfStudents > 0)
    {
        for (int i = 0; i < MAXSTUDENTS; i++)
        {
            if ((student+i)->id != 0)
            {
                printf("ID: %hhu\tName: %s\tCGPA: %g\n", (student+i)->id, (student+i)->name, (student+i)->gpa);
            }
        }
    }
    else
    {
        printf("NO STUDENTS ADDED YET!\n");
    }

    printf("\033[1;31mPress ENTER to continue.\033[0m");
    getchar();
    adminMenu(student);
}

void deleteStudent(studentData student[])
{
    unsigned char inputID;;

    systemheader();
    printf("   \e[1mDelete Student Info\033[0m\n");
    printf("========================\n");

    if (numberOfStudents != 0)
    {
        printf("ENTER Student's ID [from 1 to %d]: ", MAXSTUDENTS);
        scanf("%hhu", &inputID);

        if (inputID < 1 || inputID > MAXSTUDENTS || (student+INDEX)->id == 0)
        {
            printf("\033[1;31mInvalid Student ID. Press ENTER to continue.\033[0m");
            getchar();
			getchar();
            adminMenu(student);
        }

        (student+INDEX)->id = 0;
        printf("\033[1;31mSUCCESSFULLY DELETED!, Press ENTER to continue.\033[0m");
        numberOfStudents--;
    }
    else
    {
        printf("NO STUDENTS ADDED YET!\n");
        printf("\033[1;31mPress ENTER to continue.\033[0m");
    }

    getchar();
	adminMenu(student);
}

void aboutMenu(void)
{
	unsigned char aboutMenuInput;
	
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
			 
			//AMR
            printf("\e[1m");
            for (i = 0; amrFullName[i] != '\0'; i++)
            {
                putchar(amrFullName[i]);
                fflush(stdout);
                usleep(30000);
            }
			//AMR EMAIL
			printf("\033[0;32m");
            for (i = 0; amrInfo[i] != '\0'; i++)
            {
                putchar(amrInfo[i]);
                fflush(stdout);
                usleep(30000);
            }
			//SHAMS
			printf("\e[1m");
            for (i = 0; shamsFullName[i] != '\0'; i++)
            {
                putchar(shamsFullName[i]);
                fflush(stdout);
                usleep(30000);
            }
			//SHAMS EMAIL
            printf("\033[0;34m");
            for (i = 0; shamsInfo[i] != '\0'; i++)
            {
                putchar(shamsInfo[i]);
                fflush(stdout);
                usleep(30000);
            }
			break;
         }
		case 3: 
			mainMenu();
			return;
        default:
			aboutMenu();

    }
	//EXIT
   	printf("\033[0m========================\n");
    printf("\033[1;31mPress ENTER to continue.");
    printf("\033[0m");
    getchar();
   	aboutMenu();
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
	return;
}
