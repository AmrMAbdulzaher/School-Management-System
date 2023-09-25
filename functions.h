#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "STD_TYPES.h"

#define adminUser "admin"
#define adminPassword "admin"
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 30
#define MAX_LOGIN_ATTEMPTS 4U
#define MAX_INVALID_INPUT_ATTEMPTS 4U
#define MAX_GRADE 4.0F
#define MAX_FULL_NAME_LENGTH 60
#define WRONG_GPA -1.0

typedef struct student
{
	char name[MAX_FULL_NAME_LENGTH];
	sint8 age;
	char gender[6];
	uint32 id;
	f32 gpa;
	struct student* link;
}studentData;

void free_Students(studentData* start);

void mainMenu(void);

void loginScanAndCheck(char *user, char *pass);

void loginPanel(void);

void loginAgain(void);

void adminMenu(void);

uint8 validID(sint32* inputData);

uint8 isValidName(const char *name);

uint8 Check_Name(char* fullName);

uint8 Check_Age(sint8* inputAge,uint8* scanReturn);

uint8 Check_Gender(char* inputGender,uint8* scanReturn);

uint8 Check_GPA(f32* inputGPA,uint8* scanReturn);

uint8 Scan_Check_Info(studentData* newStudent);

void addStudent(studentData** start);

void editStudent(studentData* start);

void showStudents(studentData* start);

void showStudentsByGender(studentData* start);

void showStudentByID(studentData* start);

void deleteStudent(studentData** start);

void aboutMenu(void);

void exitSystem(void);

#endif