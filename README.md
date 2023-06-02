# dactylo_race

## Présentation générale

Notre application est un jeu multijoueur. Le but est d'écrire correctement une phrase le plus rapidement possible pour gagner.

## Fonctionnement

Tout d'abord, le serveur host se met en attente de suffisammenet de joueurs. Une fois le nombre de joueurs atteint, l'host peut lancer le jeu et chaque joueur voit alors une phrase s'afficher sur son écran. Chaque joueur possède la même phrase et le premier joueur à l'écrire correctement gagne la partie. A la fin de la partie, l'host peut relancer une partie *avec les joueurs n'ayant pas quitté la partie* ou relancer le jeu.    


## Structure 

L'application utilise une barrière pour attendre le nombre de joueurs. La barrière peut cependant être cassée par l'hôte pour lancer le jeu avec un nombre de joueurs inférieur au nombre recommandé.   
La phrase à taper est envoyée à chaque joueur via un socket.   
*Un sémaphore permet de détecter lorsqu'un joueur à écrit correctement la phrase et termine ainsi le jeu.*