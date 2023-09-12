#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define CLEAR "clear"

#define adminUser "admin"
#define adminPassword "imtheboss"

#define studentUser "ahmed"
#define studentPassword "1234"

int numOfStudents=0;

void loginPanel(char*, char*);
void adminPanel(void);
void studentPanel(void);


int main()
{
    int userChoice;
    char username[20];
    char password[30];
    int invalidLogin=1;
    int attempsCounter=4;
    
    system(CLEAR);
    

    printf("School Management System\n");
    printf("========================\n");
    
    
    do
    {
        loginPanel(username,password);
        
        if(!(strcmp(username, adminUser) && strcmp(password, adminPassword)))
        {
            invalidLogin=0;
            system(CLEAR);
            printf("School Management System\n");
            printf("========================\n");
            adminPanel();
            break;
        }
        
        
        else if(!(strcmp(username, studentUser) && strcmp(password, studentPassword)))
        {
            invalidLogin=0;
            system(CLEAR);
            printf("School Management System\n");
            printf("========================\n");
            studentPanel();
            break;
        }
        else
        {
            attempsCounter--;
            system(CLEAR);
            if(attempsCounter!=0)
            {
                printf("School Management System\n");
                printf("========================\n");
                printf("\033[1;31m");
                printf("WRONG User or Password! %d attemps left.\n",attempsCounter);
                printf("\033[0m");
            }
            else
            {
                
                printf("School Management System\n");
                printf("========================\n");
                printf("\033[1;31m");
                printf("You have been kicked out of the system due to too many wrong attempts.\n");
                break;
            }
            
        }
    }while(invalidLogin);

    printf("\033[0mGoodBye! :)\n");
    return 0;
}

void loginPanel(char* user,char* pass)
{
    printf("LOGIN PANEL\n");
    printf("===========\n");
    printf("Username: ");
    scanf("%19s",user);
    printf("Password: ");
    scanf("%29s",pass);
}

void adminPanel(void)
{
    printf("HELLO ADMIN!\n");
}
void studentPanel(void)
{
    printf("HELLO STUDENT!\n");
}
