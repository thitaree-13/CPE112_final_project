#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_system.h"

// ===== GLOBAL =====
User* userHead = NULL;
User* currentUser = NULL;

// ===== FUNCTIONS =====

void registerUser() {
    // TODO:
    // create new user
    // input username/password
    // add to linked list
    char name[50],pass[50];
    char filename[50],filepass[50];
    FILE *fp;
    int found = 0;

    printf("Create a username[50 characters limit] : ");
    scanf("%s",name);

    fp = fopen("User.txt", "r");
        if (fp == NULL) {
            printf("Cannot open file.\n");
            return 1;
        }
        found = 0;

        while (fscanf(fp, "%s %s", filename, filepass) == 2) {

            if (strcmp(name,filename)==0) {
                found = 1;
                break;
            }
        }

    fclose(fp);

    while(found == 1||strlen(name)>50){
        if(found==1){
            printf("***This username was used***\n");
        }
        if(strlen(name)>50){
            printf("***This username is too long***");
        }
        printf("Create a username[50 characters limit] : ");
        scanf("%s",name);

        fp = fopen("User.txt", "r");
            if (fp == NULL) {
                printf("Cannot open file.\n");
                return 1;
            }
            found = 0;

            while (fscanf(fp, "%s %s", filename, filepass) == 2) {

                if (strcmp(name,filename)==0) {
                    found = 1;
                    break;
                }
            }

        fclose(fp);
    }

    printf("Create a password[50 characters limit] ; ");
    scanf("%s",pass);

    while(strlen(pass)>50){
        printf("***The password is too long***\nCreate the password[50 characters limit] ; ");
        scanf("%s",pass);
    }

    strcpy(currentUser->username,name);
    strcpy(currentUser->password,pass);

    fp = fopen("User.txt", "a");
        if (fp == NULL) {
            printf("Cannot open file.\n");
            return 1;
        }
        
        fprintf(fp,"%s %s\n",name,pass);

        fclose(fp);
}

void loginUser() {
    // TODO:
    // ask username/password
    // search user list
    // if match → set currentUser
    char name[20],pass[20];
    char filename[20],filepass[20];
    FILE *fp;
    int found = 0;

    printf("Enter user name : ");
    scanf("%s",name);

    fp = fopen("User.txt", "r");
        if (fp == NULL) {
            printf("Cannot open file.\n");
            return 1;
        }
        found = 0;

        while (fscanf(fp, "%s %s", filename, filepass) == 2) {

            if (strcmp(name,filename)==0) {
                found = 1;
                break;
            }
        }

    fclose(fp);

    while(found == 0){
        printf("***User do not found***\nEnter user name : ");
        scanf("%s",name);

        fp = fopen("User.txt", "r");
            if (fp == NULL) {
                printf("Cannot open file.\n");
                return 1;
            }
            found = 0;

            while (fscanf(fp, "%s %s", filename, filepass) == 2) {

                if (strcmp(name,filename)==0) {
                    found = 1;
                    break;
                }
            }

        fclose(fp);
    }

    printf("Enter user password : ");
    scanf("%s",pass);

    while(strcmp(pass,filepass)!=0){
        printf("***Wrong password***\nEnter the password : ");
        scanf("%s",pass);
    }

    strcpy(currentUser->username,filename);
    strcpy(currentUser->password,filepass);
}

void logoutUser() {
    currentUser = NULL;
    printf("Logged out.\n");
}

int isLoggedIn() {
    return currentUser != NULL;
}