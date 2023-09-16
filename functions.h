#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define adminUser "admin"
#define adminPassword "admin"

#define MAX_STUDENTS 10


typedef struct student
{
	char name[30];
	unsigned int id;
	float gpa;
	unsigned char added;
	struct student* link;
}studentData;

void free_Students(studentData* start);
void systemheader(void);
void mainMenu(void);
void loginPanel(char *user, char *pass);
void loginAgain(void);
void adminMenu(void);
void addStudent(studentData** start);
void editStudent(studentData* start);
void showStudents(studentData* start);
void showStudentByID(studentData* start);
void deleteStudent(studentData** start);
void aboutMenu(void);
void exitSystem(void);
