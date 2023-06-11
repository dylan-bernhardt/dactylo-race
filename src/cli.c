#include "app.h"
#include "menu.h"

#define CMD "client"

int main(int argc, char *argv[])
{
    /*
    initializes variables
    */
    char my_gamertag[50];
    int soc, ret, lgEcr;
    struct sockaddr_in *adrServ;

    if (argc != 3)
        erreur("usage: %s machine port\n", argv[0]);

    soc = socket(AF_INET, SOCK_STREAM, 0);
    if (soc < 0)
        erreur_IO("socket");

    adrServ = resolv(argv[1], argv[2]);
    if (adrServ == NULL)
        erreur("adresse %s port %s inconnus\n", argv[1], argv[2]);

    ret = connect(soc, (struct sockaddr *)adrServ, sizeof(struct sockaddr_in));
    if (ret < 0)
        erreur_IO("connect");

    start();
    gamertag(my_gamertag);
    lgEcr = ecrireLigne(soc, my_gamertag);
    if (lgEcr == -1)
        erreur_IO("ecrireLigne");

    if (close(soc) == -1)
        erreur_IO("close");

    exit(EXIT_SUCCESS);
}
