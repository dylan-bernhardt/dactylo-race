
#include "app.h"

#define CMD "serveur"

typedef struct
{
    pthread_t thread;
    int canal;
    int id;
    char gamertag[50];
    int rank;
} Worker;

int seek_worker();
void create_workers();
void *thread_worker(void *arg);
int player_session(Worker *worker);
int get_sentence(char *file_path, char sentence[LIGNE_MAX]);
int get_rank();
void send_ranking_to_player(int canal);
void send_ranking(int canal);

Worker list_workers[NUMBER_OF_PLAYER];
pthread_barrier_t everyone_has_finished;
pthread_barrier_t enough_players;

int main(int argc, char **argv)
{
    pthread_barrier_init(&everyone_has_finished, NULL, NUMBER_OF_PLAYER);
    pthread_barrier_init(&enough_players, NULL, NUMBER_OF_PLAYER);
    if (argc != 2)
        erreur("usage : %s port ", argv[0]);
    int ecoute, ret, canal, id_worker_libre;
    short port;
    struct sockaddr_in adrEcoute, adrClient;
    unsigned int lgAdrClient;

    port = (short)atoi(argv[1]);

    create_workers(list_workers);
    /*
    creates the socket
    */
    ecoute = socket(AF_INET, SOCK_STREAM, 0);
    if (ecoute < 0)
        erreur_IO("socket");

    /*
    binds the socket to the server
    */
    adrEcoute.sin_family = AF_INET;
    adrEcoute.sin_addr.s_addr = INADDR_ANY;
    adrEcoute.sin_port = htons(port);
    ret = bind(ecoute, (struct sockaddr *)&adrEcoute, sizeof(adrEcoute));
    if (ret < 0)
        erreur_IO("bind");

    /*
    configuring socket as a server
    */
    ret = listen(ecoute, 5);
    if (ret < 0)
        erreur_IO("listen");

    while (VRAI)
    {
        /*
        waits for a connexion and accepts it
        */
        printf("%s: accepting a connection\n", CMD);
        canal = accept(ecoute, (struct sockaddr *)&adrClient, (socklen_t *)&lgAdrClient);
        if (canal < 0)
            erreur_IO("accept");

        printf("%s: adr %s, port %hu\n", CMD,
               stringIP(ntohl(adrClient.sin_addr.s_addr)), ntohs(adrClient.sin_port));
        for (int i = 0; i < NUMBER_OF_PLAYER; i++)
            printf("\n%d", list_workers[i].canal);
        if ((id_worker_libre = seek_worker(list_workers)) != -1)
        {
            list_workers[id_worker_libre].canal = canal;
        }
    }
    return 0;
}

void create_workers()
{
    for (int i = 0; i < NUMBER_OF_PLAYER; i++)
    {
        list_workers[i].id = i;
        list_workers[i].canal = -1;
        list_workers[i].rank = -1;
        pthread_create(&list_workers[i].thread, NULL, thread_worker, (void *)&list_workers[i]);
    }
    return;
}

int seek_worker()
{
    for (int i = 0; i < NUMBER_OF_PLAYER; i++)
    {
        if (list_workers[i].canal == -1)
            return i;
    }
    return -1;
}

void *thread_worker(void *arg)
{
    char rejouer[1];
    while (1)
    {
        Worker *worker = (Worker *)arg;
        while (worker->canal < 0)
            usleep(100000);
        puts("worker actif");

        int rank = player_session(worker);
        worker->rank = rank;
        fflush(stdout);

        pthread_barrier_wait(&everyone_has_finished);
        /*for (int i = 0; i < NUMBER_OF_PLAYER; i++)
            printf("%s %d", list_workers[i].gamertag, list_workers[i].rank);*/
        send_ranking(worker->canal);
        lireLigne(worker->canal, rejouer);

        printf("%s : %s\n", worker->gamertag, rejouer);
        fflush(stdout);

        if (strncmp(rejouer, "exit", 4) == 0)
        {
            {
                worker->canal = -1; // Réinitialise le canal
                puts("worker dort");
            }
        }
    }
    pthread_exit(NULL);
}

int player_session(Worker *worker)
{
    int canal = worker->canal;
    char ligne[LIGNE_MAX];
    char sentence[LIGNE_MAX], gamertag[50];
    int length_of_sentence = get_sentence("./sentences.txt", sentence);
    lireLigne(canal, gamertag);
    strcpy(worker->gamertag, gamertag);
    printf("\n%s is in the lobby\n\n", worker->gamertag);
    pthread_barrier_wait(&enough_players);
    ecrireLigne(canal, "ok\n");
    ecrireLigne(canal, sentence);
    while (1)
    {
        lireLigne(canal, ligne);
        if (strncmp(ligne, sentence, length_of_sentence) == 0)
        {
            /*printf("gagné");*/
            ecrireLigne(canal, "well done !\n");
            fflush(stdout);
            return get_rank();
        }
        ecrireLigne(canal, "wrong\n");
    }
}

int get_sentence(char *file_path, char sentence[LIGNE_MAX])
{
    FILE *f = fopen(file_path, "r");
    fgets(sentence, 2000, f);
    fclose(f);
    int i = 0;
    while (sentence[i++])
        ;
    return i - 1;
}

int get_rank()
{
    int rank = 0;
    for (int i = 0; i < NUMBER_OF_PLAYER; i++)
    {
        if (list_workers[i].rank != -1)
            rank++;
    }
    return rank;
}

void send_ranking(int canal)
{
    int sent = 0;
    while (sent != NUMBER_OF_PLAYER)
    {
        for (int i = 0; i < NUMBER_OF_PLAYER; i++)
        {
            if (list_workers[i].rank == sent)
            {
                sent++;
                ecrireLigne(canal, list_workers[i].gamertag);
            }
        }
    }
}