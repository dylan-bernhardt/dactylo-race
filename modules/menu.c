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

void ready()
{
    clear();
    printf("Please press entrer when you are ready");
    fputs("            ", stdout);
    puts("\n\n\n######################################################################");
    getchar();
    clear();
}

void waiting()
{
    printf("Please wait for opponents");
    puts("\n\n\n######################################################################");
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