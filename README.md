# Projet Darkest Dungeon Clone

## Description
Ce projet est une réplique du jeu **Darkest Dungeon**, avec une partie graphique affichable soit sur le terminal, soit via une interface graphique. Il est accompagné d'une documentation complète du code ainsi qu'un rapport explicatif.

## Structure du Projet
Le projet est organisé comme suit :



```
/               # Racine du projet
|-- ascii.c     # Gestion des caractères ASCII pour l'affichage
|-- ascii.h     # Header du module ASCII
|-- donnee.h    # Gestion des données
|-- font/       # Dossier des polices utilisées
|-- game.c      # Fichier principal du jeu
|-- game.h      # Header du jeu
|-- graphics.c  # Module d'affichage graphique
|-- graphics.h  # Header du module graphique
|-- image/      # Dossier contenant les images
|-- latex/      # Dossier avec les fichiers LaTeX (pour la documentation)
|-- main.c      # Point d'entrée du programme
|-- Makefile    # Script de compilation
|-- master.c    # Gestion principale du jeu
|-- master.h    # Header du module principal
|-- projet_2024_2025.pdf # Documentation détaillée
|-- rapport/    # Dossier contenant le rapport
|-- rapport.pdf # Rapport explicatif
|-- README.md   # Ce fichier
|-- sauvegarde.c  # Gestion des sauvegardes
|-- sauvegarde.h  # Header du module sauvegarde
|-- save.txt      # Fichier de sauvegarde des parties
```

## Compilation et Exécution

Pour compiler le projet, il suffit d'utiliser `make` :
```sh
make
```
Cela générera l'exécutable **projet**.

Pour lancer le jeu :
```sh
./projet (avec les options preciser dans le rapport)
```

## Dépendances
Assurez-vous d'avoir les bibliothèques nécessaires pour la compilation. Si besoin, installez-les avec :
```sh
sudo apt-get install build-essential
sudo apt-get install libsdl2-dev libsdl2-image-dev
```
(adaptez selon votre OS)

## Licence
Ce projet est sous licence MIT - voir le fichier [LICENSE](LICENSE) pour plus de détails.

## Auteurs
- [Cohen Elazar](https://github.com/ElazarCohen1)

---

Ce fichier est prêt pour être utilisé sur GitHub. Ajoutez-le simplement à votre dépôt et poussez les modifications ! 🚀

