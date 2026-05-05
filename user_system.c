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
}

void loginUser() {
    // TODO:
    // ask username/password
    // search user list
    // if match → set currentUser
}

void logoutUser() {
    currentUser = NULL;
    printf("Logged out.\n");
}

int isLoggedIn() {
    return currentUser != NULL;
}