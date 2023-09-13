#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define adminUser "admin"
#define adminPassword "imtheboss"
#define studentUser "ahmed"
#define studentPassword "1234"

#define MAXSTUDENTS 10
#define TRUE 1

typedef struct
{
    char name[20];
    unsigned char id;
    float gpa;
} studentData;

void printExiting(void);
void systemheader(void);
void mainMenu(void);
void displayAdminMenu(void);
void loginPanel(char *user, char *pass);
void loginAgain(void);
void adminPanel(studentData student[]);
void studentPanel(void);
void addStudent(studentData student[]);
void editStudent(studentData student[]);
void showStudents(studentData student[]);
void deleteStudent(studentData student[]);
void printAboutUs(void);