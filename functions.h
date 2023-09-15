#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define adminUser "admin"
#define adminPassword "admin"

#define MAXSTUDENTS 10
#define INDEX inputID-1

typedef struct student
{
    char name[20];
    unsigned char id;
    float gpa;
} studentData;

void systemheader(void);
void mainMenu(void);
void loginPanel(char *user, char *pass);
void loginAgain(void);
void adminMenu(studentData student[]);
void addStudent(studentData student[]);
void editStudent(studentData student[]);
void showStudents(studentData student[]);
void deleteStudent(studentData student[]);
void aboutMenu(void);
void exitSystem(void);
