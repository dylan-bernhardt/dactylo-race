/*
by Dylan BERNHARDT & Corentin BUNAUX
*/
#include <unistd.h>
#include "menu.h"

void display_start()
{
    clear();
    printf("Welcome to our game ! The goal is to write a phrase as fast as possible.\n\n");
    fputs("            ", stdout);
    puts("\n\n\n######################################################################");
    usleep(5000000);
    clear();
}

void waiting()
{
    clear();
    printf("Please wait for opponents");
    puts("\n\n\n######################################################################\n\n");
}

void clear()
{
    system("clear");
    fputs("######################################################################\n"
          "\t\t\tDACTYLO RACE\n"
          "######################################################################",
          stdout);
    puts("\n\n");
    return;
}

void ask_gamertag(char gamertag[50])
{
    printf("\tChose a gamertag : \t");
    fgets(gamertag, 50, stdin);
}

void compte_a_rebours(void)
{
    clear();

    puts("\t\t             @@@@@@@@@@@@");
    puts("\t\t           @@             @");
    puts("\t\t           @@@@@@@         @");
    puts("\t\t                 @@       @@");
    puts("\t\t                  @       @");
    puts("\t\t            @@@@@@@     @@");
    puts("\t\t          @@           @");
    puts("\t\t          @@           @");
    puts("\t\t            @@@@@@@     @@");
    puts("\t\t                  @       @");
    puts("\t\t                 @@       @@");
    puts("\t\t           @@@@@@@         @");
    puts("\t\t           @@             @");
    puts("\t\t             @@@@@@@@@@@@");

    usleep(1000000);

    clear();

    puts("\t\t              @@@@@@@@@@@");
    puts("\t\t            @             @");
    puts("\t\t           @     @@@@      @");
    puts("\t\t          @     @    @     @");
    puts("\t\t         @@@@@@@      @    @");
    puts("\t\t                     @    @");
    puts("\t\t                    @     @");
    puts("\t\t                  @     @");
    puts("\t\t                @      @");
    puts("\t\t              @      @");
    puts("\t\t            @      @");
    puts("\t\t           @      @@@@@@@@@@@");
    puts("\t\t          @                 @");
    puts("\t\t          @@@@@@@@@@@@@@@@@@@");

    usleep(1000000);

    clear();

    puts("\t\t                  @@@@@");
    puts("\t\t                @@    @");
    puts("\t\t             @@       @");
    puts("\t\t          @@          @");
    puts("\t\t        @             @");
    puts("\t\t        @    @@@@     @");
    puts("\t\t        @@@@@   @     @");
    puts("\t\t                @     @");
    puts("\t\t                @     @");
    puts("\t\t                @     @");
    puts("\t\t                @     @");
    puts("\t\t           @@@@@@    @@@@@@");
    puts("\t\t           @              @");
    puts("\t\t           @@@@@@@@@@@@@@@@");

    usleep(1000000);

    clear();
}

void display_end(void)
{
    clear();
    puts("Thank you for playing our game. See you next time !");
    usleep(5000000);
    system("clear");
}

void display_results(char *g1, char *g2, char *g3, char *g4)
{
    clear();
    puts("The game is finished. The winners are ....\n\n");
    usleep(2000000);
    clear();
    printf("[1] : %s \n =================================== \n", g1);
    printf("[2] : %s \n =================================== \n", g2);
    printf("[3] : %s \n =================================== \n", g3);
    printf("[4] : %s \n =================================== \n", g4);
    usleep(5000000);
    clear();
    puts("If you want to quit, press q. Else, press any.");
}