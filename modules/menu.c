#include <unistd.h>
#include "menu.h"

void start()
{
    clear();
    printf("Welcome to our game ! Press enter to start\n\n");
    fputs("            ", stdout);
    puts("\n\n\n######################################################################");
    getchar();
    clear();
}

void clear()
{
    system("clear");
    fputs("######################################################################\n"
          "           PSE Project\n"
          "######################################################################",
          stdout);
    puts("\n\n");
    fputs("\t\t", stdout);
    return;
}

void gamertag(char gamertag[50])
{
    printf("\tChose a gamertag : \t");
    fgets(gamertag, 50, stdin);
}
