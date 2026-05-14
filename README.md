# CPE112_final_project
This is CPE112 final project from group "Data Crisi but Chill" including 68070503417, 68070503420, 68070503440, 68070503445.

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

### Search Functions
- Search by Book ID (using Hash Table)
- Search by Title
- Search by Author
- Search by Category
- Search by Availability (show available or borrowed books)

### Sort Functions
- Sort by Title (A → Z using Quick Sort)
- Sort by ID (ascending using Quick Sort)

### Hash Table
- Size: 100 slots
- Collision handling: Chaining (linked list per bucket)
- Search by ID: O(1) average, O(n) worst case

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

### Time Complexity
| Operation | Complexity |
|-----------|------------|
| Search | O(1) |
| Insert | O(1) |
| Delete | O(1) |

### Compared with Stack

- Stack uses LIFO (Last In First Out)
- Latest user would receive the book first

Therefore, queue maintains fairness for users waiting to borrow books.

### Used In
- Book waitlist

---

## 3. Hash Table
Used for faster searching of books by ID using chaining for collision handling.

### Why Hash Table?
- O(1) average time for search by ID
- Much faster than scanning every book one by one
- Collision handled safely using chaining (linked list per bucket)
- Does not require data to be sorted

### How Hash Function Works
index = Book ID % TABLE_SIZE
- Book ID 5   → 5 % 100   = slot 5
- Book ID 105 → 105 % 100 = slot 5 → collision → chaining
- Book ID 23  → 23 % 100  = slot 23

### Time Complexity
| Operation | Average Case | Worst Case |
|-----------|-------------|------------|
| Search by ID | O(1) | O(n) |
| Insert | O(1) | O(1) |
| Delete | O(1) | O(n) |

### Comparison with Other Search Methods
| | Hash Table | Linear Search | Binary Search |
|---|---|---|---|
| Search | O(1) avg | O(n) | O(log n) |
| Requires sorted data | No | No | Yes |
| Insert | O(1) | O(1) | O(n) must re-sort |
| Best for | ID lookup | small datasets | sorted arrays |

Hash Table provides much faster searching performance, especially when the number of books becomes large.

### Used In
- Search book by ID
- Insert book into table
- Delete book from table

---
 Sorting Algorithm

## Quick Sort
The system uses **Quick Sort** to sort books by Book ID or Title and displaying them.

### Why Quick Sort?
Quick Sort was selected because:
- Efficient for average case with O(n log n) performance
- Uses low memory — only O(log n)
- Works well with temporary arrays created from linked lists
- Good fit for library system where books are added in random order

### Time Complexity
| Case | Complexity | When |
|------|------------|------|
| Best Case | O(n log n) | pivot splits evenly every time |
| Average Case | O(n log n) | normal random data |
| Worst Case | O(n²) | list is already sorted |

### Comparison with Other Sorting Algorithms
| Algorithm | Average Case | Memory |
|-----------|-------------|--------|
| Quick Sort (ours) | O(n log n) | O(log n) |
| Merge Sort | O(n log n) | O(n) |
| Bubble Sort | O(n²) | O(1) |
| Insertion Sort | O(n²) | O(1) |

Quick Sort uses less memory than Merge Sort and is faster in practice
than Bubble Sort and Insertion Sort for large datasets.

### Used in
- search by sort ID
- search by sort Title

---

# How to Compile

bash:
gcc main.c menu.c book_system.c search.c borrow_system.c user_system.c -o library
or ./library on terminal

# How to Use

----

The program shows a numbered menu.
Type a number and press Enter.

⸻

## Before Login

1. Register new account
2. Login
3. Exit program

⸻

## After Login

1. Add new book
2. Delete book
3. Display all books
4. Search books
5. Borrow book
6. Return book
7. My Book List
8. Logout
9. Exit program

⸻

## Example Usage

### Register

Create username: alice
Create password: 1234
Register success.

⸻

### Login

Username: alice
Password: 1234
Login success.

⸻

### Add Book

Enter Book ID: 101
Enter Title: C Programming
Enter Author: Dennis Ritchie
Enter Category: Programming
Book added successfully!

⸻

### Borrow Book

Enter Book ID: 101
Book borrowed successfully.

⸻

### Join Waitlist

Book already borrowed.
Join waitlist? (y/n): y
Added to waitlist.

⸻

### Return Book

Enter Book ID: 101
Book returned successfully.

⸻

### Search Book

===== SEARCH MENU =====
1. Search by ID
2. Search by Title
3. Search by Author
4. Search by Category
5. Show Available Books
6. Show Borrowed Books
7. Sort by Title
8. Sort by ID

⸻

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
