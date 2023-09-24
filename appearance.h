#ifndef APPEARANCE_H
#define APPEARANCE_H
#include "functions.h"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define textReset()  printf("\033[0m")
#define textNormal_B() printf("\e[1m")
#define textRed_B()  printf("\033[1;31m")
#define textBlue_B()  printf("\033[1;34m")
#define textGreen_B()  printf("\033[1;32m")
#define textCyan()  printf("\033[0;36m")
#define printLine()  printf("==================================\n")
#define printPressEnter() printf("\033[0m\e[1mPress ENTER to continue.\033[0m")

#define ProgramTextTime 10000 
#define DevTextTime 30000
#define exitingDotsTime 150000

#define programDescription "This C code represents a basic School Management System program with user authentication and student data management features.\n\nIt allows users, primarily administrators, to log in, add, edit, view, or delete student records.\n"
#define firstDevName "Amr Mohamed Abdulzaher"
#define firstDevInfo "\namrnassareng@gmail.com\nwww.linkedin.com/in/amrnassareng\n\n"
#define secondDevName "Mohamed Ahmed Shams"
#define secondDevInfo "\nMohamed.Ah.Shams@gmail.com\nwww.linkedin.com/in/mashams\n"

void systemHeader(void);

void printMainMenu(void);

void printAdminMenu(void);

void printLoginTitle(void);

void printLoginFailed(void);

void printTooManyLogins(void);

void printTitle(char* title);

void printAboutMenu(void);

void printAnimatedText(char* text,uint32 time_ms);

void printAboutProgram(void);

void printAboutDevelopers(void);

void printExiting(void);

void exitSystem(void);

void printInfoNotFound(void);

void printInvalidGPA(void);

void printNotFoundID(void);

void printEdited(void);

void printInvalidID(void);

void printAlreadyAdded(void);

void printAdded(void);

void printStudentInfo(studentData* student);

void printAlreadyEmpty(void);

void printDeleted(void);


#endif