#ifndef __GAME_H__
#define __GAME_H__

/**
 * @brief free les accesoirs d'un perso et le perso si il est mort en 
 * parcourant la liste circulaire
 * 
 * @param liste_perso liste circulaire de perso
 * @param nombre un pointeur sur Nb pour decrementer le nombre de perso
 */
void gererPersoMort(List_circ* liste_perso,Nb* nombre);


/**
 * @brief gerer l'attaque d'un perso ou d'un ennemis 
 * 
 * @param perso le perso qui attaque 
 * @param ennemis l'ennemis qui attaque ou qui se fait attaquer
 * @param attaquant un enum pour savoir qui attaque 
 */
void gererAttaque(Perso *perso,Ennemis *ennemis,Attaquant attaquant);


/**
 * @brief gere la guerison d'un cooéquipier 
 * 
 * @param perso_combat la liste circulaire de perso
 * @param perso le perso qui va soigner
 * @param aff un enum pour savoir si on est en ascii ou en graphics
 */
void gererRest(List_circ* perso_combat,Perso* perso,AFFICHAGE aff);


/**
 * @brief active le activer_defense du personnage
 * 
 * @param perso le personnage qui a activer sa defense
 */
void gererDefense(Perso* perso);

/**
 * @brief l'ennemi attaque un perso aleatoire dans la liste des combattants
 * 
 * @param ennemis l'enemi qui attaque a ce niveau
 * @param perso_combat la liste circulaire des combattants
 * @param nombre un pointeur sur Nb pour decrementer le nombre de combattant
 */
void attaqueAleatoirePerso(Ennemis * ennemis,List_circ* perso_combat,Nb *nombre);


/**
 * @brief appelle les fonctions pour gerer l'attaque d'un ennemis
 * 
 * @param ennemis l'ennemis qui attaque
 * @param perso_combat la liste pour attaquer aleatoirement un perso 
 * @param nombre un pointeur sur Nb pour decrementer le nombre de combattant
 */
void tourEnnemis(Ennemis* ennemis,List_circ* perso_combat,Nb *nombre);

/**
 * @brief gere le tour d'un perso avec un switch sur les actions possibles
 * 
 * @param perso_combat liste circulaire de perso
 * @param ennemis l'enemmi du niveau
 * @param aff un enum pour savoir si on est en ascii ou en graphics
 * @return TypeAction si c'est QUITTE pour sauvegarder
 */
TypeAction tourPerso(List_circ* perso_combat,Ennemis* ennemis,AFFICHAGE aff);

/**
 * @brief Gere le niveau en faisant des tours de combat jusqu'a certaine conditions
 * 
 * @param perso_combat la liste circulaire des combattants
 * @param ennemis l'enemi du niveau
 * @param nombre un pointeur sur Nb pour decrementer/augmenter le nombre de combattant
 * @param aff un enum pour savoir si on est en ascii ou en graphics
 * @return TypeAction si c'est QUITTE pour sauvegarder
 */
TypeAction niveau(List_circ *perso_combat,Ennemis *ennemis,Nb *nombre,AFFICHAGE aff);


/**
 * @brief a la fin d'un donjon on reintegre les perso combattant vivant dans la liste de perso dispo
 * 
 * @param liste  toute les listes chainée
 * @param nombre un pointeur sur Nb pour incrementer le nombre de perso dispo et decrementer le nombre de combattant
 */
void reintegrerPersoDispo(Type_Liste* liste,Nb* nombre);


/**
 * @brief cree un nouvelle accessoire et l'ajoute a la liste des accessoires dispo ou la roulotte
 * 
 * @param liste toute les listes chainée
 * @param roulotte_dispo si c'est pour la roullotte ou les accessoires dispo
 */
void debloquerAcc(Type_Liste* liste,int roulotte_dispo);

/**
 * @brief ajoute 7 HP par combat et si les HP sont egaux a HPmax on met le perosnnage dasn les perso_dispos 
 * 
 * @param liste toute les listes chainée
 * @warning modifie une ou plusieurs liste chainée (le sanniturium et les perso_dispo)
 */
void gererSanitarium(Type_Liste* liste);

