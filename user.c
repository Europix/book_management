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
};

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
