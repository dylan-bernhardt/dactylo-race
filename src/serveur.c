
#include "app.h"
#define CMD "serveur"

void *thread_worker(void *arg);                           /* thread that manages the game for a player */
int player_session(Worker *worker, int number_of_player); /* function called in the thread */

Worker list_workers[NUMBER_OF_PLAYER];
pthread_barrier_t everyone_has_finished, enough_players;

int main(int argc, char **argv)
{
    /*
    initializes the barriers
    */
    pthread_barrier_init(&everyone_has_finished, NULL, NUMBER_OF_PLAYER);
    pthread_barrier_init(&enough_players, NULL, NUMBER_OF_PLAYER);

    /*
    error if the program is poorly executed
    */
    if (argc != 2)
        erreur("usage : %s port ", argv[0]);

    int ecoute, ret, canal, id_worker_libre;
    short port;
    struct sockaddr_in adrEcoute, adrClient;
    unsigned int lgAdrClient;

    port = (short)atoi(argv[1]);

    /*
    initalizes workers
    */
    create_workers(list_workers, NUMBER_OF_PLAYER, thread_worker);

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
        infinite loop accepting connexions and assigning worker if it is possible
        */
        puts("Waiting for connexion...");
        canal = accept((int)ecoute, (struct sockaddr *)&adrClient, (socklen_t *)&lgAdrClient);
        if (canal < 0)
            erreur_IO("accept");

        printf("%s: adr %s, port %hu\n", CMD,
               stringIP(ntohl(adrClient.sin_addr.s_addr)), ntohs(adrClient.sin_port));
        if ((id_worker_libre = seek_worker(list_workers, NUMBER_OF_PLAYER)) != -1)
        {
            list_workers[id_worker_libre].canal = canal;
        }
    }
    return 0;
}

void *thread_worker(void *arg)
{
    char rejouer[4];
    while (1)
    {
        Worker *worker = (Worker *)arg;
        worker->rank = -1;
        while (worker->canal < 0)
            usleep(100000);
        printf("[%d] worker actif\n", worker->index);

        worker->rank = player_session(worker, NUMBER_OF_PLAYER);
        fflush(stdout);

        pthread_barrier_wait(&everyone_has_finished);
        send_ranking(list_workers, worker->canal, NUMBER_OF_PLAYER);
        lireLigne(worker->canal, rejouer);

        printf("[%d] %s : %s\n", worker->index, worker->gamertag, rejouer);
        fflush(stdout);

        if (strncmp(rejouer, "exit", 4) == 0)
        {
            {
                worker->canal = -1;
                printf("[%d] worker dort", worker->index);
            }
        }
    }
    pthread_exit(NULL);
}

int player_session(Worker *worker, int number_of_player)
{
    int canal = worker->canal;
    char ligne[LIGNE_MAX];
    char sentence[LIGNE_MAX], gamertag[50];
    int length_of_sentence = get_sentence("./sentences.txt", sentence);

    lireLigne(canal, gamertag);
    strcpy(worker->gamertag, gamertag);

    printf("[%d] %s is in the lobby\n", worker->index, worker->gamertag);
    pthread_barrier_wait(&enough_players);
    ecrireLigne(canal, "ok\n");
    ecrireLigne(canal, sentence);
    while (1)
    {
        lireLigne(canal, ligne);
        if (strncmp(ligne, sentence, length_of_sentence) == 0)
        {
            ecrireLigne(canal, "Well done !\n");
            fflush(stdout);
            return get_rank(list_workers, number_of_player);
        }
        ecrireLigne(canal, "Wrong, please try again...\n");
    }
}
