#include <stdio.h>
#include <stdlib.h>
#include "borrow_system.h"
#include "book_system.h"
#include "user_system.h"

// ===== QUEUE STRUCT =====
typedef struct Queue
{
    int userID;
    struct Queue *next;
} Queue;

// ===== GLOBAL QUEUE =====
Queue *front = NULL;
Queue *rear = NULL;

// ===== QUEUE FUNCTIONS =====
void enqueue(int userID)
{
    // TODO: create new node
    // TODO: add to rear
}

void dequeue()
{
    // TODO: remove from front
    // TODO: free memory
}

// ===== MAIN FUNCTIONS =====
void borrowBook()
{
    if (!isLoggedIn())
    {
        printf("Please login first!\n");
        return;
    }
    // TODO: find book by ID

    // IF available:
    //    mark as borrowed

    // ELSE:
    //    add user to queue
}

void returnBook()
{
    // TODO: find book

    // IF queue not empty:
    //    give book to next user

    // ELSE:
    //    mark book as available
}