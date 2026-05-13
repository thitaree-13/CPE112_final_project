#ifndef BORROW_SYSTEM_H
#define BORROW_SYSTEM_H

#include <stdbool.h>
#include "book_system.h"

// ===== CONSTANT =====

#define MAX_WAITLIST 50

// ===== WAITLIST QUEUE =====

// typedef struct
// {
//     int user_ids[MAX_WAITLIST];

//     int front;
//     int rear;
//     int count;

// } WaitQueue;

// ===== QUEUE FUNCTIONS =====

void initWaitQueue(WaitQueue *q);

bool enqueueWaitlist(WaitQueue *q,
                     int user_id);

int dequeueWaitlist(WaitQueue *q);

// ===== BORROW FUNCTIONS =====

void borrowBook();

void returnBook();

void showMyBooks();

#endif