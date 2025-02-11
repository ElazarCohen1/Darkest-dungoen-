#ifndef __SAUVEGARDE_H__
#define __SAUVEGARDE_H__



/**
 * @brief sauvergarde dans le fichier les informations du joueur
 * 
 * @param joueur le joueur que l'on veut sauvegarder
 * @param fichier le fichier dans lequel on ecrit avec la fonction fprintf
 */
void ecrireJoueur(Joueur joueur,FILE* fichier);

/**
 * @brief ecrit dans le fichier les informations d'un accessoire
 * 
 * @param acc l'acc que l'on veut sauvegarder
 * @param fichier le fichier dans lequel on ecrit
 * @param numero_lst pour retrouver dans quelle liste on a ecris 
 */
void ecrireAcc(Acc acc,FILE* fichier,int numero_lst);

/**
 * @brief ecrit dans le fichier les accessoires disponibles en appelant la fonction ecrireAcc
 * 
 * @param acc_dispo la liste des accessoires disponibles
 * @param fichier le fichier dans lequel on ecrit
 */
void ecrireAccD(List acc_dispo,FILE*fichier);

/**
 * @brief ecrit dans le fichier les accessoires de la roulotte en appelant la fonction ecrireAcc
 * 
 * @param acc_roulotte la liste des accessoires de la roulotte
 * @param fichier le fichier dans lequel on ecrit
 */
void ecrireAccR(ListD_circ acc_roulotte,FILE* fichier);

/**
 * @brief ecrit dans le fichier les informations d'un personnage
 * 
 * @param liste toute les liste pour pouvoir verifier les accessoire et les classes
 * @param perso le personnage que l'on veut sauvegarder
 * @param fichier le fichier dans lequel on ecrit
 * @param numero_lst pour retrouver dans quelle liste on a ecris
 */
void ecrirePerso(Type_Liste*liste,Perso perso,FILE*fichier,int numero_lst);

/**
 * @brief ecrit dans le fichier les personnages disponibles en appelant la fonction ecrirePerso
 * 
 * @param liste toute les liste pour pouvoir l'utiliser dans la fonction ecrirePerso
 * @param fichier le fichier dans lequel on ecrit
 */
void ecrirePersoD(Type_Liste* liste,FILE* fichier);

/**
 * @brief ecrit dans le fichier les personnages en combat en appelant la fonction ecrirePerso
 * 
 * @param liste toute les liste pour pouvoir l'utiliser dans la fonction ecrirePerso
 * @param fichier le fichier dans lequel on ecrit
 */
void ecrirePersoC(Type_Liste* liste,FILE* fichier);

/**
 * @brief ecrit dans le fichier les personnages du sanitarium ou de la taverne en appelant la fonction ecrirePerso
 * 
 * @param liste toute les liste pour pouvoir l'utiliser dans la fonction ecrirePerso
 * @param fichier le fichier dans lequel on ecrit
 * @param sanni_taverne 0 pour le sanitarium et 1 pour la taverne
 */
void ecrirePersoST(Type_Liste* liste,FILE* fichier,int sanni_taverne);

/**
 * @brief ecrit les informations du nombre de personnage, d'accessoire et d'ennemis,etc 
 * 
 * @param nombre la stricture qui contient les nombres de chaque element de la liste 
 * @param fichier le fichier dans lequel on ecrit
 */
void ecrireNombre(Nb* nombre,FILE* fichier);

/**
 * @brief la fonction qui gerer l'ecriture de toute les listes dans le fichier
 * 
 * @param liste toute les listes pour pouvoir les ecrire
 * @param joueur le joueur pour pouvoir l'ecrire
 * @param fichier le poiteur vers le fichier dans lequel on ecrit pour pouvoir l'ouvrir et le fermer
 * @param chemin le chemin du fichier
 * @return int pour savoir si la sauvegarde a reussi ou pas
 */
int sauvegarderPartie(Type_Liste* liste,Joueur joueur,FILE** fichier,const char* chemin);

/**
 * @brief lis le joueur dans le fichier
 * 
 * @param joueur le poitueur vers le joueur pour pouvoir le modifier
 * @param ligne la ligne ou se trouve les informations du joueur
 */
void lireJoueur(Joueur **joueur,char*ligne);

/**
 * @brief lis un accessoire dans le fichier
 * 
 * @param ligne la ligne ou se trouve les informations de l'accessoire
 * @return Maillon* le maillon qui contient l'accessoire
 */
Maillon* lireAcc(char*ligne);

/**
 * @brief lis un personnage dans le fichier en mettant sa classe et rajoute ses accessoires si il en avais 
 * 
 * @param liste toute les listes pour pouvoir verifier les accessoires et les classes
 * @param ligne la ligne ou se trouve les informations du personnage
 * @return Maillon* le maillon qui contient le personnage
 */
Maillon* lirePerso(Type_Liste* liste,char*ligne);

/**
 * @brief lis les informations du nombre de personnage, d'accessoire et d'ennemis,etc
 * 
 * @param nombre le nombre pour pouvoir le modifier
 * @param ligne la ligne ou se trouve les informations du nombre
 */
void lireNombre(Nb* nombre,char*ligne);

/**
 * @brief gere la lecture de toute les listes dans le fichier
 * 
 * @param liste toute les listes pour pouvoir les modifier
 * @param fichier le poiteur vers le fichier dans lequel on lit pour pouvoir l'ouvrir et le fermer
 * @param chemin le chemin du fichier
 * @param joueur le joueur pour pouvoir le modifier
 * @return int si la lecture a reussi ou pas
 */
int lancerSauvegarde(Type_Liste* liste,FILE**fichier,const char* chemin,Joueur** joueur);




#endif 