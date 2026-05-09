#include "menu.h"
#include "search.h"
#include "book_system.h"

int main()
{
    initHashTable();

    loadBooksFromFile();

    menu();

    return 0;
}