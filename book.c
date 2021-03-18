#include "book_management.h"
#include "user.h"
#include <stdlib.h>
#include <string.h>

struct Book answer[Max];
void book_add(char t[],char a[], int y){
    bookct++;
    strcpy(books[bookct].title,t);
    strcpy(books[bookct].author,a);
    books[bookct].yop=y;
    books[bookct].id=bookct;
    books[bookct].stat=0;
}// unable to fail adding, so void is applied

int book_del(int d){
    if(books[d].id==0)return 0; //not find
    books[d].stat=-1;
    return 1;
}
// save the deleted id for better managing
int findbook(char a[], int ca){
    int ct=1;
    memset(answer,0,sizeof(answer));
    if (ca==1){
        for(int i=1;i<=bookct;i++){
            if(!strcmp(a,books[i].title) && books[i].stat != -1){
                answer[ct]=books[i];
                ct++;
            }
        }
    }
    if(ca==2){
        for(int i=1;i<=bookct;i++){
            if(!strcmp(a,books[i].author) && books[i].stat != -1){
                answer[ct]=books[i];
                ct++;
            }
        }
    }
    if(ca==3){
        int y=atoi(a);
        for(int i=1;i<=bookct;i++){
            if(y==books[i].yop && books[i].stat != -1){
                answer[ct]=books[i];
                ct++;
            }
        }
    }
    return ct;
}

int borrow_book(int userid, int bookid){
    if(userid<=0 || bookid<=0)return 0;
    if(users[userid].id==0 || books[bookid].id==0 || books[bookid].stat== -1)return 0; //failure
    if(books[bookid].stat>0)return 0-books[bookid].stat; // have been borrowed by user
    users[userid].borrowed++;
    users[userid].borrow[borrowed]=bookid;
    books[bookid].stat=userid;
    return 1; //success
}

int return_book(int userid, int bookid){
    if(userid<=0 || bookid<=0)return 0;
    if(users[userid].id==0 || books[bookid].id==0 || books[bookid].stat== -1)return 0; //failure
    for(int i=1; i<=users[userid].borrowed ; i++){
        if(users[userid].borrow[i]==bookid){
            users[userid].borrow[i]=0; // return
            for(j=i ; j<=users[userid].borrowed ; j++){
                users[userid].borrow[j] = users[userid].borrow[j+1]; // change position
            }
            users[userid].borrowed--;
            books[bookid].stat=0; // initialize
            return 1; //success
        }
    }
    return -1; // book not found in given user.
}
