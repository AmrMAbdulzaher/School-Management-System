#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "STD_TYPES.h"

#define adminUser "admin"
#define adminPassword "admin"
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 30
#define MAX_LOGIN_ATTEMPTS 4U
#define MAX_GRADE (4.0F)

typedef struct student
{
	char name[30];
	unsigned int id;
	float gpa;
	struct student* link;
}studentData;

void free_Students(studentData* start);

void mainMenu(void);

void loginScanAndCheck(char *user, char *pass);

void loginPanel(void);

void loginAgain(void);

void adminMenu(void);

uint8 validID(sint32* inputData);

f32 scanGPA(void);

void addInfo(studentData* newStudent);

void addStudent(studentData** start);

void editStudent(studentData* start);

void showStudents(studentData* start);

void showStudentByID(studentData* start);

void deleteStudent(studentData** start);

void aboutMenu(void);

void exitSystem(void);

#endif