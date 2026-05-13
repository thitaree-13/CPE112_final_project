#include <stdio.h>

#include "borrow_system.h"
#include "book_system.h"
#include "user_system.h"

// ===== QUEUE FUNCTIONS =====

void initWaitQueue(WaitQueue *q)
{
    q->front = 0;

    q->rear = -1;

    q->count = 0;
}

bool enqueueWaitlist(WaitQueue *q,
                     int user_id)
{
    if (q->count >= MAX_WAITLIST)
    {
        return false;
    }

    q->rear =
        (q->rear + 1) % MAX_WAITLIST;

    q->user_ids[q->rear] = user_id;

    q->count++;

    return true;
}

int dequeueWaitlist(WaitQueue *q)
{
    if (q->count == 0)
    {
        return -1;
    }

    int user_id =
        q->user_ids[q->front];

    q->front =
        (q->front + 1) % MAX_WAITLIST;

    q->count--;

    return user_id;
}

// ===== BORROW BOOK =====

void borrowBook()
{
    if (!isLoggedIn())
    {
        printf("Please login first.\n");
        return;
    }

    int id;

    printf("Enter Book ID: ");
    scanf("%d", &id);

    Book *temp = head;

    while (temp != NULL)
    {
        if (temp->id == id)
        {
            // available
            if (temp->available)
            {
                temp->available = 0;

                temp->borrowedBy =
                    currentUser->userID;

                currentUser->borrowedCount++;

                saveAllUsers();

                saveBooksToFile();

                printf("Book borrowed successfully.\n");

                return;
            }

            // borrowed already
            else
            {
                printf("Book already borrowed.\n");

                char choice;

                printf("Join waitlist? (y/n): ");
                scanf(" %c", &choice);

                if (choice == 'y' ||
                    choice == 'Y')
                {
                    if (enqueueWaitlist(
                            &temp->waitlist,
                            currentUser->userID))
                    {
                        printf("Added to waitlist.\n");
                    }
                    else
                    {
                        printf("Waitlist full.\n");
                    }
                }

                return;
            }
        }

        temp = temp->next;
    }

    printf("Book not found.\n");
}

// ===== RETURN BOOK =====

void returnBook()
{
    if (!isLoggedIn())
    {
        printf("Please login first.\n");
        return;
    }

    int id;

    printf("Enter Book ID: ");
    scanf("%d", &id);

    Book *temp = head;

    while (temp != NULL)
    {
        if (temp->id == id)
        {
            // verify borrower
            if (temp->borrowedBy !=
                currentUser->userID)
            {
                printf("You did not borrow this book.\n");

                return;
            }

            // waitlist exists
            if (temp->waitlist.count > 0)
            {
                int nextUser =
                    dequeueWaitlist(
                        &temp->waitlist);

                temp->borrowedBy =
                    nextUser;

                printf("Book assigned to next waitlist user.\n");
            }
            else
            {
                temp->available = 1;

                temp->borrowedBy = -1;
            }

            currentUser->borrowedCount--;

            saveAllUsers();

            saveBooksToFile();

            printf("Book returned successfully.\n");

            return;
        }

        temp = temp->next;
    }

    printf("Book not found.\n");
}

void showMyBooks()
{
    if (!isLoggedIn())
    {
        printf("Please login first.\n");
        return;
    }

    Book *temp = head;

    printf("\n===== MY BORROWED BOOKS =====\n");

    while (temp != NULL)
    {
        if (temp->borrowedBy == currentUser->userID)
        {
            printf("ID: %d\n", temp->id);
            printf("Title: %s\n", temp->title);
            printf("-------------------\n");
        }

        temp = temp->next;
    }

    printf("\n===== MY WAITLIST =====\n");

    temp = head;

    while (temp != NULL)
    {
        for (int i = 0; i < temp->waitlist.count; i++)
        {
            int index =
                (temp->waitlist.front + i) % MAX_WAITLIST;

            if (temp->waitlist.user_ids[index] == currentUser->userID)
            {
                printf("ID: %d\n", temp->id);
                printf("Title: %s\n", temp->title);
                printf("-------------------\n");
            }
        }

        temp = temp->next;
    }
}