#ifndef MASTER_H
#define MASTER_H


/** 
 * @param   : aucun 
 * @brief   : initialise toute les listes chainée a NULL et le nombre a 0
 * @return  : une Type_Liste 
 * @note    : modifie 
 * @warning : fais un malloc pour allouer le Type_Liste (pensez a le free)
*/
Type_Liste * initialiser_liste();

/**
 * @brief initialise le joueur si il n'y a pas de jeu sauvegarder
 * 
 * @param aff si on est en ASCII ou graphics
 * @return Joueur* le joueur initialiser 
 * @warning on alloue la place pour le nom et le joueur
 */
Joueur* initialiserJoueur(AFFICHAGE aff);

/**
 * @brief alloue une classe 
 * @param nom un char* pour afficher le nom plus tard
 * @param att un int pour l'attaque
 * @param def un  int pour la defense
 * @param HPmax un int pour les points de vie max
 * @param rest un int pour soigner un camarade
 * @param nombre un pointeur sur Nb pour incrementer le nombre de classe
 * @return Maillon* une cellule de type Maillon ou NULL si erreur
 * @warning 1 mallocs pour le Maillon*
 */
Maillon* creerClasse(int num,char* nom,int att,int def,int HPmax,int rest,Nb *nombre);

/**
 * @brief alloue un Maillon* pour un personnage
 * 
 * @param classe de type Classe pour la classe du perso
 * @param nom un char* pour le nom du perso
 * @param num un int pour le numero du perso
 * @param nombre un pointeur sur Nb pour incrementer le nombre de perso
 * @return Maillon* pour le perso ou NULL si erreur
 * @warning 2 malloc pour le Maillon* et le nom
 */

Maillon* creerPerso(Classe classe,char*nom,int num,Nb * nombre);


/**
 * @brief alloue un Maillon* pour un ennemis
 * 
 * @param niveau un int pour le niveau dans le donjon 
 * @param atten un int pour l'attaque de l'ennemis
 * @param defenn un int pour la defense de l'ennemis
 * @param HPenn un int pour les points de vie de l'ennemis
 * @param attstrenn un int pour attaque de stresse
 * @param nombre un pointeur sur Nb pour incrementer le nombre d'ennemis
 * @return Maillon* pour l'ennemis ou NULL si erreur
 * @warning 1 malloc pour le Maillon*
 */
Maillon* creerEnnemis(char* nom,int niveau,int atten,int defenn,int HPenn,int attstrenn,Nb *nombre);

/**
 * @brief alloue un Maillon* pour un accessoire
 * 
 * @param nom un char* pour le nom de l'accessoire
 * @param num un int pour le numero de l'accessoire
 * @param prix le prix de l'accessoire
 * @param attbonus un int pour l'attaque en plus
 * @param defbonus un int pour la defense en plus
 * @param HPbonus un int pour les points de vie en plus
 * @param restbonus un int pour soigner camarades
 * @param strred un int pour le nombre de stresse en moins
 * @return Maillon* pour l'accessoire ou NULL si erreur
 * @warning 2 mallocs pour le MaillonD* et le nom
 */
MaillonD* creerAccessoire(char* nom,int num,int prix,int attbonus,int defbonus,int HPbonus,int restbonus,int strred);

/**
 * @brief extrait le maillon ou le num correspond au maillon 
 * 
 * @param liste liste simple pour les perso 
 * @param elm l'elm que l'on veut extraire
 * @return Maillon* pour le maillon extrait ou NULL si erreur
 */
Maillon* extraitPerso(List *liste ,int elm);

/**
 * @brief extrait le maillon ou le num correspond au maillon 
 * 
 * @param liste liste simple pour les accessoires
 * @param num un int pour le numero de l'accessoire a extraire
 * @return Maillon* le maillon extrait ou NULL si erreur
 */
Maillon* extraitAccD(List *liste,int num);

/**
 * @brief exrtait un maillon d'une liste doublement chainée 
 * 
 * @param liste_acc la liste des accessoires 
 * @param num le numero de l'accessoire que l'on veut extraire 
 * @return MaillonD* l'accessoire que l'on veut extraire
 */
MaillonD* extraitAccR(ListD_circ*liste_acc,int num);

/**
 * @brief verifie si les accessoires des personnages sont deja plein
 * 
 * @param perso_c la liste des perso combattants 
 * @return int 1 si ils sont remplis 0 sinon
 */
