#include "user.h"
#include "book_management.h"
#include <stdlib.h>
#include <string.h>

int user_register(char u[],char p[]){
    for(int i=1;i<=userct;i++){
        if(!strcmp(u,users[i].username))return 0;
    }//same username
    userct++;
    strcpy(users[userct].username,u);
    strcpy(users[userct].password,p);
    users[userct].id=userct;
    users[userct].priority=0;
    return 1; //1 for success
}

//struct User user_del(int x){
//no need for delete :D

int login(char u[],char p[]){
    for(int i=1;i<=userct;i++){
        if(!strcmp(u,users[i].username)){
            if(!strcmp(p,users[i].password))return users[i].id; //success
            else return 0; // wrong password
        }
    }
    return -1; //username not found
}

int store_books(){
    FILE* fp = fopen("books.txt", "wb");
	if(fp==NULL){
        return 0;
	}
    fwrite(&bookct,sizeof(int),1,fp);
    fwrite(&userct,sizeof(int),1,fp);
    for(int i=1;i<=bookct;i++){
        fwrite(&books[i],sizeof(Book),1,fp);
    }
    for(int i=1;i<=userct;i++){
        fwrite(&users[i],sizeof(User),1,fp);
    }
    fclose(fp);
    return 1;
}

int load_books(){
        FILE* fp = fopen("books.txt", "rb");
        if(fp==NULL){
            return 0;
        }
        fread(&bookct,sizeof(int),1,fp);
        fread(&userct,sizeof(int),1,fp);
        for(int i=1;i<=bookct;i++){
            fread(&books[i],sizeof(Book),1,fp);
        }
        for(int i=1;i<=userct;i++){
            fread(&users[i],sizeof(User),1,fp);
        }
        fclose(fp);
        return 1;
}

