#include "STD_TYPES.h"
#include "functions.h"
#include "appearance.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void systemHeader(void)
{
    system(CLEAR);
	printLine();
	textNormal_B();
    printf("        School Management System\n");
	textReset();
    printLine();
}

void printMainMenu(void)
{
	systemHeader();
	textNormal_B();
    printf("               Main Menu\n");
	textReset();
    printLine();
    printf("[1] Login\n");
    printf("[2] About\n");
    printf("[3] Exit\n");
    printLine();
}

void printAdminMenu(void)
{
	systemHeader();
	textNormal_B();
	printf("              Admin Panel\n");
	textReset();
    printLine();
    printf("[1] Add Student\n");
    printf("[2] Edit Student Info\n");
	printf("[3] Search by ID\n");
    printf("[4] Show Students List\n");
	printf("[5] Show Students List By Gender\n");
    printf("[6] Delete Student Info\n");
    printf("[7] Back to Main Menu\n");
    printf("[8] Exit\n");
    printLine();
}

void printAboutMenu(void)
{
	systemHeader();
	textNormal_B();
	printf("                 About\n");
	textReset();
	printLine();
    printf("[1] Program\n");
    printf("[2] Developers\n");
    printf("[3] Back to Main Menu\n");
    printLine();
}

void printLoginTitle(void)
{
	textNormal_B();
	printf("             Login Panel\n");
	textReset();
    printLine();
}

void printTitle(char* title)
{
	systemHeader();
	textNormal_B();
    printf("%s", title);
    textReset();
	printLine();
}

void printLoginFailed(void)
{
	extern uint8 attemptsCounter;
	
	systemHeader();
	textRed_B();
    printf("Login failed. %hhu attempts remaining.\n", attemptsCounter);
	textReset();
	printLine();
}

void printTooManyLogins(void)
{
	systemHeader();
	textRed_B();
    printf("Too many failed login attempts.\n");
	textReset();
	printLine();
}

void printAnimatedText(char* text,uint32 time_ms)
{
	for (uint32 i = 0; text[i] != '\0'; i++)
    {
        putchar(text[i]);
        fflush(stdout);
        usleep(time_ms);
    }
}

void printAboutProgram(void)
{
	systemHeader();
	textNormal_B();
    printf("             About Program\n");
	textReset();
    printLine();
    textCyan();
    printAnimatedText(programDescription,ProgramTextTime);
	textReset();
	printLine();
    printPressEnter();
    textReset();
}

void printAboutDevelopers(void)
{	
	systemHeader();
	textNormal_B();
    printf("            About Developers\n");
	textReset();
	printLine();
    textReset();
	printAnimatedText(firstDevName,DevTextTime);
	textGreen_B();
    printAnimatedText(firstDevInfo,DevTextTime);
	textReset();
    printAnimatedText(secondDevName,DevTextTime);
    textBlue_B();
    printAnimatedText(secondDevInfo,DevTextTime);
	textReset();
	printLine();
	printPressEnter();
    textReset();
}

void printExiting(void)
{
	systemHeader();
	printf("Exiting");
    char dots[] = ".........\n";
    printAnimatedText(dots, exitingDotsTime);
}

void printStudentInfo(studentData* student)
{
	textNormal_B();
    printf("Name:\033[0m %s\n", student->name);
	textNormal_B();
    printf("ID:\033[0m %hhu\n", student->id);
	textNormal_B();
	printf("Age:\033[0m %hhd\n", student->age);
	textNormal_B();
	printf("Gender:\033[0m %s\n", student->gender);
	textNormal_B();
	printf("CGPA:\033[0m %g\n", student->gpa);
	printLine();
}