int verrifAccPersoCRempli(List_circ perso_c);

/**
 * @brief verifie si une liste est vide 
 * 
 * @param liste une liste simplement chainée 
 * @return int 1 si elle est vide 0 sinon
 */
int is_list_empty(List liste);
/**
 * @brief verifie si le joueur peut acheter un accessoire a la roulotte avec son argent 
 * 
 * @param roulotte la liste chainée de la roulotte 
 * @param joueur les info du joueur avec son or etc 
 * @param num le numero de l'accessoire que l'on veut acheter
 * @return int 1 si il peut achtez 0 sinon
 */
int canAffordAccessory(ListD_circ roulotte,Joueur joueur,int num);

/**
 * @brief ajoute 1 combat au nombre de combat de chaque perso combattant dans la partie 
 * 
 * @param perso_combat la liste des perso combattant
 */
void ajouterNbcombat(List_circ* perso_combat);


/**
 * @brief recherche un perso dans la liste simple (sert surtout pour les verifications)
 * 
 * @param liste une liste simple pour les perso
 * @param num un int pour le numero du perso a rechercher
 * @return int si on a trouver le perso ou non
 */
int recherchePerso(List liste,int num);

/**
 * @brief recherche un accessoire dans la liste simple (sert surtout pour les verifications)
 * 
 * @param liste_accessoire une liste simple pour les accessoires
 * @param num un int pour le numero de l'accessoire a rechercher
 * @return int si on a trouver l'accessoire ou non
 */
int rechercheAcc(List liste_accessoire,int num);

/**
 * @brief recherche dans la roulotte si il y'a l'accessoire que l'on veut acheter  
 * 
 * @param liste_accessoire la liste des accessoires
 * @param num le numero de l'accessoire que l'on veut acheter
 * @return int 1 si on a trouve l'accessoire 0 sinon
 */
int rechercheAccR(ListD_circ liste_accessoire,int num);


/**
 * @brief pas utiliser pour le moment mais sert a rechercher un perso dans la liste circulaire
 * 
 * @param perso_combat une liste circulaire pour les perso
 * @param num un int pour le numero du perso a rechercher
 * @return int 0 si on a pas trouve et 1 si on a trouve
 */
int recherchePersoCirc(List_circ perso_combat,int num);

/**
 * @brief ajout au debut d'une liste simple
 * 
 * @param liste  une liste simple pour les perso
 * @param cel la cellule a ajouter au debut
 */
void ajoutDebut(List* liste,Maillon* cel);

/**
 * @brief ajoute a la fin d'une liste simple
 * 
 * @param liste une liste simple 
 * @param cel une cellule a ajouter a la fin
 */
void ajoutFin(List*liste,Maillon *cel);

/**
 * @brief ajoute a la fin d'une liste circulaire
 * 
 * @param liste une liste circulaire
 * @param maillon une cellule a ajouter a la fin
 * @warning modifie la liste circulaire pour ajouter le maillon
 * @warning ne fais pas de cast donc rete generique
 */
void ajoutFinCirc(List_circ* liste,Maillon*maillon);


/**
 * @brief extrait un maillon d'une  liste circulaire
 * 
 * @param liste une liste circulaire
 * @param perso un perso que l'on veut extraire
 * @return Maillon* le maillon extrait ou NULL si erreur
 * @warning modifie la liste circulaire poour extraire le perso
 */
Maillon* extraireListCirc(List_circ *liste,Perso perso);

/**
 * @brief  libere une liste simple passer en parametre
 * 
 * @param liste la liste simple a liberer
 * @param liberer_perso un int pour savoir si on libere le perso ou non
 * @warning libere la liste simple
 */
void libererList(List *liste,int liberer_perso);

/**
 * @brief libere une liste circulaire
 * 
 * @param liste la liste circulaire a liberer
 * @param liberer_perso un int pour savoir si on libere le perso ou non
 * @warning libere toute la liste circulaire
 */
void libererListCirc(List_circ *liste,int liberer_perso);


/**
 * @brief libere une liste doublement chainee
 * 
 * @param liste la liste double 
 * @param liberer_perso un int pour savoir si on libere le perso ou non
 * @warning libere la liste double 
 */
void libererListeD(ListD* liste,int liberer_perso);

/**
 * @brief liberer toute les listes chainees contenue dans le Type_Liste
 * 
 * @param liste la Type_Liste avec toute les listes chainee pour les liberer
 * @warning libere toute les listes chainee
 */
