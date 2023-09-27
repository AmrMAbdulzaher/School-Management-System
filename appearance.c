/**
 * @file appearance.c
 * @brief School Management System User Interface Functions
 *
 * This file contains the implementation of functions responsible for managing the
 * user interface and appearance of the School Management System program. These
 * functions handle tasks such as displaying menus, printing messages with colors,
 * and providing information about the program and its developers.
 *
 * @authors
 *   - Amr Mohamed Abdulzaher (amrnassareng@gmail.com)
 *   - Mohamed Ahmed Shams (mohamed.ah.shams@gmail.com)
 *
 * @date 26-09-2023
 */

#include "STD_TYPES.h"
#include "functions.h"
#include "appearance.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Displays the system header with a clear screen.
 *
 * This function clears the screen and then prints a header for the School
 * Management System. It adds horizontal lines for aesthetics.
 */
void systemHeader(void)
{
    system(CLEAR); // Clear the screen
    printLine();   // Print a horizontal line
    textNormal_B(); // Set text to bold and normal
    printf("        School Management System\n"); // Print the system title
    textReset();   // Reset text formatting
    printLine();   // Print another horizontal line
}
/**
 * Displays the main menu options.
 *
 * This function prints the main menu options, allowing the user to choose
 * between login, about, and exit.
 */
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
/**
 * Displays the admin menu options.
 *
 * This function prints the admin menu options, allowing administrators to
 * add students, edit student info, search by ID, and more.
 */
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
/**
 * Displays the "About" menu options.
 *
 * This function prints the "About" menu options, allowing users to learn more
 * about the program and its developers.
 */
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
/**
 * Displays the login panel title.
 *
 * This function prints the title for the login panel.
 */
void printLoginTitle(void)
{
	textNormal_B();
	printf("             Login Panel\n");
	textReset();
    printLine();
}
/**
 * Prints a specified title with a horizontal line.
 *
 * @param title The title to be printed.
 */
void printTitle(const char* title)
{
	systemHeader();
	textNormal_B();
    printf("%s", title);
    textReset();
	printLine();
}
/**
 * Displays a login failure message.
 *
 * This function informs the user that their login attempt has failed and
 * indicates the remaining login attempts.
 */
void printLoginFailed(void)
{
	extern uint8 attemptsCounter;
	
	systemHeader();
	textRed_B();
    printf("Login failed. %hhu attempts remaining.\n", attemptsCounter);
	textReset();
	printLine();
}
/**
 * Displays a message indicating too many failed login attempts.
 *
 * This function informs the user that there have been too many failed login
 * attempts.
 */
void printTooManyLogins(void)
{
	systemHeader();
	textRed_B();
    printf("Too many failed login attempts.\n");
	textReset();
	printLine();
}
/**
 * Prints text with a time delay for animation.
 *
 * @param text     The text to be printed with animation.
 * @param time_ms  The time delay between each character in milliseconds.
 */
void printAnimatedText(const char* text,const uint32 time_ms)
{
	for (uint32 i = 0; text[i] != '\0'; i++)
    {
        putchar(text[i]);
        fflush(stdout);
        sleep(time_ms);
    }
}
/**
 * Displays information about the program.
 *
 * This function provides information about the School Management System program.
 * It includes a program description.
 */
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

/**
 * Displays information about the developers.
 *
 * This function provides information about the developers of the School Management System program.
 * It includes the developers' names and contact information.
 */
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
/**
 * Displays an "Exiting" message with animated dots.
 *
 * This function displays an "Exiting" message with animated dots to indicate
 * program exit.
 */
void printExiting(void)
{
	systemHeader();
	printf("Exiting");
    char dots[] = ".........\n";
    printAnimatedText(dots, exitingDotsTime);
}
/**
 * Prints student information.
 *
 * This function prints information about a student, including their name, ID,
 * age, gender, and CGPA.
 *
 * @param student A pointer to the student data structure to be printed.
 */
void printStudentInfo(studentData* student)
{
	textNormal_B();
    printf("Name:\033[0m %s\n", student->name);
	textNormal_B();
    printf("ID:\033[0m %d\n", student->id);
	textNormal_B();
	printf("Age:\033[0m %hhd\n", student->age);
	textNormal_B();
	printf("Gender:\033[0m %s\n", student->gender);
	textNormal_B();
	printf("CGPA:\033[0m %g\n", student->gpa);
	printLine();
}
/**
 * Prints student information by Gender.
 *
 * This function prints information about a student, including their name, ID,
 * and CGPA.
 *
 * @param student A pointer to the student data structure to be printed.
 */
void printStudentsByGender(studentData* student)
{
	printf(_bold_ "Name: " _reset_ "%s", student->name);
	printf(" [" _bold_ "ID:" _reset_ "%d]",student->id);
	printf(" [" _bold_ "CGPA:" _reset_ "%g]\n", student->gpa);
}
/**
 * Prints all students info
 *
 * This function prints information about a student, including their name, ID,
 * and CGPA.
 *
 * @param student A pointer to the student data structure to be printed.
 */
void printStudents(studentData* student)
{
	printf(_bold_ "Name: " _reset_ "%s", student->name);
	printf(" [" _bold_ "ID:" _reset_ "%d]",student->id);
	printf(" [" _bold_ "CGPA:" _reset_ "%g]\n", student->gpa);
}