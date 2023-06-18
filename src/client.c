#include "app.h"

#define CMD "client"

int main(int argc, char *argv[])
{
    int lgEcr, sock, ret, fin, i;
    struct sockaddr_in *adrServ;
    int want_to_play = VRAI;
    char ligne[LIGNE_MAX], res, gamertag[50];
    char players_in_order[NUMBER_OF_PLAYER][50];

    /*
    error if program is poorly executed
    */
    if (argc != 3)
        erreur("usage: %s machine port\n", argv[0]);

    /*
    creates the socket
    */
    printf("%s: creating a socket\n", CMD);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        erreur_IO("socket");

    /*
    dns resolving
    */
    printf("%s: DNS resolving for %s, port %s\n", CMD, argv[1], argv[2]);
    adrServ = resolv(argv[1], argv[2]);
    if (adrServ == NULL)
        erreur("adresse %s port %s inconnus\n", argv[1], argv[2]);

    printf("%s: adr %s, port %hu\n", CMD,
           stringIP(ntohl(adrServ->sin_addr.s_addr)),
           ntohs(adrServ->sin_port));

    /*
    connects the socket to the server
    */
    printf("%s: connecting the socket\n", CMD);
    ret = connect(sock, (struct sockaddr *)adrServ, sizeof(struct sockaddr_in));
    if (ret < 0)
        erreur_IO("connect");

    lireLigne(sock, ligne);
    if (strncmp(ligne, "ok", 2) != 0)
    {
        puts("Number of player max reached. Please try later !");
        return 0;
    }
    display_start();
    ask_gamertag(gamertag);
    while (want_to_play)
    {
        ecrireLigne(sock, gamertag); /* sends his gamertag */
        fin = FAUX;

        waiting(); /* waits until every players are connected */

        lireLigne(sock, ligne);
        if (strncmp(ligne, "ok", 2) != 0)
            erreur_IO("pseudo");

        compte_a_rebours();

        lireLigne(sock, ligne);
        puts(ligne); /* display the sentence to write as fast as possible */
        while (!fin)
        {
            printf("> ");
            if (fgets(ligne, LIGNE_MAX, stdin) == NULL)
                erreur("saisie fin de fichier\n");

            lgEcr = ecrireLigne(sock, ligne);
            if (lgEcr == -1)
                erreur_IO("ecrire ligne");
            lireLigne(sock, ligne);
            printf("%s\n", ligne); /* print the server response : wrong or well done*/
            if (strncmp(ligne, "Wrong", 5) != 0)
            {
                fin = VRAI;
            }
        }

        /*
        receives results of the game
        */

        for (i = 0; i < NUMBER_OF_PLAYER; i++)
            lireLigne(sock, players_in_order[i]);

        display_results(players_in_order[0], players_in_order[1], players_in_order[2], players_in_order[3]);
        /*
        asks for players to play again or not and sends response to the server
        */
        res = getchar();

        if (res == 'q')
        {
            want_to_play = FAUX;
            ecrireLigne(sock, "exit\n");
            display_end();
        }
        else
        {
            ecrireLigne(sock, "continue\n");
        }
    }

    if (close(sock) == -1)
        erreur_IO("close socket");

    exit(EXIT_SUCCESS);
}