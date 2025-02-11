#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__
#include <MLV/MLV_all.h>

/**
 * @brief initialise la fenetre graphics 
 * 
 */
void initialiserFenetre();

/**
 * @brief affiche sur la fenetre graphics un texte donnée en parametre 
 * utilise ssprintf
 * 
 * @param x la coordonée en abscisse pour affihcer le texte 
 * @param y la coordonée en ordonée pour affihcer le texte 
 * @param texte le texte a afficher avec des %d,s etc possible
 * @param valeur la valeur a remplacer dans les % 
 * @param font une font de texte pour afficher le texte
 * @param couleur une MLV_COLOR pour la couleur du texte
 */
void afficherTexteFormate(int x, int y, const char* texte, int valeur, MLV_Font* font, MLV_Color couleur);

/**
 * @brief affiche les accessoires pour choisir en combat 
 * 
 * @param accessoire l'accessoire que l'on veut afficher  
 */
void afficherInfoAccG(Acc accessoire);

/**
 * @brief gère les accessoires pendant le combat si on veut l'ajouter ou passer au suivant etc 
 * utilise la fonction afficherInfoAccG
 * 
 * @param acc_dispo la liste des accessoires disponible 
 * @return Maillon* renvoie le Maillon* contenant l'accessoire a mettre sur le personnage 
 */
Maillon* gererAccessoireG(List* acc_dispo);


/**
 * @brief affiche les ennemis en combat en afichant surtout les images et leur barre de vie
 * 
 * @param ennemis l'ennemis a afficher
 */
void afficherEnnemisG(Ennemis ennemis);

/**
 * @brief afficher les informations d'un personnage sur une fenetre de fond gris avec la phtos de la classe du personnage 
 * 
 * @param perso le personnage a afficher 
 */
void afficherPersoG(Perso perso);   

/**
 * @brief affiche l'image du Hameau 
 * 
 */
void afficherHameauG();

/**
 * @brief gere les clics sur le hameau (cette fonction est utilisé dans game.c pour gerer le hameau)
 * 
 * @return Hameau le choix que l'on a fait dans le hameau(qui peut etre le donjon les infos etc)
 */
Hameau gererHameauG();

/**
 * @brief gere la guerison d'un autre personnage en plein combat en cliquant sur le R et sur un perso a guerir
 * 
 * @param perso_combat la liste des perso combattant pour savoir sur quelle perso on clique 
 * @return int le numero du personnage que l'on veut guerir  
 */
int gererRestGraphics(List_circ *perso_combat);

/**
 * @brief affiche les persos en combat (des images différents des infos des personnages)
 * 
 * @param perso_combat la liste des personnage combattants
 */
void afficherPersoCombatG(List_circ perso_combat);

/**
 * @brief affiche les infos necessaire pour un combat comme l'image de fond et les boutons pour attaquer etc
 * 
 * @param perso_combat la liste des personnages combattants 
 * @param ennemis l'ennemis du niveau pour appeler la fonction afficherEnnemisG
 */
void afficherCombat(List_circ perso_combat,Ennemis ennemis);


/**
 * @brief gere le nouveau personnage en combat apres les niveaux pair 
 * 
 * @param liste toute les listes chainée 
 * @param joueur les informations du joueur 
 * @return int le choix que l'on a fait sur on on veut le mettre ou ajouter un accessoire
 */
int gererNvPerso(Type_Liste* liste,Joueur* joueur);

/**
 * @brief affiche les informations du personnage et l'or du joueur. diffère un peu si en_combat est vrai 
 * 
 * @param joueur les informations du joueur pour afficher l'or 
 * @param en_combat si on est en combat on n'affiche pas le bouttons next ou on change le titre 
 */
void afficherInfo(Joueur joueur,int en_combat);

/**
 * @brief gere la fenetre des infos si on veut mettre le personnage en combat etc
 * 
 * @param liste toute les listes chainée  
 * @param joueur les infos du joueur 
 */
void gererInfo(Type_Liste* liste,Joueur* joueur);

/**
 * @brief les actions du combat 
 * 
 * @return TypeAction le type de l'action si c'est attque defense guerir ou quittez 
 */
TypeAction ActionGraphique();

/**
 * @brief gere la roulotte pour achetez les accessoires regarde ou on clique principalement
 * 
 * @param acc_roulotte la liste d'accessoires de la roulotte
 * @return int le numero de l'accessoire a acheter pour continuer dans game.c
 */
int gererRoulotteG(ListD_circ acc_roulotte);

/**
 * @brief affiche les accessoires de la roulotte
 * 
 * @param accessoire_roulotte la liste des accessoires de la roulotte
 */
void afficherRoulotteG(ListD_circ accessoire_roulotte);





#endif
