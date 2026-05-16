#ifndef BOOK_SYSTEM_H
#define BOOK_SYSTEM_H

// ===== WAITLIST =====
#include <stdbool.h>
#define MAX_WAITLIST 50


typedef struct
{
    int user_ids[MAX_WAITLIST];

    int front;
    int rear;
    int count;

} WaitQueue;

// ===== BOOK STRUCT =====

typedef struct Book
{
    int id;

    char title[100];
    char author[100];
    char category[50];

    int available;

    // borrow system
    int borrowedBy;

    WaitQueue waitlist;

    // linked list
    struct Book* next;

    // hash table
    struct Book* hashNext;

} Book;

// ===== GLOBAL =====

extern Book* head;

// ===== FUNCTIONS =====

void addBook();

void deleteBook();

void displayBooks();

void saveBooksToFile();

void loadBooksFromFile();

#endif