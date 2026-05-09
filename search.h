// #ifndef SEARCH_H
// #define SEARCH_H

// void searchBook();

// #endif

#ifndef HASH_SEARCH_H
#define HASH_SEARCH_H

#include "book_system.h"

// size of our hash table
#define TABLE_SIZE 100

// the hash table is an array of Book pointers
// each slot can hold a chain of books (for collision)
extern Book* hashTable[TABLE_SIZE];

// hash table functions
void initHashTable(void);
int  hashFunction(int id);
void insertHash(Book* book);
void deleteHash(int id);

// search functions
Book* searchByID(int id);
void  searchByTitle(Book* head, const char* title);
void  searchByAuthor(Book* head, const char* author);
void  searchByCategory(Book* head, const char* category);
void  searchByAvailability(Book* head, int available); // 1 = available, 0 = borrowed

// sort functions
void sortBooksByTitle(Book* head);
void sortBooksByID(Book* head);

#endif