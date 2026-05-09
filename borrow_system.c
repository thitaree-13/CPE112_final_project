#include "borrow_system.h"
#include <stdio.h>
#include <string.h>

//queue function

static void queue_init(WaitQueue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

static bool queue_is_empty(WaitQueue *q) {
    return q->count == 0;
}

static bool queue_is_full(WaitQueue *q) {
    return q->count >= MAX_WAITLIST;
}

static bool queue_enqueue(WaitQueue *q, int user_id) {

    if (queue_is_full(q)) {
        return false;
    }

    q->rear = (q->rear + 1) % MAX_WAITLIST;

    q->user_ids[q->rear] = user_id;

    q->count++;

    return true;
}

static int queue_dequeue(WaitQueue *q) {

    if (queue_is_empty(q)) {
        return -1;
    }

    int user_id = q->user_ids[q->front];

    q->front = (q->front + 1) % MAX_WAITLIST;

    q->count--;

    return user_id;
}

//lib function

void library_init(Library *lib) {

    lib->book_count = 0;

    for (int i = 0; i < MAX_USERS; i++) {
        lib->user_borrow_count[i] = 0;
    }
}

int library_add_book(Library *lib, const char *title) {

    if (lib->book_count >= MAX_BOOKS) {
        return -1;
    }

    int id = lib->book_count;

    Book *book = &lib->books[id];

    book->book_id = id;

    strncpy(book->title, title, MAX_TITLE_LEN - 1);

    book->title[MAX_TITLE_LEN - 1] = '\0';

    book->is_borrowed = false;

    book->borrowed_by = -1;

    queue_init(&book->waitlist);

    lib->book_count++;

    return id;
}

static Book* find_book(Library *lib, int book_id) {

    if (book_id < 0 || book_id >= lib->book_count) {
        return NULL;
    }

    return &lib->books[book_id];
}

//borrowing book

bool borrow_book(Library *lib, int book_id, int user_id) {

    Book *book = find_book(lib, book_id);

    if (!book) {
        return false;
    }

    //check user
    if (user_id < 0 || user_id >= MAX_USERS) {
        return false;
    }

    //limit check
    if (lib->user_borrow_count[user_id] >= MAX_BORROW_LIMIT) {

        printf("User %d reached borrow limit (%d books).\n",
               user_id,
               MAX_BORROW_LIMIT);

        return false;
    }

    //book already borrow
    if (book->is_borrowed) {
        return false;
    }

    book->is_borrowed = true;

    book->borrowed_by = user_id;

    lib->user_borrow_count[user_id]++;

    printf("User %d borrowed '%s'\n",
           user_id,
           book->title);

    return true;
}

//return book

bool return_book(Library *lib, int book_id, int user_id) {

    Book *book = find_book(lib, book_id);

    if (!book) {
        return false;
    }

    //verify
    if (!book->is_borrowed ||
        book->borrowed_by != user_id) {

        return false;
    }

    //delete borrow count
    lib->user_borrow_count[user_id]--;

    //waitlist checker
    int next_user = queue_dequeue(&book->waitlist);

    if (next_user != -1) {

        // Check next user limit
        if (lib->user_borrow_count[next_user]
            < MAX_BORROW_LIMIT) {

            book->borrowed_by = next_user;

            book->is_borrowed = true;

            lib->user_borrow_count[next_user]++;

            printf("Book '%s' auto-assigned to user %d from waitlist.\n",
                   book->title,
                   next_user);
        }
        else {

            printf("User %d skipped (borrow limit reached).\n",
                   next_user);

            book->is_borrowed = false;

            book->borrowed_by = -1;
        }
    }
    else {

        book->is_borrowed = false;

        book->borrowed_by = -1;
    }

    return true;
}

//waiting list

bool join_waitlist(Library *lib, int book_id, int user_id) {

    Book *book = find_book(lib, book_id);

    if (!book) {
        return false;
    }

    // No need to wait if available
    if (!book->is_borrowed) {
        return false;
    }

    // Prevent duplicate waitlist entry
    for (int i = 0; i < book->waitlist.count; i++) {

        int index =
            (book->waitlist.front + i) % MAX_WAITLIST;

        if (book->waitlist.user_ids[index] == user_id) {
            return false;
        }
    }

    return queue_enqueue(&book->waitlist, user_id);
}

//function status

bool is_book_available(Library *lib, int book_id) {

    Book *book = find_book(lib, book_id);

    return book && !book->is_borrowed;
}

int get_waitlist_count(Library *lib, int book_id) {

    Book *book = find_book(lib, book_id);

    return book ? book->waitlist.count : -1;
}