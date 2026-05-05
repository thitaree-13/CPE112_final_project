#ifndef USER_SYSTEM_H
#define USER_SYSTEM_H

// ===== STRUCT =====
typedef struct User {
    int userID;
    char username[50];
    char password[50];
    int borrowedCount;
    struct User* next;
} User;

// ===== GLOBAL =====
extern User* userHead;
extern User* currentUser;

// ===== FUNCTIONS =====
void registerUser();
void loginUser();
void logoutUser();
int isLoggedIn();

#endif