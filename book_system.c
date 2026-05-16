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

// ===== QUICK SORT FUNCTIONS =====

// swap two book pointers
void swapBooks(Book **a, Book **b)
{
    Book *temp = *a;
    *a = *b;
    *b = temp;
}

// partition for quick sort
int partitionBooks(Book *arr[], int low, int high)
{
    Book *pivot = arr[high];

    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j]->id < pivot->id)
        {
            i++;

            swapBooks(&arr[i], &arr[j]);
        }
    }

    swapBooks(&arr[i + 1], &arr[high]);

    return i + 1;
}

// quick sort by book ID
void quickSortBooks(Book *arr[],
                    int low,
                    int high)
{
    if (low < high)
    {
        int pivot =
            partitionBooks(arr,
                           low,
                           high);

        quickSortBooks(arr,
                       low,
                       pivot - 1);

        quickSortBooks(arr,
                       pivot + 1,
                       high);
    }
}

// ===== DISPLAY BOOKS =====

void displayBooks()
{
    int count = 0;

    Book *temp = head;

    if (head == NULL)
    {
        printf("No books available.\n");
        return;
    }

    // count books
    while (temp != NULL)
    {
        count++;

        temp = temp->next;
    }

    // create array of pointers
    Book *arr[count];

    temp = head;

    for (int i = 0; i < count; i++)
    {
        arr[i] = temp;

        temp = temp->next;
    }

    // quick sort
    quickSortBooks(arr, 0, count - 1);

    printf("\n===== Book List =====\n");

    // display sorted books
    for (int i = 0; i < count; i++)
    {
        printf("\nID: %d\n", arr[i]->id);

        printf("Title: %s\n",
               arr[i]->title);

        printf("Author: %s\n",
               arr[i]->author);

        printf("Category: %s\n",
               arr[i]->category);

        printf("Status: %s\n",
               arr[i]->available
                   ? "Available"
                   : "Borrowed");

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
                "%d|%s|%s|%s|%d|%d|%d|",
                temp->id,
                temp->title,
                temp->author,
                temp->category,
                temp->available,
                temp->borrowedBy,
                temp->waitlist.count);

        // save queue user IDs
        for (int i = 0; i < temp->waitlist.count; i++)
        {
            int index =
                (temp->waitlist.front + i)
                % MAX_WAITLIST;

            fprintf(fp,
                    "%d",
                    temp->waitlist.user_ids[index]);

            // comma between IDs
            if (i < temp->waitlist.count - 1)
            {
                fprintf(fp, ",");
            }
        }

        fprintf(fp, "\n");

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
        Book *newBook =
            (Book *)malloc(sizeof(Book));

        if (newBook == NULL)
        {
            break;
        }

        char queueData[200] = "";

        int result = fscanf(fp,
                            "%d|%99[^|]|%99[^|]|%49[^|]|%d|%d|%d|%199[^\n]\n",
                            &newBook->id,
                            newBook->title,
                            newBook->author,
                            newBook->category,
                            &newBook->available,
                            &newBook->borrowedBy,
                            &newBook->waitlist.count,
                            queueData);

        if (result < 7)
        {
            free(newBook);
            break;
        }

        // initialize queue
        initWaitQueue(&newBook->waitlist);

        // restore count
        int count = 0;

        // split queue string
        if (strlen(queueData) > 0)
        {
            char *token = strtok(queueData, ",");

            while (token != NULL)
            {
                newBook->waitlist.user_ids[count]
                    = atoi(token);

                count++;

                token = strtok(NULL, ",");
            }
        }

        newBook->waitlist.count = count;

        newBook->waitlist.front = 0;

        newBook->waitlist.rear = count - 1;

        // initialize pointers
        newBook->next = NULL;
        newBook->hashNext = NULL;

        // insert linked list
        newBook->next = head;
        head = newBook;

        // insert hash table
        insertHash(newBook);
    }

    fclose(fp);
}