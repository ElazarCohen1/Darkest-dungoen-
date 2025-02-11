#ifndef DONNEE_H
#define DONNEE_H

#include <stdlib.h>
#include <stdio.h>

#define LEN_ROLL 41
#define LEN_NOM_ACC 50
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 700
#define RECTANGLE_PERSO_W 150
#define RECTANGLE_PERSO_H 300



typedef enum _affichage{
    ASCII,
    GRAPHICS
}AFFICHAGE;


typedef enum _type_action{
    ATTAQUE,
    DEFENSE,
    REST,
    QUITTE
}TypeAction;

typedef enum _attaquant{
    PERSONNAGE,
    ENNEMIS
}Attaquant;

typedef enum _hameau{
    INFO = 0,
    DONJON = 1,
    ROULOTTE = 2,
    SANNITARIUM = 3,
    TAVERNE = 4,
    QUITTER = 5,
    COMBAT = 6,
}Hameau;


// les parametres du jeu
typedef struct _param{
    AFFICHAGE aff;
    char* fichier_sauvegarde;
    char* fichier_chargement;
}Param; 

typedef struct _point{
    int x;
    int y;
}Point;


typedef struct _nb{
    int perso_total;
    int perso_dispo;
    int nb_combattant;
    int nb_classe;
    int accessoire_dispo;
    int accessoire_roulotte;
    int nb_ennemis;
    int perso_sanni;
    int perso_taverne;
    int accessoire_total;

}Nb;

typedef struct _joueur{
    char* nom;// a allouer 
    int or;
    int niveau; // le niveau du joueur dans le jeu
}Joueur;



/*-----------listes simple générale--------------*/
typedef struct _simple{
    struct _simple* next;
}*List,*List_circ,Maillon;

/*-----------listes double générale--------------*/
typedef struct _double{
    struct _double* prev;
    struct _double* next;
}*ListD,*ListD_circ,MaillonD;

typedef struct _classe{
    int num;
    char* nom;
    int att; //attaque
    int def; //defensse
    int HPmax; // point de vie
    int rest; // soigner un camarade 
}Classe;

/*----------listes pour les classes dispo---------*/
typedef struct _classeD{
    List base;
    Classe classe;
}ClasseD;

typedef struct _accessoire{
    int num;
    char* nom;
    int prix;
    int attbonus; // attaque en plus 
    int defbonus;// defense en plus 
    int HPbonus;// vie en plus 
    int restbonus;//soigner camarades
    int strred; // nb de stresse en moins 
    Point zone_roulotte;// en graphics ou est afficher l'acc(le point en haut a gauche du boutton)
}Acc; // que par un personnage a la fois


typedef struct _ennemis{
    char* nom; 
    int niveau;
    int atten;
    int defenn;
    int HPenn;
    int HPennMax;
    int attstrenn;// attaque de stresse
}Ennemis;

/*----------listes pour le donjon----------------*/
typedef struct _donjon{
    List base;
    Ennemis ennemis;
}Salle,Donjon;



/*----------listes pour les accessoires dispo ----------*/

typedef struct _accessoireD{
    List base;
    Acc accessoire;
}AccD,MaillonAcc; // les accessoires du joueurs 

/*----------listes pour les accessoires roulotte ----------*/

typedef struct _accessoireR{
    struct _double base;
    Acc accessoire;
}AccR,MaillonAccD;


typedef struct _personnage{
    int num;// num du perso (pour choisir)
    char *nom;// le nom du perso (surtout pour l'affichage) 
    Classe classe;
    int att;
    int def;
    int HP;
    int HPmax;
    int rest; // guerir de combien un autre perso
    int str;// stresse du perso
    int nbcomb; // nombre de combat effectuée 
    int activer_defense; // booleen pour savoir si le perso a activer sa defense
    MaillonAcc *acc1;
    MaillonAcc *acc2;
    Point zone_graphics;
}Perso;

/*----------listes pour les perso dispo----------*/
typedef struct _persoD{
    List base;
    Perso personnage;
}PersoD;

/*----------listes pour les perso en combat ----------*/

typedef struct _persoC{
    List_circ base;
    Perso personnage;
}PersoC;

/*----------listes pour les perso au saniturium ----------*/

typedef struct _persoS{
    struct _double base;
    Perso personnage;
}PersoS,PersoT;



typedef struct _liste{
    List classe_dispo;// pas besoin de sauvegarder
    List personnage_dispo;
    List_circ perso_combat;
    ListD_circ perso_sanitarium;
    ListD_circ perso_taverne;
    List accessoire_dispo;
    ListD_circ accessoire_roulotte;
    List donjon; // pas besoin de sauvegarder
    Nb *nombre;
    char* nom_acc[LEN_NOM_ACC];
}Type_Liste;


typedef struct _close_execute{
    Type_Liste *liste;
    Joueur *joueur;
    FILE ** fichier;
    char* fichier_sauvegarde;
    char* fichier_chargement;
    int sauvegarde_milieu;
}Execute;
#endif