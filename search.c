#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "search.h"
#include "book_system.h"

// our hash table array
Book* hashTable[TABLE_SIZE];

// set all slots to NULL at the start
void initHashTable(void) {
    int i;
    for (i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

// simple hash function: use book ID mod table size
int hashFunction(int id) {
    return id % TABLE_SIZE;
}

// insert a book into the hash table // chaining, bucket
void insertHash(Book* book) {
    int index = hashFunction(book->id);

    // put book at front of chain (no malloc needed, book already exists)
    book->hashNext = hashTable[index];
    hashTable[index] = book;
}

// delete a book from hash table by ID
void deleteHash(int id) {
    int index = hashFunction(id);

    Book* curr = hashTable[index];
    Book* prev = NULL;

    while (curr != NULL) {
        if (curr->id == id) {
            if (prev == NULL) {
                hashTable[index] = curr->hashNext;
            } else {
                prev->hashNext = curr->hashNext;
            }
            printf("Book ID %d removed from hash table.\n", id);
            return;
        }
        prev = curr;
        curr = curr->hashNext;
    }

    printf("Book ID %d not found.\n", id);
}

// search book by ID using hash table - this is O(1) average
Book* searchByID(int id) {
    int index = hashFunction(id);
    Book* temp = hashTable[index];

    while (temp != NULL) {
        if (temp->id == id) {
            return temp; // found!
        }
        temp = temp->hashNext;
    }

    return NULL; // not found
}

// ------------------------------------------------
// helper functions (only used inside this file)
// ------------------------------------------------

// lower and upper case
static int containsIgnoreCase(const char* haystack, const char* needle) {
    if (needle[0] == '\0') return 1;

    char lowerHay[256], lowerNeedle[256];
    int i;

    for (i = 0; haystack[i]; i++)
        lowerHay[i] = tolower((unsigned char)haystack[i]);
    lowerHay[i] = '\0';

    for (i = 0; needle[i]; i++)
        lowerNeedle[i] = tolower((unsigned char)needle[i]);
    lowerNeedle[i] = '\0';

    return strstr(lowerHay, lowerNeedle) != NULL;
}

// print one book details
void printBook(const Book* book) {
    printf("-----------------------------\n");
    printf("ID       : %d\n",  book->id);
    printf("Title    : %s\n",  book->title);
    printf("Author   : %s\n",  book->author);
    printf("Category : %s\n",  book->category);
    printf("Status   : %s\n",  book->available ? "Available" : "Borrowed");
    printf("-----------------------------\n");
}

// we use this enum so we don't need 3 separate search functions
// just pass which field you want to search
typedef enum { FIELD_TITLE, FIELD_AUTHOR, FIELD_CATEGORY } SearchField;

static void searchByField(Book* head, const char* query, SearchField field) {
    Book* temp = head;
    int count = 0;

    while (temp != NULL) {
        // pick which field to check
        const char* target = NULL;
        if (field == FIELD_TITLE)         target = temp->title;
        else if (field == FIELD_AUTHOR)   target = temp->author;
        else if (field == FIELD_CATEGORY) target = temp->category;

        // check if query matches
        if (containsIgnoreCase(target, query)) {
            if (count == 0) {
                printf("\n===== Search Results =====\n");
            }
            printBook(temp);
            count++;
        }
        temp = temp->next;
    }

    if (count == 0) {
        printf("\nNo books found matching \"%s\".\n", query);
    } else {
        printf("Total: %d book(s) found.\n", count);
    }
}

// ------------------------------------------------
// search functions (these call searchByField)
// ------------------------------------------------

void searchByTitle(Book* head, const char* title) {
    searchByField(head, title, FIELD_TITLE);
}

void searchByAuthor(Book* head, const char* author) {
    searchByField(head, author, FIELD_AUTHOR);
}

void searchByCategory(Book* head, const char* category) {
    searchByField(head, category, FIELD_CATEGORY);
}

// show only available or only borrowed books
// available = 1 means show available books
// available = 0 means show borrowed books
void searchByAvailability(Book* head, int available) {
    Book* temp = head;
    int count = 0;

    while (temp != NULL) {
        if (temp->available == available) {
            if (count == 0) {
                printf("\n===== %s Books =====\n", available ? "Available" : "Borrowed");
            }
            printBook(temp);
            count++;
        }
        temp = temp->next;
    }

    if (count == 0) {
        printf("\nNo %s books found.\n", available ? "available" : "borrowed");
    } else {
        printf("Total: %d book(s).\n", count);
    }
}

// ------------------------------------------------
// quicksort (pivot, low, high) --- Sorted Book
// ------------------------------------------------

// convert linked list to array
static Book** buildArray(Book* head, int* n) {
    *n = 0;
    Book* temp = head;
    while (temp != NULL) {
        (*n)++;
        temp = temp->next;
    }
    if (*n == 0) return NULL;

    Book** arr = (Book**)malloc((*n) * sizeof(Book*));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    temp = head;
    int i = 0;
    while (temp != NULL) {
        arr[i] = temp;
        i++;
        temp = temp->next;
    }

    return arr;
}

// swap two book pointers in array
static void swapBooks(Book** a, Book** b) {
    Book* temp = *a;
    *a = *b;
    *b = temp;
}

// Sort by Title
static int partitionByTitle(Book** arr, int low, int high) {
    Book* pivot = arr[high];
    int i = low - 1; 

    int j;
    for (j = low; j < high; j++) {

        if (strcasecmp(arr[j]->title, pivot->title) < 0) {
            i++;
            swapBooks(&arr[i], &arr[j]);
        }
    }


    swapBooks(&arr[i + 1], &arr[high]);
    return i + 1; 
}

// quicksort by title (recursive)
static void quickSortByTitle(Book** arr, int low, int high) {
    if (low < high) {
      
        int pivot = partitionByTitle(arr, low, high);

        quickSortByTitle(arr, low, pivot - 1);

        quickSortByTitle(arr, pivot + 1, high);
    }
}

// Sort by ID 
static int partitionByID(Book** arr, int low, int high) {
    Book* pivot = arr[high];
    int i = low - 1;

    int j;
    for (j = low; j < high; j++) {

        if (arr[j]->id < pivot->id) {
            i++;
            swapBooks(&arr[i], &arr[j]);
        }
    }

    swapBooks(&arr[i + 1], &arr[high]);
    return i + 1;
}

// quicksort by ID (recursive)
static void quickSortByID(Book** arr, int low, int high) {
    if (low < high) {
        int pivot = partitionByID(arr, low, high);

        quickSortByID(arr, low, pivot - 1);

        quickSortByID(arr, pivot + 1, high);
    }
}

// sort functions

void sortBooksByTitle(Book* head) {
    int n;
    Book** arr = buildArray(head, &n);

    if (arr == NULL) {
        printf("\nNo books to sort!\n");
        return;
    }

    quickSortByTitle(arr, 0, n - 1);

    printf("\n===== Books Sorted by Title =====\n");
    int i;
    for (i = 0; i < n; i++) {
        printBook(arr[i]);
    }
    printf("Total: %d book(s).\n", n);

    free(arr);
}

void sortBooksByID(Book* head) {
    int n;
    Book** arr = buildArray(head, &n);

    if (arr == NULL) {
        printf("\nNo books to sort!\n");
        return;
    }

    quickSortByID(arr, 0, n - 1);

    printf("\n===== Books Sorted by ID =====\n");
    int i;
    for (i = 0; i < n; i++) {
        printBook(arr[i]);
    }
    printf("Total: %d book(s).\n", n);

    free(arr);
}

// ------------------------------------------------
// search menu
// ------------------------------------------------

void searchMenu() {
    int choice;
    int id;
    char keyword[100];

    printf("\n===== SEARCH MENU =====\n");
    printf("1. Search by ID\n");
    printf("2. Search by Title\n");
    printf("3. Search by Author\n");
    printf("4. Search by Category\n");
    printf("5. Show Available Books\n");
    printf("6. Show Borrowed Books\n");
    printf("7. Sort by Title\n");
    printf("8. Sort by ID\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
    case 1: {
        printf("Enter Book ID: ");
        scanf("%d", &id);

        Book* found = searchByID(id);
        if (found != NULL) {
            printBook(found);
        } else {
            printf("Book not found.\n");
        }
        break;
    }
    case 2:
        printf("Enter title keyword: ");
        fgets(keyword, 100, stdin);
        keyword[strcspn(keyword, "\n")] = 0;
        searchByTitle(head, keyword);
        break;

    case 3:
        printf("Enter author keyword: ");
        fgets(keyword, 100, stdin);
        keyword[strcspn(keyword, "\n")] = 0;
        searchByAuthor(head, keyword);
        break;

    case 4:
        printf("Enter category keyword: ");
        fgets(keyword, 100, stdin);
        keyword[strcspn(keyword, "\n")] = 0;
        searchByCategory(head, keyword);
        break;

    case 5:
        searchByAvailability(head, 1);
        break;

    case 6:
        searchByAvailability(head, 0);
        break;

    case 7:
        sortBooksByTitle(head);
        break;

    case 8:
        sortBooksByID(head);
        break;

    default:
        printf("Invalid choice.\n");
    }
}