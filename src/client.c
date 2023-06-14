#include "app.h"

#define CMD "client"

int main(int argc, char *argv[])
{
    int sock, ret;
    struct sockaddr_in *adrServ;
    int fin = FAUX;
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

    lireLigne(sock, ligne);
    puts(ligne);

    start();
    gamertag(pseudo);
    waiting();
    while (1)
    {
    }

    while (!fin)
    {
        printf("ligne> ");
        if (fgets(ligne, LIGNE_MAX, stdin) == NULL)
            erreur("saisie fin de fichier\n");

        lgEcr = ecrireLigne(sock, ligne);
        if (lgEcr == -1)
            erreur_IO("ecrire ligne");

        lireLigne(sock, ligne);
        puts(ligne);
        if (strncmp(ligne, "faux", 3) != 0)
        {
            puts("tu as fini");
            fin = VRAI;
        }
    }

    for (;;)
        puts("salut");
    ;
    if (close(sock) == -1)
        erreur_IO("close socket");

    exit(EXIT_SUCCESS);
}