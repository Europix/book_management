#define Max 10000
struct User{
    int id;
    char name[Max];
    char username[Max];
    char password[Max];
    int priority; // users' priority=0 & Librarian's priority=1.
    int borrow[Max];
    int borrowed;
};

struct Book{
    int id;
    char title[Max];
    char author[Max];
    int yop; // year of publication
    int stat; //stat=0 for not been borrowed, stat=p for borrowed by person with id p, stat=-1 for deleted.
   // int length; // length=0 for not been borrowed, length>0 for days have been borrowed;
};

extern Book books[Max*10];
extern User users[Max];
extern int userct; // counter
extern int bookct;
