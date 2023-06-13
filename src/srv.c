#include "app.h"
#include <pthread.h>

#define CMD "serveur"

struct Player
{
    char gamertag[50];
};
typedef struct Player Player;

pthread_barrier_t B;
char sentence[200];

void *sessionClient(void *arg); /*thread*/

int main(int argc, char *argv[])
{
    /*
    iniatilizes variables
    */
    short port;
    int ecoute, canal, ret;
    struct sockaddr_in adrEcoute, adrClient;
    unsigned int lgAdrClient;
    DataThread *dataThread;

    /*
    creates barrier to have max 2 players
    */
    pthread_barrier_init(&B, NULL, 2);

    /*
    reads the sentence that player will need to type
    */
    FILE *f = fopen("./sentences.txt", "r");
    if (f == NULL)
        erreur("ouverture du fichier");
    fgets(sentence, 200, f);
    puts("La phrase à écrire sera la suivante :");
    puts(sentence);

    initDataThread();

    /*
    error if no argument
    */
    if (argc != 2)
        erreur("usage: %s port\n", argv[0]);

    /*
    ascci to integer for the port number
    */
    port = (short)atoi(argv[1]);

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
    printf("%s: listening to socket\n", CMD);
    ret = listen(ecoute, 5);
    if (ret < 0)
        erreur_IO("listen");

    while (VRAI)
    {
        /*
        waits for a connexion and accepts it
        */
        printf("%s: accepting a connection\n", CMD);
        canal = accept(ecoute, (struct sockaddr *)&adrClient, (socklen_t *restrict)&lgAdrClient);
        if (canal < 0)
            erreur_IO("accept");

        printf("%s: adr %s, port %hu\n", CMD,
               stringIP(ntohl(adrClient.sin_addr.s_addr)), ntohs(adrClient.sin_port));

        /*
        creates the thread which manage the communication between the server & the client
        */
        dataThread = ajouterDataThread();
        if (dataThread == NULL)
            erreur_IO("ajouter data thread");

        dataThread->spec.canal = canal;
        ret = pthread_create(&dataThread->spec.id, NULL, sessionClient,
                             &dataThread->spec);
        if (ret != 0)
            erreur_IO("creation thread");

        joinDataThread();
    }

    if (close(canal) == -1)
        erreur_IO("close canal");

    if (close(ecoute) == -1)
        erreur_IO("close ecoute");

    exit(EXIT_SUCCESS);
}

void *sessionClient(void *arg)
{
    /*
    initializes variables
    */
    DataSpec *dataTh = (DataSpec *)arg;
    int canal;
    int fin = FAUX;
    char ligne[LIGNE_MAX];
    int lgLue;

    canal = dataTh->canal;

    lgLue = lireLigne(canal, ligne);
    printf("Un joueur a rejoint la partie : %s\n", ligne);
    if (ecrireLigne(canal, ligne) == -1)
        erreur_IO("ecrireLigne");

    pthread_barrier_wait(&B);

    if (ecrireLigne(canal, sentence) == -1)
        erreur_IO("ecrire ligne");

    while (!fin)
    {
        lgLue = lireLigne(canal, ligne);
        if (lgLue < 0)
            erreur_IO("lireLigne");
        else if (lgLue == 0)
            erreur("interruption client\n");

        printf("%s: reception %d octets : \"%s\"\n", CMD, lgLue, ligne);

        if (strcmp(ligne, "fin") == 0)
        {
            printf("%s: fin client\n", CMD);
            fin = VRAI;
        }
    }

    if (close(canal) == -1)
        erreur_IO("fermeture canal");

    dataTh->libre = VRAI;

    pthread_exit(NULL);
}
