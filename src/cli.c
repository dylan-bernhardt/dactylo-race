#include "app.h"
#include "menu.h"

#define CMD "client"

int main(int argc, char *argv[])
{
    /*
    initializes variables
    */
    char my_gamertag[50];
    int soc, ret;
    struct sockaddr_in *adrServ;
    char ligne[LIGNE_MAX], sentence[200];
    int lgLue;
    /*
    error if there are less than 2 arg
    */
    if (argc != 3)
        erreur("usage: %s machine port\n", argv[0]);

    /*
    socket creation
    */
    soc = socket(AF_INET, SOCK_STREAM, 0);
    if (soc < 0)
        erreur_IO("socket");

    /*
    get server ip and port
    */
    adrServ = resolv(argv[1], argv[2]);
    if (adrServ == NULL)
        erreur("adresse %s port %s inconnus\n", argv[1], argv[2]);

    /*
    connects the socket to the server
    */
    ret = connect(soc, (struct sockaddr *)adrServ, sizeof(struct sockaddr_in));
    if (ret < 0)
        erreur_IO("connect");

    /*
    starts the menu and ask for a gamertag
    */
    start();
    gamertag(my_gamertag);
    /*
    sends gamertag to the server
    */
    if (ecrireLigne(soc, my_gamertag) == -1)
        erreur_IO("ecrireLigne");

    lgLue = lireLigne(soc, ligne);
    if (lgLue < 0)
        erreur_IO("lireLigne");

    clear();
    printf("Your gamertag is : %s\n\n\tWe are waiting for other players... please wait...\n", ligne);

    lireLigne(soc, sentence);
    while (sentence == NULL)
        ;
    clear();
    printf("Objective : write the sentence as fast as possible : \n %s\n\n", sentence);
    for (;;)
        ;
    /*
    close the connection with the server
    */
    if (close(soc) == -1)
        erreur_IO("close");

    exit(EXIT_SUCCESS);
}
