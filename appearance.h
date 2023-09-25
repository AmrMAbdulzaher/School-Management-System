#ifndef APPEARANCE_H //fileguard
#define APPEARANCE_H

#include "functions.h"

//clear screen MACRO "Cross-platform"
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

//TEXT COLOR MACROS
#define textReset()  printf("\033[0m")
#define textNormal_B() printf("\e[1m")
#define textRed_B()  printf("\033[1;31m")
#define textBlue_B()  printf("\033[1;34m")
#define textGreen_B()  printf("\033[1;32m")
#define textCyan()  printf("\033[0;36m")
#define _reset_ "\033[0m"
#define _bold_ "\e[1m"

//PRINT MESSAGES MACROS
#define printInfoNotFound() do{\
            textRed_B();\
    		printf("Student Info Not Added Yet! ");\
           }while(0)

#define printInvalidID() do{\
            textRed_B();\
    		printf("Invalid Student ID! ");\
           }while(0)

#define printEdited() do{\
            textGreen_B();\
    		printf("Successfully Edited! ");\
           }while(0)

#define printNotFoundID() do{\
            textRed_B();\
			printf("ID Not Found! ");\
           }while(0)

#define printInvalidGPA() do {\
            textRed_B();\
    		printf("Invalid GPA! ");\
			textReset();\
			printf("Enter Student's GPA [Max. %g]: ", MAX_GRADE);\
           }while(0)

#define printInvalidName() do {\
            textRed_B();\
    		printf("Invalid Name! ");\
			textReset();\
			printf("Enter Student's Full Name: ");\
           }while(0)

#define printInvalidAge() do {\
            textRed_B();\
    		printf("Invalid Age! ");\
			textReset();\
			printf("Enter Student's Age: ");\
           }while(0)

#define printInvalidGender() do {\
            textRed_B();\
    		printf("Why are you gay?! ಠಿ_ಠ\n");\
			printf("Invalid Gender! ");\
			textReset();\
			printf("Enter Student's Gender [MALE or FEMALE ONLY HA!]: ");\
           }while(0)

#define printAlreadyEmpty() do{\
            textRed_B();\
			printf("Already Empty! ");\
           }while(0)

#define printDeleted() do{\
            textGreen_B();\
   			printf("Successfully Deleted! ");\
           }while(0)

#define printAlreadyAdded() do{\
            textRed_B();\
    		printf("Already Added! ");\
           }while(0)

#define printAdded() do{\
            textGreen_B();\
    		printf("Successfully Added! ");\
           }while(0)

#define printFailure() do{\
            textRed_B();\
    		printf("FAILURE! You have exceeded the maximum number of attempts.\n");\
           }while(0)

#define printPressEnter() do{\
            textReset();\
			textNormal_B();\
    		printf("Press ENTER to continue.");\
			textReset();\
           }while(0)

#define printNumberOfStudents() do{\
            textReset();\
    		printf("       Total Number of Students:%d\n",numberOfStudents);\
			printLine();\
           }while(0)

#define showStudentsFormat() do{\
			printf(_bold_ "Name: " _reset_ "%s", student->name);\
			printf(" [" _bold_ "ID:" _reset_ "%hhd]",student->id);\
			printf(" [" _bold_ "Age:" _reset_ "%hhd]",student->age);\
			printf(" [" _bold_ "CGPA:" _reset_ "%g]", student->gpa);\
			printf(" [%s]\n",student->gender);\
           }while(0)

#define showStudentsByGenderFormat() do{\
			printf(_bold_ "Name: " _reset_ "%s", student->name);\
			printf(" [" _bold_ "ID:" _reset_ "%hhd]",student->id);\
			printf(" [" _bold_ "Age:" _reset_ "%hhd]",student->age);\
			printf(" [" _bold_ "CGPA:" _reset_ "%g]\n", student->gpa);\
           }while(0)


//DRAW LINE MACRO
#define printLine()  printf("========================================\n")

//Time Intervals MACROS
#define ProgramTextTime 10000 
#define DevTextTime 30000
#define exitingDotsTime 150000

//SYSTEM INFO TEXTS MACROS
#define programDescription "This  C  code represents a basic School\nManagement  System  program  with user\nauthentication and student data manage-\n-ment features.\n\nIt allows users , primarily admins to log\nin, add, edit, view, or delete student\nrecords.\n"
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

void printStudentInfo(studentData* student);


#endif