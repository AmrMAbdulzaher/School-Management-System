/*
 * Shams: Add Typing Effect to Exiting option @6:10
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

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
void systemheader(void);

typedef struct
{
    char name[20];
    unsigned char id;
    float gpa;

}studentData;

int numberOfStudents=0;

int main()
{
    int userChoice;
    char username[20];
    char password[30];
    int choice;
    unsigned char inputID;
    char choiceChar;
    //Array of struct studentData
    studentData student[MAXSTUDENTS];
    int flag;

    // Initialize student data
    for (int i = 0; i < MAXSTUDENTS; i++)
    {
        student[i].id = 0; 
    }
	
	LoginLine:
	systemheader();
	int attempsCounter = 4;
	int invalidLogin = 1;
	
    do
    {
        loginPanel(username, password);
		
		//USER IS ADMIN
        if (!(strcmp(username, adminUser) || strcmp(password, adminPassword)))
        {
            invalidLogin = 0;
            adminLine:
			systemheader();
            printf("[1] Add Student\n");
            printf("[2] Edit Student Info\n");
            printf("[3] Show Students List\n");
            printf("[4] Delete Student Info\n");
			printf("[5] Logout\n");
			printf("[6] Exit\n");
            printf("========================\n");
            scanChoiceChar:
            scanf(" %c", &choiceChar);
            switch (choiceChar)
            {
                case '1':
                {
					int scanReturn;
					systemheader();
					printf("Add Student\n");
    				printf("============\n");

                    printf("Enter Student's ID [from 1 to %d]: ",MAXSTUDENTS);
                    scanReturn= scanf("%hhu", &inputID);

                    if (inputID < 1 || inputID > MAXSTUDENTS || scanReturn!=1)
                    {
                        printf("\033[1;31mInvalid Student ID. Press any key to continue.");
						printf("\033[0m");
						getchar();
						int c;
						while ((c = getchar()) != '\n' && c != EOF);
						getchar();
                        goto adminLine;
                    }
					
					if (student[inputID - 1].id == 0)
					{
                    	student[inputID - 1].id = inputID;
                    	printf("Enter Student's Full Name: ");
                    	scanf(" %[^\n]%*c", student[inputID - 1].name);
                    	printf("Enter Student's CGPA [MAX. 4]: ");
						scanGPA:
                    	scanf("%f", &student[inputID - 1].gpa);
						
						if(student[inputID - 1].gpa < 0.0 || student[inputID - 1].gpa > 4.0)
						{
							printf("Invalid GPA, re-Enter Student's CGPA [MAX. 4]: ");
							goto scanGPA;
						}
						
						numberOfStudents++;
                    	printf("\033[1;31mSUCCESSFULLY ADDED!, Press any key to continue.\n");
					}
					else
					{
						printf("\033[1;31mALREADY ADDED!, Press any key to continue.\n");
					}
                    printf("\033[0m");
                    getchar(); 
                    getchar();
                    goto adminLine;

					
                    break;
                }
                case '2':
                {
                    systemheader();
					printf("Edit Student Info\n");
    				printf("==================\n");
                    printf("Enter Student's ID [from 1 to %d]: ",MAXSTUDENTS);
                    scanf("%hhu", &inputID);

                    if (inputID < 1 || inputID > MAXSTUDENTS || student[inputID-1].id==0 )
                    {
                        printf("\033[1;31mInvalid Student ID. Press any key to continue.");
						printf("\033[0m");
						getchar();
						getchar(); 
                        int c;
						while ((c = getchar()) != '\n' && c != EOF);
                        goto adminLine;
                    }
                    printf("Enter Student's New Full Name: ");
                    scanf(" %[^\n]%*c", student[inputID-1].name);
                    printf("Enter Student's New CGPA [MAX. 4]: ");
					scanNewGPA:
                    scanf("%f", &student[inputID-1].gpa);
					if(student[inputID - 1].gpa < 0.0 || student[inputID - 1].gpa > 4.0)
					{
						printf("Invalid GPA, re-Enter Student's New CGPA [MAX. 4]: ");
						goto scanNewGPA;
					}
                    printf("\033[1;31mSUCCESSFULLY EDITED!, Press any key to continue.\n");
                    printf("\033[0m");
                    getchar(); 
                    getchar();
                    goto adminLine;
                    break;
                }
                case '3':
                {
                    systemheader();
					printf("Students List\n");
    				printf("==================\n");
					
					if(numberOfStudents>0)
					{
						for(int i= 0; i< MAXSTUDENTS ; i++)
						{
							if(student[i].id !=0)
							{
								printf("ID: %hhu\tName: %s\tCGPA: %g\n",student[i].id,student[i].name,student[i].gpa);
							}
							else
							{
								continue;
							}
						}
					}
					else
					{
						printf("NO STUDENTS ADDED YET!\n");
					}
					
					printf("\033[1;31mPress any key to continue.\n");
					printf("\033[0m");
					getchar();
					getchar();
                    goto adminLine;
                    break;
                }
                case '4':
                {
                    systemheader();
					printf("Delete Student Info\n");
    				printf("==================\n");
                    if (numberOfStudents!=0){

                        printf("Enter Student's ID [from 1 to %d]: ",MAXSTUDENTS);
                        scanf("%hhu", &inputID);

                        if (inputID < 1 || inputID > MAXSTUDENTS || student[inputID-1].id==0 )
                        {
                            printf("\033[1;31mInvalid Student ID. Press any key to continue.");
                            printf("\033[0m");
                            getchar();
                            getchar();
                            int c;
                            while ((c = getchar()) != '\n' && c != EOF);
                            goto adminLine;
                        }
                        student[inputID-1].id = 0;
                        printf("\033[1;31mSUCCESSFULLY Deleted!, Press any key to continue.\n");
                        numberOfStudents--;
                        printf("\033[0m");
                        getchar();
                        getchar();
                        goto adminLine;
                        break;
                    }
                    else{
						printf("NO STUDENTS ADDED YET!\n");
                        printf("\033[1;31mPress any key to continue.\n");
                        printf("\033[0m");
                        getchar();
                        getchar();
                        goto adminLine;
                        break;
                    }

                }
				case '5':
                {
                    goto LoginLine;
                }
				case '6':
                {
                    systemheader();
                    char plain[] = "Exiting......\n";
                    for(int i = 0; plain[i]!='\0';i++)
                    {
                        putchar(plain[i]);
                        fflush(stdout);
                        usleep(150000);
                    }
                    return 0;
                }
                default:
                    goto scanChoiceChar;
            }
        }
		
		//USER IS STUDENT
        else if (!(strcmp(username, studentUser) || strcmp(password, studentPassword)))
        {
            invalidLogin = 0;
            systemheader();
            printf("HELLO STUDENT!\n");
        }
		
		//WRONG USERNAME OR PASSWORD
        else
        {
            attempsCounter--;
            if (attempsCounter != 0)
            {
                systemheader();
                printf("\033[1;31mWRONG User or Password! %d attempts left.\n\033[0m", attempsCounter);
            }
            else
            {
				systemheader();
                printf("\033[1;31mYou have been kicked out of the system due to too many wrong attempts.\n\033[0m");
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

void systemheader(void)
{
	system(CLEAR);
	printf("School Management System\n");
    printf("========================\n");
}
