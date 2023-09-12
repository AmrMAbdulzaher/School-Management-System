#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define adminUser "admin"
#define adminPassword "imtheboss"

#define studentUser "ahmed"
#define studentPassword "1234"

#define MAXSTUDENTS 10

void loginPanel(char *, char *);
void adminPanel(void);
void studentPanel(void);
void systemclr(void);

typedef struct
{
    char name[20];
    unsigned char id;
    float gpa;
} studentData;

int main()
{
    int userChoice;
    char username[20];
    char password[30];
    int invalidLogin = 1;
    int attempsCounter = 4;
    int choice;
    unsigned char inputID;
    char choiceChar;
    studentData student[MAXSTUDENTS];

    // Initialize student data
    for (int i = 0; i < MAXSTUDENTS; i++)
    {
        student[i].id = 0; 
		strcpy(student[i].name, "NONAME");
		student[i].gpa= 0.0;
    }

	systemclr();

    do
    {
        loginPanel(username, password);

        if (!(strcmp(username, adminUser) && strcmp(password, adminPassword)))
        {
            invalidLogin = 0;
            adminLine:
			systemclr();
            printf("[1] Add Student\n");
            printf("[2] Edit Student Info\n");
            printf("[3] Show Students List\n");
            printf("[4] Exit\n");
            scanLine:
            scanf(" %c", &choiceChar); // Read a character with space to skip whitespace
            switch (choiceChar)
            {
                case '1':
                {
					systemclr();
					printf("Add Student\n");
    				printf("============\n");

                    printf("Enter Student's ID [from 1 to %d]: ",MAXSTUDENTS);
                    scanf("%hhu", &inputID);

                    if (inputID < 1 || inputID > MAXSTUDENTS)
                    {
                        printf("Invalid Student ID. Press any key to continue.");
                        getchar(); // Consume newline
                        getchar(); // Wait for user input
                        goto adminLine;
                    }
					if (student[inputID - 1].id == 0)
					{
                    	student[inputID - 1].id = inputID;
                    	printf("Enter Student's Full Name: ");
                    	scanf(" %[^\n]%*c", student[inputID - 1].name);
                    	printf("Enter Student's CGPA: ");
                    	scanf("%f", &student[inputID - 1].gpa);
                    	printf("\033[1;31mSUCCESSFULLY ADDED!, enter 'a' for admin panel or 'e' to exit.\n");
					}
					else
					{
						printf("\033[1;31mALREADY ADDED!, enter 'a' for admin panel or 'e' to exit.\n");
					}
					printf("\033[0m");
                    scanf(" %c", &choiceChar);
                    if (choiceChar == 'a')
                    {
                        goto adminLine;
                    }
					
                    break;
                }
                case '2':
                {
                    systemclr();
					printf("Edit Student Info\n");
    				printf("==================\n");
                    break;
                }
                case '3':
                {
                    systemclr();
					printf("Students List\n");
    				printf("==================\n");
					for(int i= 0; i< MAXSTUDENTS; i++)
					{
						printf("ID: %hhu\tName: %s\tCGPA: %g\n",student[i].id,student[i].name,student[i].gpa);
					}
					printf("\033[1;31menter 'a' for admin panel or any other key to exit.\n");
					printf("\033[0m");
                    scanf(" %c", &choiceChar);
                    if (choiceChar == 'a')
                    {
                        goto adminLine;
                    }
                    break;
                }
                case '4':
                {
                    printf("Exiting...\n");
                    return 0;
                }
                default:
                    printf("Invalid Input: ");
                    goto scanLine;
            }
        }
        else if (!(strcmp(username, studentUser) && strcmp(password, studentPassword)))
        {
            invalidLogin = 0;
            systemclr();
            printf("HELLO STUDENT!\n");
        }
        else
        {
            attempsCounter--;
            if (attempsCounter != 0)
            {
                systemclr();
                printf("\033[1;31m");
                printf("WRONG User or Password! %d attempts left.\n", attempsCounter);
                printf("\033[0m");
            }
            else
            {
				systemclr();
                printf("\033[1;31m");
                printf("You have been kicked out of the system due to too many wrong attempts.\n");
                break;
            }
        }
    } while (invalidLogin);
    return 0;
}

void loginPanel(char *user, char *pass)
{
    printf("LOGIN PANEL\n");
    printf("===========\n");
    printf("Username: ");
    scanf("%19s", user);
    printf("Password: ");
    scanf("%29s", pass);
}

void systemclr(void)
{
	system(CLEAR);
	printf("School Management System\n");
    printf("========================\n");
}
