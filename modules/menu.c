#include <unistd.h>
#include "menu.h"

void start()
{
    clear();
    printf("Welcome to our game ! The goal is to write a phrase as fast as possible. Press enter to start\n\n");
    fputs("            ", stdout);
    puts("\n\n\n######################################################################");
    getchar();
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

void gamertag(char gamertag[50])
{
    printf("\tChose a gamertag : \t");
    fgets(gamertag, 50, stdin);
}

void podium(char *gamer1, char *gamer2, char *gamer3)
{
    printf("                                    %s                                       \n", gamer1);
    printf("          %s                                                                 \n", gamer2);
    printf("                                                                   %s          \n", gamer3);
    printf("                          /////////////////////////                          \n");
    printf("                          /////////      //////////                          \n");
    printf("(((((((((((((((((((((((###/////////  1   //////////                          \n");
    printf("((((((((       ((((((((###/////////      //////////                          \n");
    printf("((((((((   2   ((((((((###/////////////////////////###(((((((((((((((((((((((\n");
    printf("((((((((       ((((((((###/////////////////////////###(((((((((     (((((((((\n");
    printf("(((((((((((((((((((((((###/////////////////////////###(((((((((  3  (((((((((\n");
    printf("(((((((((((((((((((((((###/////////////////////////###(((((((((     (((((((((\n");
}

void compte_a_rebours(void)
{
    clear();

    puts("\t\t             @@@@@@@@@@@@");
    puts("\t\t           @@             @");
    puts("\t\t          @@@@@@@@         @");
    puts("\t\t         @@      @@       @@");
    puts("\t\t                  @       @");
    puts("\t\t            @@@@@@@     @@");
    puts("\t\t          @@           @");
    puts("\t\t          @@           @");
    puts("\t\t            @@@@@@@     @@");
    puts("\t\t                  @       @");
    puts("\t\t         @@      @@       @@");
    puts("\t\t          @@@@@@@@         @");
    puts("\t\t           @@             @");
    puts("\t\t             @@@@@@@@@@@@");

    usleep(1000000);

    clear();

    puts("\t\t              @@@@@@@@@@@");
    puts("\t\t            @             @");
    puts("\t\t           @     @         @");
    puts("\t\t          @     @    @     @");
    puts("\t\t         @@@@@@       @    @");
    puts("\t\t                      ,    @");
    puts("\t\t                    @     @");
    puts("\t\t                  @     @");
    puts("\t\t                @,     @");
    puts("\t\t              @      @");
    puts("\t\t            @      @");
    puts("\t\t           @      @@@@@@@@@@@");
    puts("\t\t          @                 @");
    puts("\t\t          @@@@@@@@@@@@@@@@@@@");

    usleep(1000000);

    clear();

    puts("\t\t                  (@@@@ ");
    puts("\t\t                @&   *@ ");
    puts("\t\t             /@      *@ ");
    puts("\t\t          @@         *@ ");
    puts("\t\t        @            *@ ");
    puts("\t\t        @    .@ (    *@ ");
    puts("\t\t        @ @@   .@    *@ ");
    puts("\t\t                @    *@ ");
    puts("\t\t                @    *@ ");
    puts("\t\t                @    *@ ");
    puts("\t\t                @    *@ ");
    puts("\t\t           @@@@@@    @@@@@@");
    puts("\t\t           @              @ ");
    puts("\t\t           @@@@@@@@@@@@@@@@");

    usleep(1000000);

    clear();
}

void end(void)
{
    clear();
    puts("Thank you for playing our game. See you next time !");
    usleep(5000000);
    system("clear");
}

void results(char *gamer1, char *gamer2, char *gamer3)
{
    puts("The game is finished. The winners are ....");
    usleep(2000000);
    podium(gamer1, gamer2, gamer3);
    usleep(2000000);
    puts("If you want to play angain, press P. Else, press E");
    char trash = getchar();
    if (trash == 'E')
    {
        end();
    }
}