#include "menu.h"
#include "book_system.h"
#include "search.h"
#include "user_system.h"

int main()
{
    initHashTable();

    loadBooksFromFile();

    loadUsers();

    menu();

    return 0;
}