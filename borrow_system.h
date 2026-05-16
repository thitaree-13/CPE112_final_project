#ifndef BORROW_SYSTEM_H
#define BORROW_SYSTEM_H

#include <stdbool.h>
#include"book_system.h"

void initWaitQueue(WaitQueue *q);

bool enqueueWaitlist(WaitQueue *q,
                     int user_id);

int dequeueWaitlist(WaitQueue *q);

void borrowBook();
void returnBook();

void showMyBooks();

#endif