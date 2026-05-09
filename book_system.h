#ifndef BORROW_SYSTEM_H
#define BORROW_SYSTEM_H

#include <stdbool.h>

//constant

#define MAX_BOOKS 100
#define MAX_TITLE_LEN 100
#define MAX_WAITLIST 50

//new
#define MAX_USERS 100
#define MAX_BORROW_LIMIT 5

//waiting queue

typedef struct {
    int user_ids[MAX_WAITLIST];
    int front;
    int rear;
    int count;
} WaitQueue;

//book

typedef struct {

    int book_id;

    char title[MAX_TITLE_LEN];

    bool is_borrowed;

    int borrowed_by;

    WaitQueue waitlist;

} Book;

//lib

typedef struct {

    Book books[MAX_BOOKS];

    int book_count;

    //new
    int user_borrow_count[MAX_USERS];

} Library;

//function

void library_init(Library *lib);

int library_add_book(Library *lib,
                     const char *title);

bool borrow_book(Library *lib,
                 int book_id,
                 int user_id);

bool return_book(Library *lib,
                 int book_id,
                 int user_id);

bool join_waitlist(Library *lib,
                   int book_id,
                   int user_id);

bool is_book_available(Library *lib,
                       int book_id);

int get_waitlist_count(Library *lib,
                       int book_id);

#endif