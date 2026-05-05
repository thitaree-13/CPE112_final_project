#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_system.h"

// ===== GLOBAL VARIABLE =====
Book* head = NULL;

// ===== FUNCTIONS =====

void addBook() {
    Book* newBook = (Book*)malloc(sizeof(Book));

    if (newBook == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Book ID: ");
    scanf("%d", &newBook->id);
    getchar(); // clear newline

    printf("Enter Title: ");
    fgets(newBook->title, 100, stdin);
    newBook->title[strcspn(newBook->title, "\n")] = 0;

    printf("Enter Author: ");
    fgets(newBook->author, 100, stdin);
    newBook->author[strcspn(newBook->author, "\n")] = 0;

    printf("Enter Category: ");
    fgets(newBook->category, 50, stdin);
    newBook->category[strcspn(newBook->category, "\n")] = 0;

    newBook->available = 1;

    // Insert at head (O(1))
    newBook->next = head;
    head = newBook;

    printf("Book added successfully!\n");
}

// Time Complexity: O(n)
void deleteBook() {
    int id;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    Book *temp = head, *prev = NULL;

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Book not found.\n");
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Book deleted successfully!\n");
}

// Time Complexity: O(n)
void displayBooks() {
    Book* temp = head;

    if (temp == NULL) {
        printf("No books available.\n");
        return;
    }

    printf("\n===== Book List =====\n");

    while (temp != NULL) {
        printf("\nID: %d\n", temp->id);
        printf("Title: %s\n", temp->title);
        printf("Author: %s\n", temp->author);
        printf("Category: %s\n", temp->category);
        printf("Status: %s\n", temp->available ? "Available" : "Borrowed");

        temp = temp->next;
    }
}