# dactylo_race

## Présentation générale

Notre application est un jeu multijoueur. Le but est d'écrire correctement une phrase le plus rapidement possible pour gagner.

## Stucture de l'archive

Les codes sources se trouvent dans le dossier src/.
Dans modules/ et include/ se trouvent les librairies utiles à l'application. Nous avons repris quelques fichiers des tps réalisés en cours. 
(précisé en commentaire dans les fichiers)

## Installation des librairies

Pour installer les librairies, 
	cd modules/ 
	make
Ceci crée un fichier dans lib/

## Compilation du code source

Pour compiler le code source 
	cd src/
	make

Deux fichiers apparaissent : client.c & serveur.c 
Nous ne compilons malheuresement pas avec l'option pedantic qui génère des erreurs sur les fichiers resolv.c et resolv.h que nous avons simplement copié des anciens TPs. (Nous n'avons pas eu le temps de corriger les erreurs et avons ainsi décider de compiler sans l'option -pedantic). Nous compilons cependant avec les options -W et -Wall !

## Utilisation

Le serveur doit lancer le l'executable serveur et passer le port en argument :
	./serveur 2000 (par exemple)

Les joueurs executent l'executable client avec l'ip du serveur et le port en argument :
	./client 192.128.21.1 2000

## Changer la phrase à écrire 

La phrase à écrire le plus vite se trouve dans le fichier sentences.txt. Pour changer la phrase à écrire, il suffit d'effacer et d'écrire une nouvelle phrase dans le fichier !

## Changer le nombre de joueurs

Le nombre de joueurs est 4 par défaut, même si cela peut être changer dans les codes sources :
	cd modules/
	code app.h (ou vim app.h... en fonction de votre éditeur de texte)
	Modifier la ligne #define NUMBER_OF_PLAYER 4 avec le nombre de joueur voulu.

Il reste à recompiler les librairies :
    cd lib/
    rm *
    cd ../modules/
    make
    cd ../src/
    make clean
    make

Le nombre de joueurs est désormais changé. 

## Contact

Nous restons à disposition pour tout éventuel "bug" aux adresses mails suivantes :
	dylan.bernhardt@etu.emse.fr
	corentin.bunaux@etu.emse.fr

(espérons que ça ne soit pas utile)
