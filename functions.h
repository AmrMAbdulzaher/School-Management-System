/**
 * @file functions.h
 * @brief School Management System Function Declarations
 *
 * This file contains the declarations of functions and constants used in the
 * School Management System program. It includes functions for user authentication,
 * student data management, and menu handling.
 *
 * @details
 *   The constants in this file define important parameters such as admin credentials,
 *   maximum username and password lengths, maximum login attempts, and more.
 *
 * @authors
 *   - Amr Mohamed Abdulzaher (amrnassareng@gmail.com)
 *   - Mohamed Ahmed Shams (mohamed.ah.shams@gmail.com)
 *
 * @date 26-09-2023
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "STD_TYPES.h"

// Constants for admin authentication
#define adminUser "admin"          // Admin username
#define adminPassword "admin"      // Admin password

// Variable Like Macros
#define MAX_USERNAME_LENGTH 20     // Maximum username length
#define MAX_PASSWORD_LENGTH 30     // Maximum password length
#define MAX_LOGIN_ATTEMPTS 4U      // Maximum login attempts allowed
#define MAX_INVALID_INPUT_ATTEMPTS 4U // Maximum invalid input attempts allowed
#define MAX_GRADE 4.0F             // Maximum GPA value
#define MAX_FULL_NAME_LENGTH 50    // Maximum full name length

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "STD_TYPES.h"

// Constants for admin authentication
#define adminUser "admin"          // Admin username
#define adminPassword "admin"      // Admin password

// Variable Like Macros
#define MAX_USERNAME_LENGTH 20     // Maximum username length
#define MAX_PASSWORD_LENGTH 30     // Maximum password length
#define MAX_LOGIN_ATTEMPTS 4U      // Maximum login attempts allowed
#define MAX_INVALID_INPUT_ATTEMPTS 4U // Maximum invalid input attempts allowed
#define MAX_GRADE 4.0F             // Maximum GPA value
#define MAX_FULL_NAME_LENGTH 50    // Maximum full name length
#define MIN_FULL_NAME_LENGTH 2    // Maximum full name length
#define WRONG_GPA -1.0             // Special value to indicate invalid GPA
// Functions Like Macros
#define clearBuffer() while (getchar() != '\n')

// Data structure representing a student
typedef struct student
{
    char name[MAX_FULL_NAME_LENGTH]; // Student's full name
    sint8 age;                      // Student's age
    char gender[6];                 // Student's gender
    uint32 id;                      // Student's ID
    f32 gpa;						// Student's GPA
    struct student* link;           // Pointer to the next student in the list
} studentData;
	
// Function prototypes
void free_Students(studentData* start);               // Free memory used by student data
void mainMenu(void);                                  // Display the main menu
void loginScanAndCheck(char *user, char *pass);       // Scan and check user login
void loginPanel(void);                                // Display the login panel
void loginAgain(void);                                // Prompt for login again
void adminMenu(void);                                 // Display the admin menu
uint8 isValidID(sint32* inputData);                     // Check if an ID is valid
uint8 isValidName(const char *name);                  // Check if string is valid
uint8 isValidFullName(char* fullName);                     // Check if a full name is valid
uint8 isValidAge(sint8* inputAge);   // Check if an age is valid
uint8 isValidGender(char* inputGender); // Check if a gender is valid
uint8 isValidGPA(f32* inputGPA);     // Check if a GPA is valid
uint8 collectInfo(studentData* newStudent);       // Scan and check student information
void insertStudentAtEnd(studentData** start, studentData* newStudent);
uint8 duplicateStudent(studentData* start, sint32 id);
void addStudent(studentData** start);                 // Add a new student
void editStudent(studentData* start);                 // Edit student information
void showStudents(studentData* start);                // Display all students
void showStudentsByGender(studentData* start);        // Display students by gender
void showStudentByID(studentData* start);             // Display a student by ID
void deleteStudent(studentData** start);              // Delete a student
void aboutMenu(void);                                 // Display the about menu
void exitSystem(void);                                // Exit the system

#endif
