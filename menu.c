#include <stdio.h>

#include "menu.h"
#include "book_system.h"
#include "search.h"
#include "borrow_system.h"
#include "user_system.h"

void menu()
{
    int choice;

    do
    {
        // ===== LOGIN / REGISTER MENU =====

        while (!isLoggedIn())
        {
            printf("\n===== LIBRARY SYSTEM =====\n");

            printf("1. Register\n");
            printf("2. Login\n");
            printf("3. Exit\n");

            printf("Enter choice: ");

            if (scanf("%d", &choice) != 1)
            {
                printf("Invalid input\n");

                while (getchar() != '\n')
                    ;

                continue;
            }

            while (getchar() != '\n')
                ;

            switch (choice)
            {
            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 3:
                printf("Exit program.\n");
                return;

            default:
                printf("Invalid choice\n");
            }
        }

        // ===== MAIN MENU AFTER LOGIN =====

        do
        {
            printf("\n===== LIBRARY MENU =====\n");

            printf("Logged in as: %s\n",
                   currentUser->username);

            printf("\n1. Add Book\n");
            printf("2. Delete Book\n");
            printf("3. Display Books\n");
            printf("4. Search Book\n");
            printf("5. Borrow Book\n");
            printf("6. Return Book\n");
            printf("7. My Book List\n");
            printf("8. Logout\n");
            printf("9. Exit\n");

            printf("Enter choice: ");

            if (scanf("%d", &choice) != 1)
            {
                printf("Invalid input\n");

                while (getchar() != '\n')
                    ;

                continue;
            }

            while (getchar() != '\n')
                ;

            switch (choice)
            {
            case 1:
                addBook();
                break;

            case 2:
                deleteBook();
                break;

            case 3:
                displayBooks();
                break;

            case 4:
                searchMenu();
                break;

            case 5:
                borrowBook();
                break;

            case 6:
                returnBook();
                break;

            case 7:
                showMyBooks();
                break;

            case 8:
                logoutUser();

                printf("Back to login menu.\n");

                break;

            case 9:
                logoutUser();

                printf("Exit program.\n");

                return;

            default:
                printf("Invalid choice\n");
            }

        } while (isLoggedIn());

    } while (1);
}