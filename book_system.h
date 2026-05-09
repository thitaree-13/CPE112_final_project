#ifndef BOOK_SYSTEM_H
#define BOOK_SYSTEM_H

typedef struct Book
{
    int id;

    char title[100];
    char author[100];
    char category[50];

    int available;

    // linked list pointer
    struct Book* next;

    // hash table pointer
    struct Book* hashNext;

} Book;

// global head
extern Book* head;

// functions
void addBook();
void deleteBook();
void displayBooks();

// file handling
void saveBooksToFile();
void loadBooksFromFile();

#endif