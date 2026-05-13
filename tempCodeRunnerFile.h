#ifndef BOOK_SYSTEM_H
#define BOOK_SYSTEM_H

// ===== STRUCT =====
typedef struct Book {
    int id;
    char title[100];
    char author[100];
    char category[50];
    int available;          // 1 = available, 0 = borrowed
    struct Book* next;
} Book;

// ===== GLOBAL HEAD =====
extern Book* head;

// ===== FUNCTIONS =====
void addBook();
void deleteBook();
void displayBooks();

#endif