# CPE112_final_project
This is CPE112 final project group including 3417, 3420, 3440, 3445

# Library Management System

## Project Overview

This project is a console-based Library Management System written in C language for Data Structure coursework.

The system allows users to:

- Register, login, and logout
- Add, delete, and display books
- Search books
- Borrow and return books
- Join a waiting list when books are unavailable
- View their borrowed books and waiting list

The project demonstrates the use of multiple data structures and file handling in C.

---

# Data Structures Used

## 1. Linked List

Used for storing books and users dynamically.

### Why Linked List?
- Dynamic memory allocation
- Easy insertion and deletion
- No fixed size required

### Time Complexity
| Operation | Complexity |
|-----------|------------|
| Insert | O(1) |
| Delete | O(n) |
| Search | O(n) |

### Compared with Array
If Array was used:
- Insertion/deletion becomes expensive because elements must shift
- Fixed size limitation

Therefore, linked list is more flexible for library systems.

### Used In
- Book storage
- User storage

---

## 2. Queue

Used for the waiting list system.

### Why Queue?
- First Come First Serve (FCFS)
- Fair order for users waiting for books

### Used In
- Book waitlist

---

## 3. Hash Table

Used for faster searching of books by ID.

### Why Hash Table?
- Faster lookup compared to linear search
- Improves search efficiency

---
 Sorting Algorithm

## Bubble Sort

The system uses **Bubble Sort** to sort books by Book ID before displaying them.

### Why Bubble Sort?
Bubble Sort was selected because:
- Easy to understand and implement
- Suitable for small datasets
- Good for beginner-level Data Structure projects
- Works well with temporary arrays created from linked lists

### Time Complexity
| Case | Complexity |
|------|------------|
| Best Case | O(n) |
| Average Case | O(n²) |
| Worst Case | O(n²) |

---

# Features

## User System
- Register new users
- Login system
- Logout system
- Prevent duplicate usernames
- Auto login after registration
- Store user data in `User.txt`

---

## Book Management
- Add books
- Delete books
- Display all books
- Books sorted by ID
- Save books into `books.txt`
- Load books automatically when program starts

---

## Search System
- Search by Book ID
- Search by Title
- Search by Author
- Search by Category

---

## Borrow System
- Borrow books
- Return books
- Track borrower
- Borrow limit per user
- Waiting list support
- Auto assign book to next user in queue
- Track borrower using `borrowedBy`
- Track borrowed count for each user

---

## My Book List
Users can view:
- Currently borrowed books
- Books in waiting list

---

# File Handling

## books.txt
Stores all book information.

## User.txt
Stores all user information.

Data is automatically saved and loaded when the program runs.

---

# Program Structure

## Source Files

| File | Description |
|---|---|
| main.c | Program entry point |
| menu.c | Menu system |
| book_system.c | Book management |
| borrow_system.c | Borrow and waitlist system |
| search.c | Search functionality |
| user_system.c | User management |

---

## Header Files

| File | Description |
|---|---|
| menu.h | Menu function |
| book_system.h | Book structure and functions |
| borrow_system.h | Borrow system functions |
| search.h | Search functions |
| user_system.h | User structure and functions |

---

# How to Compile

```bash
gcc main.c menu.c book_system.c search.c borrow_system.c user_system.c -o library