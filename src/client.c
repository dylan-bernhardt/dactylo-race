#include "app.h"

#define CMD "client"

int main(int argc, char *argv[])
{
    int sock, ret;
    struct sockaddr_in *adrServ;
    int want_to_play = VRAI;
    char ligne[LIGNE_MAX];
    int lgEcr;
    char pseudo[50];

    if (argc != 3)
        erreur("usage: %s machine port\n", argv[0]);

    printf("%s: creating a socket\n", CMD);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        erreur_IO("socket");

    printf("%s: DNS resolving for %s, port %s\n", CMD, argv[1], argv[2]);
    adrServ = resolv(argv[1], argv[2]);
    if (adrServ == NULL)
        erreur("adresse %s port %s inconnus\n", argv[1], argv[2]);

    printf("%s: adr %s, port %hu\n", CMD,
           stringIP(ntohl(adrServ->sin_addr.s_addr)),
           ntohs(adrServ->sin_port));

    printf("%s: connecting the socket\n", CMD);
    ret = connect(sock, (struct sockaddr *)adrServ, sizeof(struct sockaddr_in));
    if (ret < 0)
        erreur_IO("connect");

    start();
    gamertag(pseudo);
    while (want_to_play)
    {
        ecrireLigne(sock, pseudo);
        int fin = FAUX;

        waiting();
        lireLigne(sock, ligne);
        puts("je teste");
        if (strncmp(ligne, "ok", 2) != 0)
            erreur_IO("pseudo");

        compte_a_rebours();

        lireLigne(sock, ligne);
        puts(ligne);
        while (!fin)
        {
            printf("> ");
            if (fgets(ligne, LIGNE_MAX, stdin) == NULL)
                erreur("saisie fin de fichier\n");

            lgEcr = ecrireLigne(sock, ligne);
            if (lgEcr == -1)
                erreur_IO("ecrire ligne");
            lireLigne(sock, ligne);
            printf("%s\n", ligne);
            if (strncmp(ligne, "wrong", 5) != 0)
            {
                fin = VRAI;
            }
        }

        char players_in_order[NUMBER_OF_PLAYER][50];
        for (int i = 0; i < NUMBER_OF_PLAYER; i++)
            lireLigne(sock, players_in_order[i]);

        results(players_in_order[0], players_in_order[1], players_in_order[2], players_in_order[3]);

        char res = getchar();

        if (res == 'E')
        {
            want_to_play = FAUX;
            strcpy(ligne, "exit");
            ecrireLigne(sock, ligne);
            end();
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