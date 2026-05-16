#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_system.h"
#include "search.h"
#include "borrow_system.h"

// ===== GLOBAL VARIABLE =====

Book *head = NULL;

// ===== ADD BOOK =====

void addBook()
{
    Book *newBook = (Book *)malloc(sizeof(Book));

    if (newBook == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Book ID: ");

    scanf("%d", &newBook->id);
    getchar();

    // check duplicate ID
    if (searchByID(newBook->id) != NULL)
    {
        printf("Book ID already exists.\n");

        free(newBook);

        return;
    }

    printf("Enter Title: ");

    fgets(newBook->title, 100, stdin);
    newBook->title[strcspn(newBook->title, "\n")] = 0;

    printf("Enter Author: ");

    fgets(newBook->author, 100, stdin);
    newBook->author[strcspn(newBook->author, "\n")] = 0;

    printf("Enter Category: ");

    fgets(newBook->category, 50, stdin);
    newBook->category[strcspn(newBook->category, "\n")] = 0;

    // available
    newBook->available = 1;

    // borrow system
    newBook->borrowedBy = -1;

    initWaitQueue(&newBook->waitlist);

    // initialize pointers
    newBook->next = NULL;
    newBook->hashNext = NULL;

    // insert into linked list
    newBook->next = head;
    head = newBook;

    // insert into hash table
    insertHash(newBook);

    // save file
    saveBooksToFile();

    printf("Book added successfully!\n");
}

// ===== DELETE BOOK =====

void deleteBook()
{
    int id;

    printf("Enter Book ID to delete: ");

    scanf("%d", &id);

    Book *temp = head;
    Book *prev = NULL;

    while (temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Book not found.\n");
        return;
    }

    // remove from linked list
    if (prev == NULL)
    {
        head = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }

    // remove from hash table
    deleteHash(id);

    // free memory
    free(temp);

    // update file
    saveBooksToFile();

    printf("Book deleted successfully!\n");
}

// ===== DISPLAY BOOKS =====

void displayBooks()
{
    // count books
    int count = 0;
    Book *temp = head;

    if (head == NULL)
    {
        printf("No books available.\n");
        return;
    }

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    // create array
    Book *arr[count];

    temp = head;

    for (int i = 0; i < count; i++)
    {
        arr[i] = temp;
        temp = temp->next;
    }

    // sort by ID (bubble sort)
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (arr[j]->id > arr[j + 1]->id)
            {
                Book *swap = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = swap;
            }
        }
    }

    printf("\n===== Book List =====\n");

    // display sorted books
    for (int i = 0; i < count; i++)
    {
        printf("\nID: %d\n", arr[i]->id);
        printf("Title: %s\n", arr[i]->title);
        printf("Author: %s\n", arr[i]->author);
        printf("Category: %s\n", arr[i]->category);

        printf("Status: %s\n",
               arr[i]->available ? "Available" : "Borrowed");

        if (!arr[i]->available)
        {
            printf("Borrowed By User ID: %d\n",
                   arr[i]->borrowedBy);
        }

        printf("Waitlist Count: %d\n",
               arr[i]->waitlist.count);
    }
}

// ===== SAVE FILE =====

void saveBooksToFile()
{
    FILE *fp = fopen("books.txt", "w");

    if (fp == NULL)
    {
        printf("Cannot open file.\n");
        return;
    }

    Book *temp = head;

    while (temp != NULL)
    {
        fprintf(fp,
                "%d|%s|%s|%s|%d|%d\n",
                temp->id,
                temp->title,
                temp->author,
                temp->category,
                temp->available,
                temp->borrowedBy);

        temp = temp->next;
    }

    fclose(fp);
}

// ===== LOAD FILE =====

void loadBooksFromFile()
{
    FILE *fp = fopen("books.txt", "r");

    if (fp == NULL)
    {
        return;
    }

    while (1)
    {
        Book *newBook = (Book *)malloc(sizeof(Book));

        if (newBook == NULL)
        {
            break;
        }

        int result = fscanf(fp,
                            "%d|%99[^|]|%99[^|]|%49[^|]|%d|%d\n",
                            &newBook->id,
                            newBook->title,
                            newBook->author,
                            newBook->category,
                            &newBook->available,
                            &newBook->borrowedBy);

        if (result != 6)
        {
            free(newBook);
            break;
        }

        // initialize queue
        initWaitQueue(&newBook->waitlist);

        // initialize pointers
        newBook->next = NULL;
        newBook->hashNext = NULL;

        // insert into linked list
        newBook->next = head;
        head = newBook;

        // insert into hash table
        insertHash(newBook);
    }

    fclose(fp);
}