/**
 * @brief enleve les personnage de la taverne si ils ont 0 str et enleve 25 str a chaque tour 
 * 
 * @param liste toute les listes chainée
 */
void gererTaverne(Type_Liste* liste);


/**
 * @brief remplis la roulotte avec un nombre aleatoire d'accessoire 
 * 
 * @param liste toute les listes chainée
 */
void remplirRoulotte(Type_Liste* liste);


/**
 * @brief si elle est vide on la remplit et demande ce qu'on veut acheter et ajoute a accessoire dispo
 * 
 * @param liste toute les listes chainée
 * @param aff si on est en ascii ou en graphics
 * @param joueur pour verifier si il a assez d'or
 */
void gererRoulotte(Type_Liste* liste,AFFICHAGE aff,Joueur* joueur);


/**
 * @brief demande si on veut ajouter les acc au nouveau personnage et ajoute si oui
 * 
 * @param liste toute les listes chainée
 * @param aff si on est en ascii ou en graphics
 * @param nv_perso le nouveau personnage gagné dans le combat
 */
void ajouterAccPersoC(Type_Liste* liste,AFFICHAGE aff,Maillon* nv_perso);


/**
 * @brief demande on veut faire quoi du nouveau personnage et on agi en consequence
 * 
 * @param liste le pointeur vers toute les listes chainée pour mettre le nouveau perso ou on veut
 * @param aff un enum pour savoir si on est en ascii ou en graphics
 * @param niveau un int pour savoir si on peut mettre le perso en combat
 * @warning modifie une ou plusieurs liste chainée 
 */
void debloquerNouveauPerso(Type_Liste* liste,AFFICHAGE aff,int niveau,Joueur* joueur);

/**
 * @brief enleve a chaque fin de tour le acriver defense des perso combattants 
 * 
 * @param perso_combat la liste circulaire des combattants
 */
void enleverDefensePerso(List_circ* perso_combat);

/**
 * @brief remplis la vie des ennemis après un donjon
 * 
 * @param donjon la liste du donjon avec les ennemis pour les faire revivre
 */
void revivreEnnemis(List *donjon);


/**
 * @brief gere une partie de donjon en faisant des tours de combat jusqu'a la fin du donjon
 * 
 * @param liste toute les listes chainée
 * @param aff si on est en ascii ou en graphics
 * @param joueur le joueur pour savoir si il a gagné de l'or et lui en ajouté a la fin d'un combat
 * @param execute la structure pour sauvegarder si on quitte en pleine partie
 */
void  donjon(Type_Liste* liste, AFFICHAGE aff,Joueur* joueur,Execute* execute);




/**
 * @brief demande quelle personnage on veut rentrer au sanitarium ou a la taverne et le rentre
 * 
 * @param liste toute les listes chainée
 * @param aff si on est en ascii ou en graphics
 * @param sanniTaverne pour savoir si c'est pour le sanitarium ou la taverne
 */
void rentrerSanniTaverne(Type_Liste*liste,AFFICHAGE aff,int sanniTaverne);


/**
 * @brief gere la ville des qu'on ne combat plus on peut aller en combat, a la roulotte, au sanniturium etc 
 * 
 * @param liste toute les listes chainée
 * @param aff si on est en ascii ou en graphics
 * @param joueur le poiteur vers la struture du joueur 
 * @param execute la structure pour sauvegarder si on quitte en pleine partie
 * @return int si ca c'est bien passé ou pas
 */
int hameau(Type_Liste * liste,AFFICHAGE aff,Joueur* joueur,Execute* execute);


/**
 * @brief la boucle principale du jeu qui appelle les fonctions pour jouer une partie
 * 
 * @param liste toute les listes pour les modifier
 * @param aff si on est en ASCII ou en graphics
 * @param Joueur les info du joueur comme le nom,l'or et le niveau
 * @param execute la structure pour sauvegarder si on quitte en pleine partie
 * @return -1 si il y'a eu des erreurs d'allocation 0 sinon
 */
int mainGame(Type_Liste* liste,AFFICHAGE aff,Joueur*joueur,Execute* execute);


#endif