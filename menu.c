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
        printf("\n===== LIBRARY SYSTEM =====\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Add Book\n");
        printf("4. Delete Book\n");
        printf("5. Display Books\n");
        printf("6. Search Book\n");
        printf("7. Borrow Book\n");
        printf("8. Return Book\n");
        printf("9. Logout\n");
        printf("10. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
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

    } while (choice != 10);
}