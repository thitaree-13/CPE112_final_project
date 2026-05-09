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
    struct Book* hashNext;

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

void saveBooksToFile();
void loadBooksFromFile();

#endif