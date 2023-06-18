#include "worker.h"
#include <stdio.h>
#include "ligne.h"
#include <pthread.h>

int seek_worker(Worker *list_workers, int number_of_player)
{
    for (int i = 0; i < number_of_player; i++)
    {
        if (list_workers[i].canal == -1)
            return i;
    }
    return -1;
}

void create_workers(Worker *list_workers, int number_of_workers, void *(*start_routine)(void *))
{
    for (int i = 0; i < number_of_workers; i++)
    {
        list_workers[i].index = i;
        list_workers[i].canal = -1;
        list_workers[i].rank = -1;
        pthread_create(&list_workers[i].thread, NULL, start_routine, (void *)&list_workers[i]);
    }
    return;
}

void send_ranking(Worker *list_workers, int canal, int number_of_player)
{
    int sent = 0;
    while (sent != number_of_player)
    {
        for (int i = 0; i < number_of_player; i++)
        {
            if (list_workers[i].rank == sent)
            {
                sent++;
                ecrireLigne(canal, list_workers[i].gamertag);
            }
        }
    }
}

int get_rank(Worker *list_workers, int number_of_player)
{
    int rank = 0;
    for (int i = 0; i < number_of_player; i++)
    {
        if (list_workers[i].rank != -1)
            rank++;
    }
    return rank;
}

int get_sentence(char *file_path, char sentence[LIGNE_MAX])
{
    FILE *f = fopen(file_path, "r");
    fgets(sentence, LIGNE_MAX, f);
    fclose(f);

    int i = 0;
    while (sentence[i++])
        ;
    return i - 2;
}