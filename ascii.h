#ifndef ASCII_H
#define ASCII_H

#include "donnee.h"

/**
 * @brief affiche le debut du jeu
 * 
 * @param perso_dispo une liste de perso dispo
 * @param classe_dispo une liste de classe dispo
 * @return int si tout c'est bien passer
 */
int affichageDebutAscii(List perso_dispo, List classe_dispo);

/**
 * @brief affiche un perso en tableau tout beau 
 * 
 * @param perso un perso a afficher
 */
void afficherPerso(Perso perso);

/**
 * @brief affiche une classe en tableau tout beau
 * 
 * @param classe une classe a afficher
 */
void afficherAccessoire(Acc acc);

/**
 * @brief affiche les accessoires des personnages en combat sous forme de tableau
 * 
 * @param perso_c la liste des personnages combattant
 */
void afficherAccPersoC(List_circ perso_c);

/**
 * @brief affiche une liste de perso dispo en utilisant la fonction afficherPerso
 * 
 * @param liste une liste de perso dispo
 */
void afficherPersoD(List liste);

/**
 * @brief affiche une liste de classe dispo en utilisant la fonction afficherClasseD
 * 
 * @param liste une liste de classe dispo
 */
void afficherClasseD(List liste);

/**
 * @brief affiche une liste de perso combattant en utilisant la fonction afficherPerso
 * 
 * @param liste une liste de perso combattant
 */
void afficherPersoC(List_circ perso_c);

/**
 * @brief affiche une liste d'accessoire dispo en utilisant la fonction afficherAccessoire
 * 
 * @param liste une liste d'accessoire dispo
 */
void afficherAccDAscii(List liste);

/**
 * @brief affiche les accesssoires dans la roulotte sous forme de tableau 
 * 
 * @param acc_roulotte la liste des accessoire a la roulotte 
 */
void afficherAccRoulotteAscii(ListD_circ  acc_roulotte);


/**
 * @brief fais une  boucle pour choisir les combattants et les ajouter a la liste de combattant 
 * 
 * @param liste toute les listes chainees
 * @warning modifie la liste de perso dispo et la liste de perso combattant et le nombre de combattant_dispo
 */
void choisirCombattantAscii(Type_Liste *liste);

/**
 * @brief fais une boucle pour choisir les accessoires et les ajouter a la liste des accessoires dispo
 * 
 * @param liste toute les listes chainees
 * @warning modifie la liste de perso combattant et la liste d'accessoire dispo et le nombre d'accessoire dispo
 */
void choisirAccessoireAscii(Type_Liste*liste);

/**
 * @brief affiche  en ligne au debut de la partie les personnages choisi pour combattre
 * 
 * @param perso_c une liste circulaire de perso combattant
 */
void affichagePersoChoisi(List_circ perso_c);

/**
 * @brief affiche le donjon pour les tests (faut que je l'enleve a la fin)
 * 
 * @param donjon la liste de donjon avec les ennemis 
 */
void afficherDonjon(List donjon);

/**
 * @brief demande quelle action pour le personnage en combat
 * 
 * @param perso_c un perso combattant
 * @return TYPE_ACTION un enmum pour l'action a effectuer
 */
TypeAction demandeActionAscii(Perso perso_c);


#endif 