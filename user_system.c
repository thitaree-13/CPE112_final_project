#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_system.h"

// ===== GLOBAL =====
User *userHead = NULL;
User *currentUser = NULL;

// ===== LOAD USERS FROM FILE =====
void loadUsers()
{

    FILE *fp = fopen("User.txt", "r");

    if (fp == NULL)
    {
        return;
    }

    User temp;

    while (fscanf(fp, "%d %s %s %d",
                  &temp.userID,
                  temp.username,
                  temp.password,
                  &temp.borrowedCount) == 4)
    {

        User *newUser = (User *)malloc(sizeof(User));
        if (newUser == NULL)
        {
            printf("Memory allocation failed.\n");
            return;
        }

        *newUser = temp;
        newUser->next = NULL;

        // add to linked list
        if (userHead == NULL)
        {
            userHead = newUser;
        }
        else
        {
            User *current = userHead;

            while (current->next != NULL)
            {
                current = current->next;
            }

            current->next = newUser;
        }
    }

    fclose(fp);
}

// ===== SAVE USER =====
void saveUser(User *user)
{

    FILE *fp = fopen("User.txt", "a");

    if (fp == NULL)
    {
        printf("Cannot open file.\n");
        return;
    }

    fprintf(fp, "%d %s %s %d\n",
            user->userID,
            user->username,
            user->password,
            user->borrowedCount);

    fclose(fp);
}

// ===== REGISTER =====
void registerUser()
{

    char name[50];
    char pass[50];

    printf("Create username: ");
    scanf("%49s", name);

    // check duplicate
    User *current = userHead;

    while (current != NULL)
    {

        if (strcmp(current->username, name) == 0)
        {
            printf("Username already used.\n");
            return;
        }

        current = current->next;
    }

    printf("Create password: ");
    scanf("%49s", pass);

    // create new user
    User *newUser = (User *)malloc(sizeof(User));
    if (newUser == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    // generate userID
    int newID = 1;

    current = userHead;

    while (current != NULL)
    {

        if (current->userID >= newID)
        {
            newID = current->userID + 1;
        }

        current = current->next;
    }

    newUser->userID = newID;

    strcpy(newUser->username, name);
    strcpy(newUser->password, pass);

    newUser->borrowedCount = 0;

    newUser->next = NULL;

    // add to linked list
    if (userHead == NULL)
    {
        userHead = newUser;
    }
    else
    {
        current = userHead;

        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = newUser;
    }

    // save to file
    saveUser(newUser);

    // auto login
    currentUser = newUser;

    printf("Register success.\n");
    printf("Welcome %s\n", currentUser->username);
}

// ===== LOGIN =====
void loginUser()
{
    if (currentUser != NULL)
    {
        printf("Another user already logged in.\n");
        return;
    }

    char name[50];
    char pass[50];

    printf("Username: ");
    scanf("%49s", name);

    printf("Password: ");
    scanf("%49s", pass);

    User *current = userHead;

    while (current != NULL)
    {

        if (strcmp(current->username, name) == 0 &&
            strcmp(current->password, pass) == 0)
        {

            currentUser = current;

            printf("Login success. Welcome %s\n", currentUser->username);
            return;
        }

        current = current->next;
    }

    printf("Wrong username or password.\n");
}

// ===== LOGOUT =====
void logoutUser()
{

    currentUser = NULL;

    printf("Logged out.\n");
}

// ===== CHECK LOGIN =====
int isLoggedIn()
{

    return currentUser != NULL;
}

// ===== DISPLAY USERS =====
void displayUsers()
{

    User *current = userHead;

    if (current == NULL)

    {

        printf("No users found.\n");

        return;
    }

    while (current != NULL)
    {

        printf("ID: %d\n", current->userID);
        printf("Username: %s\n", current->username);
        printf("Borrowed: %d\n", current->borrowedCount);

        printf("-------------------\n");

        current = current->next;
    }
}

void saveAllUsers()
{
    FILE *fp = fopen("User.txt", "w");

    if (fp == NULL)
    {
        printf("Cannot open file.\n");
        return;
    }

    User *current = userHead;

    while (current != NULL)
    {
        fprintf(fp,
                "%d %s %s %d\n",
                current->userID,
                current->username,
                current->password,
                current->borrowedCount);

        current = current->next;
    }

    fclose(fp);
}