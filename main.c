#include "book_management.h"
#include "user.h"
#include "user.c"
#include "book.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void initial(int type){
    strcpy(users[1].username,"librarian");
    strcpy(users[1].password,"librarian");
    users[1].id=1;
    users[1].priority=1;
    userct=1;
    bookct=0;
    if(type==1){
        bookct=3;
        strcpy(books[1].author, "Haha");
        strcpy(books[1].title, "China");
        books[1].id=1;
        books[1].yop=1926;
        books[1].stat=0;
        books[1].copies=9;
        strcpy(books[2].author, "Fak");
        strcpy(books[2].title, "Jspan");
        books[2].id=2;
        books[2].yop=1926;
        books[2].stat=0;
        books[2].copies=89;
        strcpy(books[3].author, "Xixixixi");
        strcpy(books[3].title, "testtestyixia");
        books[3].id=3;
        books[3].yop=1936;
        books[3].stat=0;
        books[3].copies=0;
    }
}
int main(){
    int c;
    initial(1);
    int log=0;
    char s1[300];
    char s2[300];
    while(1){
            if(log==0)printf("Please choose an option:\n 1)Register an account\n 2)Login\n 3)Search for books\n 4)Display all books\n 5)Quit\nOption:");
            if(log>=2)printf("Please choose an option:\n 1)Borrow a book\n 2)Return a book\n 3)Search for books\n 4)Display all books\n 5)Sign out\nOption:");
            if(log==1)printf("You are librarian, please choose an option:\n 1)Add a new book\n 2)Delete a book\n 3)Search for books\n 4)Display all books\n 5)Sign out\nOption:");
            scanf("%d",&c);
            if(c==1&& log==0){
                printf("Please enter your username(Max 150 characters):");
                scanf("%s",s1);
                printf("Please enter your password(Max 150 characters):");
                scanf("%s",s2);
                int r1=user_register(s1,s2);
                if(r1)printf("Success!\n");
                else printf("Failed to register. Invalid username.\n");
            }
            if(c==1 && log==1){
                printf("Please input the name(title) of the book(Max 150 characters):");
                char new_title[152],new_author[152];
                int new_copy,new_yop;
                getchar();
                scanf("%[^\n]",new_title);
                printf("Please input the authors of the book(Max 150 characters):");
                getchar();
                scanf("%[^\n]",new_author);
                printf("Please input the copies of the book:");
                scanf("%d",&new_copy);
                printf("Please input the publish year of the book:");
                scanf("%d",&new_yop);
                int rr=book_add(new_title,new_author,new_yop,new_copy);
                printf("Successfully added the book with ID %d\n",rr);
            }
            if(c==1 && log>=2){
                    int bor;
                printf("Please enter the ID of the book which you want to borrow:");
                scanf("%d",&bor);
                int z=borrow_book(log,bor);
                if(z){
                        printf("Successfully borrowed book ID %d!\n",bor);
                }
                if(z==0){
                    printf("Failed to borrow the book. Please try again. \n");
                }
                if(z==-1){
                    printf("The book has been borrowed by other users, please try again later!\n");
                }
                if(z==-2){
                    printf("You have already borrowed this book!\n");
                }
                if(z==-5){
                    printf("You have borrowed too many books, please return them before borrowing new one.\n");
                }

            }
            if(c==2 && log==0){
                    printf("Please enter your username:");
                    scanf("%s",s1);
                    printf("Please enter your password:");
                    scanf("%s",s2);
                    int r2=login(s1,s2);
                    if(r2>=1){
                            printf("Welcome, %s!\n",users[r2].username);
                            log=r2;
                    }
                    if(r2==-1)printf("Username not found!\n");
                    if(r2==0)printf("Wrong password!\n");
                    continue;
            }
            if(c==2 && log==1){
                printf("Please enter the ID of the book which you want to delete:");
                int de;
                scanf("%d",&de);
                if(book_del(de))printf("Successfully deleted book %d which named %s\n",de,books[de].title);
                else printf("Failed to delete, please try again.\n");
            }
            if(c==2 && log>=2){
                printf("You have borrowed %d books.\n",users[log].borrowed);
                printf("ID\tTitle\t\tAuthor\t\tYear of Publication\n");
                for(int i=1;i<=users[log].borrowed;i++){
                    printf("%d\t%-8s\t%-8s\t%4d\n",users[log].borrow[i],books[users[log].borrow[i]].title,books[users[log].borrow[i]].author,books[users[log].borrow[i]].yop);
                }
                printf("Please enter the book ID you want to return:");
                int ret;
                scanf("%d",&ret);
                int p=return_book(log,ret);
                if(p==0)printf("Failed to return, please try again!\n");
                if(p==1)printf("Successfully returned book %d!\n",ret);
                if(p==-1)printf("You haven't borrowed this book!\n");
            }
            if(c==3){
                printf("Choose the way you want to search:\n 1)Search by Title\n 2)Search by author\n 3)Search by publication year\n");
                int d;
                char se[152];
                scanf("%d",&d);
                getchar();
                printf("Please input the content you want to search(Max 150 character):");
                scanf("%[^\n]",se);
                int r3=findbook(se,d);
                if(r3==0)printf("No search results! \n");
                else{
                    printf("Find %d books. \nID\tTitle\t\tAuthor\t\tCopies\tYear of Publication\n", r3 );
                        for(int ii=0;ii<r3;ii++){
                        printf("%d\t%-8s\t%-8s\t%4d\t%4d\n",answer[ii].id,answer[ii].title,answer[ii].author,answer[ii].copies,answer[ii].yop);
                    }
                }

            }
            if(c==4){
                printf("ID\tTitle\t\tAuthor\t\tCopies\tYear of Publication\n");
                    for(int i=1;i<=bookct;i++){
                        if(books[i].stat!=-1){
                        printf("%d\t%-8s\t%-8s\t%4d\t%4d\n",i,books[i].title,books[i].author,books[i].copies,books[i].yop);
                    }
                    }

            }
            if(c==5){
                if(log==0)return 0;
                else log=0;
            }
            else if(c!=1 && c!=2 && c!=3 && c!=4 && c!=5){
                    printf("Invalid input, please try again!\n");
                    continue;
            }
    }






    return 0;
}