void LibererTypeListe(Type_Liste *liste);



/**
 * @brief choisi aleatoirement parmis les classes dispos et la renvoie
 * 
 * @param classe_dispo une liste simple pour les classes
 * @param nombre la structure nombre pour le nombre de classe
 * @return Classe* la classe aleatoire choisie
 */
Classe* choisirClasseAleatoire(List classe_dispo,Nb nombre);

/**
 * @brief ajoute au debut d'une liste doublement chainee circulaire
 * 
 * @param liste une liste doublement chainee circulaire
 * @param cel la cellule a ajouter au debut
 * @warning modifie la liste doublement chainee circulaire
 */
void ajoutDebutDcirc(ListD_circ *liste,MaillonD* cel);


/**
 * @brief copier un perso en allouant le necessaire
 * 
 * @param dest la copie du perso
 * @param source la source
 */
void copierPerso(Perso*dest,Perso*source);

/**
 * @brief copier un accessoire en allouant le necessaire (on s'en sert pour AccDToAcc ou AccToAccD)
 * 
 * @param dest la copie de l'acc
 * @param source la source
 */
void copierAccessoire(Acc* dest,Acc* source);

/**
 * @brief transforme un MaillonD* avec un accessoire en Maillon*
 * 
 * @param acc_double l'accessoire que l'on veut transformer
 * @return Maillon* le maillon traforme et qui a ete copier en profondeur
 */
Maillon* AccDToAcc(MaillonD* acc_double);

/**
 * @brief transforme un Maillon* avec un accessoire en MaillonD*
 * 
 * @param acc_simple l'accessoire que l'on veut transformer
 * @return MaillonD* le maillon traforme et qui a ete copier en profondeur
 */
MaillonD* AccToAccD(Maillon* acc_simple);


/**
 * @brief convetie un Maillon* en MaillonD* en copiant le personnage et en initialisant le next et prev du maillonD*
 * 
 * @param perso_simple un maillon contenant un perso
 * @return MaillonD* un maillon d'une liste doublement chainée 
 * @warning on alloue la place pour un PersoS* que l'on caste en MaillonD*
 */
MaillonD* MaillonToMaillonD(Maillon* perso_simple);


/**
 * @brief transforme un MaillonD* en Maillon* en copiant le personnage
 * 
 * @param perso_double un perso doublement chainée
 * @return Maillon* un maillon simple contenant le personnage
 */
Maillon* MaillonDToMaillon(MaillonD* perso_double);

/**
 * @brief libere le nom et les possible accessoire du personnage 
 * 
 * @param perso le perso a qui on veut liberer le nom et les accessoires 
 */
void libererDAccessoireNomPerso(MaillonD *perso);


/**
 * @brief extrait un maillon d'une liste doublement chainée circulaire
 * 
 * @param liste il s'agit d'une liste doublement chainée circulaire
 * @param num le numere du perso/acc a extraire
 * @return MaillonD* la cellule a renvoyer ou NULL si erreur
 */
MaillonD* extraireListDcirc(ListD_circ* liste,int num);


MaillonD* extraireListDcirc2(ListD_circ*liste_acc,int num,int acc_perso);


/**
 * @brief libere la liste des nom d'accessoire qui sert a creer un nouvelle accessoire 
 * 
 * @param nom_acc la liste de char* de nom d'accessoire
 */
void libererNomAcc(char** nom_acc);

/**
 * @brief libere le nom du joueur et la structure contenant le nom
 * 
 * @param joueur 
 */
void libererJoueur(Joueur* joueur);


/**
 * @brief liberer les accessoires du personnage dans le maillon et son nom
 * 
 * @param perso le personnage dont on va liberer les accessoires et le nom
 * @warning libere les accessoires et le nom du personnage
 */
void libererAccessoireNomPerso(Maillon *perso);

/**
 * @brief une reecriture de strdup de string.h car ca ne marchait pas en l'incluant alloue et copier un char*
 * 
 * @param s la chaine a dupliquer
 * @return char*  la chaine dupliquer
 */
char* strdup(const char* s);

/**
 * @brief le main du master qui initialise toute les listes chainee et les ennemis etc 
 * 
 * @param liste la Type_Liste que l'on recupere du main 
 * @return int un code d'erreur  si tout c'est bien passer
 * @warning modifie toute les listes chainee
 */
int mainMaster(Type_Liste *liste,Param param);

#endif