#ifndef IF_MENU
#define IF_MENU

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void display_start();
void clear();
void ask_gamertag(char gamertag[50]);
void waiting();
void compte_a_rebours(void);
void display_end(void);
void display_results(char *g1, char *g2, char *g3, char *g4);

#endif