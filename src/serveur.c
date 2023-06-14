
#include "app.h"

#define CMD "serveur"
#define NUMBER_OF_PLAYER 2

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
void player_session(int canal);
int get_sentence(char *file_path, char sentence[LIGNE_MAX]);

Worker list_workers[NUMBER_OF_PLAYER];
int main(int argc, char **argv)
{
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
    int i = 0;
    while (list_workers[i].canal != -1 && i < NUMBER_OF_PLAYER)
        i++;
    if (i < NUMBER_OF_PLAYER)
        return i;
    else
        return -1;
}

void *thread_worker(void *arg)
{
    while (1)
    {
        Worker *worker = (Worker *)arg;
        while (worker->canal < 0)
            usleep(100000);
        puts("yo jme reveille");
        player_session(worker->canal);

        worker->canal = -1;
    }
    pthread_exit(NULL);
}

void player_session(int canal)
{
    char ligne[LIGNE_MAX];
    char sentence[LIGNE_MAX];
    int length_of_sentence = get_sentence("./sentences.txt", sentence);
    ecrireLigne(canal, sentence);
    while (1)
    {
        lireLigne(canal, ligne);
        if (strncmp(ligne, sentence, length_of_sentence) == 0)
            puts("gagné");
    }
    return;
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