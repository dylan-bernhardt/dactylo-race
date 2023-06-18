/*
by Dylan BERNHARDT & Corentin BUNAUX
*/
#ifndef IF_WORKER

#include "ligne.h"
#include <pthread.h>

#define LIGNE_MAX 2000
typedef struct
{
    pthread_t thread;
    int canal;
    int index;
    char gamertag[50];
    int rank;
    int sentence_index;
} Worker;

typedef struct
{
    Worker *worker;
    int number_of_player;
    Worker *list_workers;
} Data_for_thread;

int seek_worker(Worker *list_workers, int number_of_workers);
void create_workers(Worker *list_workers, int number_of_workers, void *(*start_routine)(void *));
void send_ranking(Worker *list_workers, int canal, int number_of_player);
int get_rank(Worker *list_worker, int number_of_player);
int get_sentence(char *file_path, char sentence[LIGNE_MAX]);

#endif