#include <stdio.h>
#include <stdlib.h>
#include "donnee.h"
#include <string.h>
#include <MLV/MLV_all.h>


Type_Liste * initialiser_liste(){
    Type_Liste* liste = (Type_Liste*)malloc(sizeof(Type_Liste));

    liste->classe_dispo = NULL;
    liste->personnage_dispo = NULL;
    liste->perso_combat = NULL;
    liste->perso_sanitarium = NULL;
    liste->perso_taverne = NULL;
    liste->accessoire_dispo = NULL;
    liste->accessoire_roulotte = NULL;
    liste->donjon = NULL;

    liste->nombre = (Nb*)malloc(sizeof(Nb));
    liste->nombre->perso_total = 0;
    liste->nombre->perso_dispo = 0;
    liste->nombre->nb_combattant = 0;
    liste->nombre->nb_classe = 0;
    liste->nombre->accessoire_dispo = 0;
    liste->nombre->nb_ennemis = 0;
    liste->nombre->perso_sanni = 0;
    liste->nombre->perso_taverne = 0;
    liste->nombre->accessoire_roulotte = 0;
    liste->nombre->accessoire_total = 0;
    return liste;
}


Joueur* initialiserJoueur(AFFICHAGE aff){
    Joueur* joueur = (Joueur*)malloc(sizeof(Joueur));
    joueur->nom = (char*)malloc(sizeof(char)*50);
    if(!joueur|| !joueur->nom)return NULL;
    if(aff == ASCII){
        printf("comment voulez vous vous appelez ?(50 caractere maximum) ");
        scanf("%49s",joueur->nom);
    }else{
        char* texte;
        MLV_create_window("nom_joueur","nom_joueur",WINDOW_WIDTH,WINDOW_HEIGHT);
        MLV_wait_input_box(WINDOW_WIDTH/2-100,WINDOW_HEIGHT/2-100,200,100,MLV_COLOR_WHITE,
                            MLV_COLOR_BLACK,MLV_COLOR_WHITE,"entrez votre nom:  ",&texte);
    
        strcpy(joueur->nom,texte);
        free(texte);
        MLV_free_window();
    }
    
    joueur->or = 0;
    joueur->niveau = 0;

    return joueur;

}


Maillon* creerClasse(int num,char* nom,int att,int def,int HPmax,int rest,Nb *nombre){
    ClasseD * cel = (ClasseD*)malloc(sizeof(ClasseD));
    if( !cel)return NULL;
    cel->classe.num   = num;
    cel->classe.nom   = nom;
    cel->classe.att   = att;
    cel->classe.def   = def;
    cel->classe.HPmax = HPmax;
    cel->classe.rest  = rest;

    nombre->nb_classe++;
    
    Maillon* maillon = (Maillon*)cel;// cast pour retourner un Maillon*

    return maillon;
}


Maillon* creerPerso(Classe classe,char*nom,int num,Nb * nombre){
    PersoD* liste_perso = (PersoD*)malloc(sizeof(PersoD));
    liste_perso->personnage.nom = malloc(sizeof(char*)*strlen(nom)+1);
    if (!liste_perso)return NULL;
    liste_perso->personnage.num = num;
    strcpy(liste_perso->personnage.nom,nom);
    
    liste_perso->personnage.classe = classe;
    liste_perso->personnage.att = classe.att;
    liste_perso->personnage.def = classe.def;
    liste_perso->personnage.HP = classe.HPmax;
    liste_perso->personnage.HPmax = classe.HPmax;
    liste_perso->personnage.rest = classe.rest;
    liste_perso->personnage.str = 0;
    liste_perso->personnage.nbcomb = 0;
    liste_perso->personnage.acc1 = NULL;
    liste_perso->personnage.acc2 = NULL;
    liste_perso->personnage.activer_defense = 0;
    Point zone;// la zone graphiquement ou se trouve le pero en combat
    zone.x = zone.y =  -1;
    liste_perso->personnage.zone_graphics = zone;
    nombre->perso_total++;


    Maillon* maillon = (Maillon*)liste_perso;


    return maillon;
}


Maillon* creerEnnemis(char* nom,int niveau,int atten,int defenn,int HPenn,int attstrenn,Nb *nombre){
    Salle* donjon = (Salle*)malloc(sizeof(Salle));
    if (!donjon)return NULL;
    donjon->ennemis.nom = nom;
    donjon->ennemis.niveau = niveau;
    donjon->ennemis.atten = atten;
    donjon->ennemis.defenn = defenn;
    donjon->ennemis.HPenn = HPenn;
    donjon->ennemis.HPennMax = HPenn;

    donjon->ennemis.attstrenn = attstrenn;
    nombre->nb_ennemis++;
    Maillon* cel = (Maillon*)donjon;

    return cel;
}


MaillonD* creerAccessoire(char* nom,int num,int prix,int attbonus,int defbonus,int HPbonus,int restbonus,int strred){
    MaillonAccD*  lst_acc = (MaillonAccD*)malloc(sizeof(MaillonAccD));
    lst_acc->accessoire.nom = (char*)malloc(sizeof(char)*50);
    if (!lst_acc)return NULL;

    lst_acc->accessoire.num = num;
    strcpy(lst_acc->accessoire.nom,nom);
    lst_acc->accessoire.prix = prix;
    lst_acc->accessoire.attbonus = attbonus;
    lst_acc->accessoire.defbonus = defbonus;
    lst_acc->accessoire.HPbonus = HPbonus;
    lst_acc->accessoire.restbonus = restbonus;
    lst_acc->accessoire.strred = strred;
    Point p;
    p.x = p.y = -1;
    lst_acc->accessoire.zone_roulotte = p;
    MaillonD* cel = (MaillonD*)lst_acc;
    cel->next = cel;
    cel->prev = cel;
    return cel;
}

int verrifAccPersoCRempli(List_circ perso_c){
    if(!perso_c)return 0;
    Maillon* debut = perso_c;
    Maillon* tmp = perso_c;
    do{
        PersoC* perso = (PersoC*)tmp;
        tmp = tmp->next;
        if(!perso->personnage.acc1 || !perso->personnage.acc2)return 0;
    }while(tmp != debut);
    return 1;
}

int is_list_empty(List liste){
    return liste == NULL;
}

int recherchePerso(List liste,int num){
    for(;liste;liste = liste->next){
        if(((PersoD*)liste)->personnage.num == num)return 1;
    }
    return 0;
}

int rechercheAcc(List liste_accessoire,int num){
    for(;liste_accessoire;liste_accessoire = liste_accessoire->next){
        if(((AccD*)liste_accessoire)->accessoire.num == num)return 1;
    }
    return 0;
}

int rechercheAccR(ListD_circ liste_accessoire,int num){
    if(!liste_accessoire)return 0;
    MaillonD* debut = liste_accessoire;
    MaillonD* arriere = liste_accessoire->prev; // pour ne pas etre deja egale avec avant au debut
    MaillonD* avant = liste_accessoire;
    do{
        AccR* lst_acc_arriere = (AccR*)arriere;
        AccR* lst_acc_avant = (AccR*)avant;
        

        if(lst_acc_arriere->accessoire.num == num || lst_acc_avant->accessoire.num == num )return 1;
        
        
        arriere = arriere->prev;
        avant = avant->next;
        
    }while(arriere != avant && arriere != debut && avant != debut );
    return 0;
}

int canAffordAccessory(ListD_circ roulotte,Joueur joueur,int num){
    if(!roulotte)return 0;
    MaillonD* debut = roulotte;
    do{
        AccR* acc = (AccR*)roulotte;
        if(acc->accessoire.num == num){// recherche l'accessoire en question 
            if(joueur.or >= acc->accessoire.prix)return 1;
        }
        roulotte = roulotte->next;
    }while(roulotte != debut);
    return 0;
}

void ajoutDebut(List* liste,Maillon* cel){
    if(!cel)return;
    if (!*liste){
        *liste = cel;
        (*liste)->next = NULL;
        return;
        
    }else{
        cel->next = *liste;
        *liste = cel;
    }  
}


void ajoutFin(List*liste,Maillon *cel){
    if(!*liste){
        *liste = cel;
        (*liste)->next = NULL;   
        return;
    }else{
        List tmp = *liste;
        for(;tmp->next;tmp = tmp->next);
        cel->next = tmp->next;
        tmp->next = cel;
    }
}


Maillon* extraitPerso(List *liste ,int elm){
    if(!*liste)return NULL;
    List tmp = *liste;
    if(((PersoD*)*liste)->personnage.num == elm){// si le premier maillon est ce que l'on cherche
        Maillon*cel = *liste;
        *liste = (*liste)->next;
        cel->next = NULL;
        return cel;
    }
    // il apparait dans le reste de la liste ou pas du tout 
    for(;tmp->next;tmp = tmp->next){
        PersoD* lst_perso = (PersoD*)tmp->next;
        Maillon* cel = tmp->next;
        if(lst_perso->personnage.num == elm){// on a trouvé le personnage
            tmp->next = cel->next;
            cel->next = NULL;
            return cel;
        }
    }
    return NULL;
}


Maillon* extraitAccD(List *liste,int num){
    if(!*liste)return NULL;
    List tmp = *liste;
    if(((AccD*)*liste)->accessoire.num == num){
        Maillon* cel = *liste;
        *liste = (*liste)->next;
        cel->next = NULL;
        return cel;
    }
    for(;tmp->next;tmp = tmp->next){
        AccD* list_acc = (AccD*)tmp->next;
        Maillon* cel = tmp->next;
        if(list_acc->accessoire.num == num){
            tmp->next = cel->next;
            cel->next = NULL;
            return cel;
        }
    }
    return NULL;
}


MaillonD* extraitAccR(ListD_circ*liste_acc,int num){
    if(!*liste_acc)return NULL;
    MaillonD* debut = *liste_acc;

    MaillonD* avant = (*liste_acc)->next; // pour parcourir la liste vers la droite
    MaillonD* precedent_avant;
    MaillonD* suivant_avant;

    MaillonD* arriere = *liste_acc;// pour parcourir la liste vers la gauche
    MaillonD* precedent_arriere;
    MaillonD* suivant_arriere;


    do{
        AccR* lst_acc_arriere = (AccR*)arriere;
        AccR* lst_acc_avant = (AccR*)avant;

        precedent_avant = avant->prev;
        suivant_avant = avant->next;

        precedent_arriere = arriere->prev;
        suivant_arriere = arriere->next;

        if(lst_acc_avant->accessoire.num == num){// si vers la droite on a trouvé
            if(*liste_acc == avant)*liste_acc = avant->next;
            if(avant == debut)*liste_acc = NULL;
            precedent_avant->next = suivant_avant;
            suivant_avant->prev = precedent_avant;
            avant->prev = NULL;
            avant->next = NULL;

            return avant;
        }
        if(lst_acc_arriere->accessoire.num == num){// si on a trouve en allant a gauche
            if(*liste_acc == arriere)*liste_acc = arriere->prev;

            precedent_arriere->next = suivant_arriere;
            suivant_arriere->prev = precedent_arriere;
            arriere->prev = NULL;
            arriere->next = NULL;
            return arriere;
        }

        avant = avant->next;
        arriere = arriere->prev;
        
    
    }while(arriere != avant && arriere != debut && avant != debut);
    return NULL;
}



void ajoutFinCirc(List_circ* liste,Maillon*maillon){
    if(!*liste){
        *liste = maillon;
        maillon->next = maillon;
        return;
    }
    Maillon * debut = *liste;
    List_circ tmp = *liste;

    for(;tmp->next!=debut;tmp = tmp->next);// pour liée le dernier maillon avec le deuxieme
    maillon->next = debut;
    tmp->next = maillon;
    
}


Maillon* extraireListCirc(List_circ *liste,Perso perso){
    if(!*liste)return NULL;
    Maillon* debut = *liste;
    Maillon* elm = *liste;
    List_circ tmp = *liste;

    if(((PersoC*)*liste)->personnage.num == perso.num){// si c'est le premier maillon
        if(debut->next == debut){
            *liste = NULL;// on met a NULL si il y'a qu'un maillon
        }else{
            for(;tmp->next != debut; tmp = tmp->next);
            tmp->next = debut->next;
            *liste = (*liste)->next;
        }
        debut->next = NULL;
        return debut;
    }
    do{
        elm = tmp->next;
        if (((PersoC*)elm)->personnage.num == perso.num){
            tmp->next = elm->next;
            elm->next = NULL;
            return elm;
        }
        tmp = tmp->next;
    }while(tmp != debut);
    return NULL;
}


int recherchePersoCirc(List_circ perso_combat,int num){
    Maillon * debut = perso_combat;
    if(!perso_combat)return 0;
    do{
        PersoC* perso = (PersoC*)perso_combat;
        if (perso->personnage.num == num)return 1;
        perso_combat = perso_combat->next;
    }while(perso_combat != debut);
    return 0;
}


Classe* choisirClasseAleatoire(List classe_dispo,Nb nombre){
    int aleatoire = rand() % nombre.nb_classe;
    int index = 0;
    for(;classe_dispo;classe_dispo = classe_dispo->next){
        if(index == aleatoire)
            return &((ClasseD*)classe_dispo)->classe;
        index++;
    }
    return NULL;
}


void ajoutDebutDcirc(ListD_circ *liste,MaillonD* cel){
    if(!*liste){
        *liste = cel;
        cel->next = cel;
        cel->prev = cel;
    }else{
        MaillonD* prev = (*liste)->prev;

        cel->next = *liste;
        cel->prev = (*liste)->prev;
        prev->next = cel;
        (*liste)->prev = cel;
        *liste = cel;
    }
}


MaillonD* extraireListDcirc2(ListD_circ*liste_acc,int num,int acc_perso){
    if(!*liste_acc)return NULL;
    MaillonD* debut = *liste_acc;

    MaillonD* avant = (*liste_acc)->next; // pour parcourir la liste vers la droite
    MaillonD* precedent_avant;
    MaillonD* suivant_avant;

    MaillonD* arriere = *liste_acc;// pour parcourir la liste vers la gauche
    MaillonD* precedent_arriere;
    MaillonD* suivant_arriere;
    AccR* lst_acc_arriere;
    AccR* lst_acc_avant;
    PersoT* lst_acc_arriere_perso;
    PersoT* lst_acc_avant_perso;
    do{
        if(acc_perso == 0){
            lst_acc_arriere = (AccR*)arriere;
            lst_acc_avant = (AccR*)avant;
        }else{
            lst_acc_arriere_perso = (PersoT*)arriere;
            lst_acc_avant_perso  = (PersoT*)avant;
        }
        

        precedent_avant = avant->prev;
        suivant_avant = avant->next;

        precedent_arriere = arriere->prev;
        suivant_arriere = arriere->next;

        if((acc_perso == 0 && lst_acc_avant->accessoire.num == num) || (acc_perso == 1 &&lst_acc_avant_perso->personnage.num == num )){// si vers la droite on a trouvé
            if(*liste_acc == avant)*liste_acc = avant->next;
            if(avant == debut)*liste_acc = NULL;
            precedent_avant->next = suivant_avant;
            suivant_avant->prev = precedent_avant;
            avant->prev = NULL;
            avant->next = NULL;

            return avant;
        }
        if((acc_perso == 0 && lst_acc_arriere->accessoire.num == num)|| (acc_perso == 1 && lst_acc_avant_perso->personnage.num == num)){// si on a trouve en allant a gauche
            if(*liste_acc == arriere)*liste_acc = arriere->prev;

            precedent_arriere->next = suivant_arriere;
            suivant_arriere->prev = precedent_arriere;
            arriere->prev = NULL;
            arriere->next = NULL;
            return arriere;
        }

        avant = avant->next;
        arriere = arriere->prev;
        
    
    }while(arriere != avant && arriere != debut && avant != debut);
    return NULL;
}


// fonction a revoir et optimiser 
MaillonD* extraireListDcirc(ListD_circ* liste,int num){
    if(!*liste)return NULL;
    MaillonD* debut = *liste;
    MaillonD* precedent = (*liste)->prev;
    MaillonD* elm = *liste;
    MaillonD* suivant = (*liste)->next;

    PersoS* info_perso = (PersoS*)elm;
    if(info_perso->personnage.num == num){
        if(debut->next == debut)
            *liste = NULL;
        else{
            precedent->next = suivant;
            suivant->prev = precedent;
            *liste = suivant;
            elm->next = NULL;
            elm->prev = NULL;
        }
        return elm;
    }
    do{
        precedent = elm->prev;
        suivant = elm->next;
        PersoS* info_perso = (PersoS*)suivant;
        if(info_perso->personnage.num == num){
            precedent->next = suivant;
            suivant->prev = precedent;
            elm->next = NULL;
            elm->prev = NULL;
            return elm;
        }
        elm = suivant;
    }while(elm != debut);
    return NULL;
}


void libererAccessoireNomPerso(Maillon *perso){
    if(!perso)return;
    PersoD* info_perso = (PersoD*)perso;
    free(info_perso->personnage.nom);
    info_perso->personnage.nom = NULL;
    if(info_perso->personnage.acc1){
        free(info_perso->personnage.acc1->accessoire.nom);
        free(info_perso->personnage.acc1);
        info_perso->personnage.acc1 = NULL;
    }
    if(info_perso->personnage.acc2){
        free(info_perso->personnage.acc2->accessoire.nom);
        free(info_perso->personnage.acc2);
        info_perso->personnage.acc2 = NULL;
    }
   
}


void libererDAccessoireNomPerso(MaillonD *perso){
    if(!perso)return;
    PersoS* info_perso = (PersoS*)perso;
    free(info_perso->personnage.nom);
    info_perso->personnage.nom = NULL;
    if(info_perso->personnage.acc1){
        free(info_perso->personnage.acc1->accessoire.nom);
        free(info_perso->personnage.acc1);
        info_perso->personnage.acc1 = NULL;
    }
    if(info_perso->personnage.acc2){
        free(info_perso->personnage.acc2->accessoire.nom);
        free(info_perso->personnage.acc2);
        info_perso->personnage.acc2 = NULL;
    }
   
}


void copierPerso(Perso*dest,Perso*source){
    if(!dest || !source)return;
    dest->nom = (char*)malloc(sizeof(char)*strlen(source->nom)+1);
    if(!dest->nom)return;
    strcpy(dest->nom,source->nom);


    if(source->acc1){
        dest->acc1 = (MaillonAcc*)malloc(sizeof(MaillonAcc));
        if(!dest->acc1)return;
        dest->acc1->accessoire.nom = (char*)malloc(sizeof(char)*50);
        if(!dest->acc1->accessoire.nom){
            free(dest->acc1);
            return;

        }
        
        strcpy(dest->acc1->accessoire.nom,source->acc1->accessoire.nom);
        dest->acc1 = source->acc1;

    }else   
        dest->acc1 = NULL;

    if(source->acc2){
        dest->acc2 = (MaillonAcc*)malloc(sizeof(MaillonAcc));
        dest->acc2->accessoire.nom = (char*)malloc(sizeof(char)*50);
        if(!dest->acc2 ||!dest->acc2->accessoire.nom ){
            free(dest->acc2);
            free(dest->nom);
            return;
        }
        strcpy(dest->acc2->accessoire.nom,source->acc2->accessoire.nom);
        dest->acc2 = source->acc2;
    }else
        dest->acc2 = NULL;
    dest->num = source->num;

    dest->classe = source->classe;
    dest->att = source->att;
    dest->def = source->def;
    dest->HP = source->HP;
    dest->HPmax = source->HPmax;
    dest->rest = source->rest;
    dest->str = source->str;
    dest->nbcomb = source->nbcomb;
    dest->activer_defense = source->activer_defense;

}


void copierAccessoire(Acc* dest,Acc* source){
    if(!dest|| !source )return;
    dest->nom = (char*)malloc(sizeof(char)*strlen(source->nom)+1);
    if(!dest->nom)return;
    dest->num = source->num;
    strcpy(dest->nom,source->nom);
    dest->prix = source->prix;
    dest->attbonus = source->attbonus;
    dest->defbonus = source->defbonus;
    dest->HPbonus = source->HPbonus;
    dest->restbonus = source->restbonus;
    dest->strred = source->strred;
  
}


Maillon* AccDToAcc(MaillonD* acc_double){
    if(!acc_double)return NULL;

    AccD* info_acc_simple= (AccD*)malloc(sizeof(AccD));
    if(!info_acc_simple)return NULL;

    AccR* info_acc_double = (AccR*)acc_double;
    copierAccessoire(&info_acc_simple->accessoire,&info_acc_double->accessoire);

    Maillon* acc_simple = (Maillon*)info_acc_simple;
    acc_simple->next = NULL;

    free(info_acc_double->accessoire.nom);
    free(acc_double);
    acc_double = NULL;

    return acc_simple;
}


MaillonD* AccToAccD(Maillon* acc_simple){
    if(!acc_simple)return NULL;

    AccR* info_acc_double= (AccR*)malloc(sizeof(AccR));
    if(!info_acc_double)return NULL;

    AccD* info_acc_simple = (AccD*)acc_simple;

    copierAccessoire(&info_acc_double->accessoire,&info_acc_simple->accessoire);

    MaillonD* acc_double = (MaillonD*)info_acc_double;
    acc_double->next = acc_double;
    acc_double->prev = acc_double;

    free(info_acc_simple->accessoire.nom);
    free(acc_simple);
    acc_simple = NULL;

    return acc_double;
}


MaillonD* MaillonToMaillonD(Maillon* perso_simple){
    if(!perso_simple)return NULL;

    PersoS* info_perso_double = (PersoS*)malloc(sizeof(PersoS));
    if(!info_perso_double)return NULL;

    PersoD* info_perso = (PersoD*)perso_simple;
    copierPerso(&info_perso_double->personnage,&info_perso->personnage);
    


    MaillonD* perso_double = (MaillonD*)info_perso_double;
    perso_double->next = perso_double;
    perso_double->prev = perso_double;
    libererAccessoireNomPerso(perso_simple);
    free(perso_simple);
    perso_simple = NULL;

    return perso_double;

}


Maillon* MaillonDToMaillon(MaillonD* perso_double){
    if(!perso_double)return NULL;

    PersoD* info_perso = (PersoD*)malloc(sizeof(PersoD));
    if(!info_perso)return NULL;

    PersoS* info_perso_double = (PersoS*)perso_double;

    copierPerso(&info_perso->personnage,&info_perso_double->personnage);

    Maillon* perso_simple = (Maillon*)info_perso;
    perso_simple->next = NULL;

    libererDAccessoireNomPerso(perso_double);
    free(perso_double);
    perso_double = NULL;
    
    return perso_simple;
}


void libererList(List* liste,int liberer_perso){
    if(!*liste)return;
    do{
        List tmp = *liste;
        *liste = (*liste)->next;

        if(liberer_perso == 1){// si c'est un pero
            libererAccessoireNomPerso(tmp); // libere les accessoires et le nom du perso
        }else if (liberer_perso == 2){// si c'est une classe on libere son nom
            ClasseD* classe = (ClasseD*)tmp;
            free(classe->classe.nom);
        }else if(liberer_perso == 3){// si c'est un accessoire
            AccD* acc = (AccD*)tmp;
            free(acc->accessoire.nom);
        }
        free(tmp);

    }while(*liste);
    *liste = NULL;
}


void libererListCirc(List_circ *liste,int liberer_perso){
    if(!*liste)return;
    Maillon* debut = *liste;
    Maillon *tmp;
    List_circ lst_tmp = *liste;
    do{
        tmp = lst_tmp;
        lst_tmp = lst_tmp->next;
        if(liberer_perso == 1){
            libererAccessoireNomPerso(tmp);
        }
        free(tmp);
    }while(lst_tmp != debut);
    *liste = NULL;
}

void ajouterNbcombat(List_circ* perso_combat){
    if(!*perso_combat)return;
    Maillon* debut = *perso_combat;
    List_circ tmp = *perso_combat;
    do{
        PersoC* perso = (PersoC*)tmp;
        perso->personnage.nbcomb++;
        tmp = tmp->next;
    }while(tmp != debut);
}

void libererListeD(ListD* liste,int liberer_perso){
    if(!*liste)return;
    MaillonD* debut = *liste;
    MaillonD* tmp;
    do{
        tmp = *liste;
        *liste = (*liste)->next;
        if(liberer_perso == 1)
            libererDAccessoireNomPerso(tmp);
        if(liberer_perso == 3){
            AccR* acc = (AccR*)tmp;
            free(acc->accessoire.nom);
        }
        free(tmp);
    }while(*liste != debut);
    *liste = NULL;
}

void libererNomAcc(Type_Liste*liste){
    for(int i = 0;i<LEN_NOM_ACC;i++){
        if(*(liste->nom_acc+i))
            free(*(liste->nom_acc+i));
    }
}

void libererJoueur(Joueur* joueur){
    if(!joueur)return;
    free(joueur->nom);
    free(joueur);
}


void LibererTypeListe(Type_Liste* liste){
    
    libererList(&liste->classe_dispo,2);

    libererList(&liste->personnage_dispo,1);

    libererList(&liste->donjon,0);

    libererListCirc(&liste->perso_combat,1); 

    libererList(&liste->accessoire_dispo,3);

    libererListeD(&liste->perso_sanitarium,1);

    libererListeD(&liste->perso_taverne,1);
    libererListeD(&liste->accessoire_roulotte,3);

    libererNomAcc(liste);
    free(liste->nombre);
    free(liste);
}


char* strdup(const char* s) {
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char* copy = malloc(len);
    if (copy) {
        memcpy(copy, s, len);
    }
    return copy;
}


int mainMaster(Type_Liste *liste,Param param){
    const char* nom_acc[LEN_NOM_ACC] = {  
                        "Sigil_de_Eldritch", "Idole_Maudite", "Talisman_de_la_Lumière", "Amulette_de_la_Nuit", 
                        "Médaillon_de_la_Mort", "Pendentif_de_la_Vie", "Anneau_de_la_Bravoure", "Charme_de_la_Peur", 
                        "Totem_de_la_Bête", "Relique_de_Ancien", "Grimoire_de_la_Sagesse", "Sceau_de_la_Puissance", 
                        "Orbe_de_Ombre", "Cristal_de_Aube", "Pierre_de_Esprit", "Fétiche_de_la_Folie", 
                        "Icône_de_la_Foi", "Symbole_de_la_Terreur", "Emblème_de_la_Gloire", "Insigne_de_la_Honte", 
                        "Médaillon_de_Infamie", "Pendentif_de_la_Vertu", "Talisman_de_la_Chance", "Amulette_de_la_Malédiction", 
                        "Anneau_de_la_Vengeance", "Charme_de_la_Protection", "Totem_de_la_Fureur", "Relique_de_la_Tranquillité", 
                        "Grimoire_de_la_Connaissance", "Sceau_de_la_Destruction", "Orbe_de_la_Sérénité", "Cristal_de_la_Rage", 
                        "Pierre_de_la_Résilience", "Fétiche_de_la_Douleur", "Icône_de_la_Rédemption", "Symbole_de_la_Déchéance", 
                        "Emblème_de_la_Victoire", "Insigne_de_la_Défaite", "Médaillon_de_Agonie", "Pendentif_de_la_Joie", 
                        "Talisman_de_la_Peur", "Amulette_de_la_Force", "Anneau_de_la_Sagesse", "Charme_de_la_Tromperie", 
                        "Totem_de_la_Vérité", "Relique_de_la_Tromperie", "Grimoire_de_la_Puissance", "Sceau_de_la_Lumière", 
                        "Orbe_de_la_Nuit", "Cristal_de_la_Mort"
                    };
    for(int i = 0;i<LEN_NOM_ACC;i++){
        char* nom =  strdup(nom_acc[i]);
        liste->nom_acc[i] = nom;
    }

    Maillon *brigand         = creerEnnemis("brigand",0,8,3,50,10,liste->nombre);
    Maillon *squelette       = creerEnnemis("squelette",1,10,4,60,20,liste->nombre);
    Maillon *goule           = creerEnnemis("goule",2,11,1,70,10,liste->nombre);
    Maillon *gargouille      = creerEnnemis("gargouille",3,12,4,80,15,liste->nombre);
    Maillon *bagarreur       = creerEnnemis("bagarreur",4,15,3,80,20,liste->nombre);
    Maillon *brigand_raideur = creerEnnemis("brigand_raideur",5,10,4,80,30,liste->nombre);
    Maillon *fou             = creerEnnemis("fou",6,16,12,80,40,liste->nombre);
    Maillon *ancetre         = creerEnnemis("ancetre",7,20,5,70,50,liste->nombre);
    Maillon *collectionneur  = creerEnnemis("collectionneur",8,10,9,100,20,liste->nombre);
    Maillon *fanatique       = creerEnnemis("fanatique",9,20,20,110,40,liste->nombre);

    ajoutFin(&liste->donjon,brigand);
    ajoutFin(&liste->donjon,squelette);
    ajoutFin(&liste->donjon,goule);
    ajoutFin(&liste->donjon,gargouille);
    ajoutFin(&liste->donjon,bagarreur);
    ajoutFin(&liste->donjon,brigand_raideur);
    ajoutFin(&liste->donjon,fou);
    ajoutFin(&liste->donjon,ancetre);
    ajoutFin(&liste->donjon,collectionneur);
    ajoutFin(&liste->donjon,fanatique);


    char* nom_furie = (char*)malloc(sizeof(char)*50);
    char* nom_vestale = (char*)malloc(sizeof(char)*50);
    char* nom_chasseur_prime = (char*)malloc(sizeof(char)*50);
    char* nom_chien = (char*)malloc(sizeof(char)*50);
    char* nom_medecin_peste = (char*)malloc(sizeof(char)*50);
    char* nom_evade = (char*)malloc(sizeof(char)*50);
    if(!nom_furie || !nom_vestale || !nom_chasseur_prime || !nom_chien || 
        !nom_medecin_peste  || !nom_evade)return -1;
    strcpy(nom_furie,"furie");
    strcpy(nom_vestale,"vestale");
    strcpy(nom_chasseur_prime,"chasseur_prime");
    strcpy(nom_chien,"chien");
    strcpy(nom_medecin_peste,"medecin_peste");
    strcpy(nom_evade,"evade");

    Maillon *furie           = creerClasse(0,nom_furie,13,3,50,1,liste->nombre);
    Maillon *vestale         = creerClasse(1,nom_vestale,3,3,50,3,liste->nombre);
    Maillon *chasseur_prime  = creerClasse(2,nom_chasseur_prime,7,3,60,3,liste->nombre);
    Maillon *chien           = creerClasse(3,nom_chien,10,6,100,5,liste->nombre);
    Maillon *medecin_peste   = creerClasse(4,nom_medecin_peste,5,3,80,5,liste->nombre);
    Maillon *evade           = creerClasse(5,nom_evade,10,3,50,5,liste->nombre);
    if (!furie || !vestale || !chasseur_prime ||!chien|| !medecin_peste ||
        !evade)return -1;
    

    ajoutFin(&liste->classe_dispo,furie);
    ajoutFin(&liste->classe_dispo,vestale);
    ajoutFin(&liste->classe_dispo,chasseur_prime);
    ajoutFin(&liste->classe_dispo,chien);
    ajoutFin(&liste->classe_dispo,medecin_peste);
    ajoutFin(&liste->classe_dispo,evade);
    if(*param.fichier_chargement == '\0'){
        //alloue la place pour le nom comme ca des que je crée un nv_perso il s'affiche correctement
        char* nom_boudicca  = (char*)malloc(sizeof(char)*50);
        char* nom_junia     = (char*)malloc(sizeof(char)*50);
        char* nom_william   = (char*)malloc(sizeof(char)*50);
        char* nom_tardif    = (char*)malloc(sizeof(char)*50);
        char* nom_Alhazred  = (char*)malloc(sizeof(char)*50);

        if(!nom_boudicca || !nom_junia || !nom_william || !nom_tardif || !nom_Alhazred)return -1;
        strcpy(nom_boudicca,"boudicca");    
        strcpy(nom_junia,"junia");
        strcpy(nom_william,"william");
        strcpy(nom_tardif,"tardif");
        strcpy(nom_Alhazred,"Alhazred");


        Maillon *budicca  = creerPerso(((ClasseD*)furie)->classe,nom_boudicca,0,liste->nombre);
        Maillon *junia    = creerPerso(((ClasseD*)evade)->classe,nom_junia,1,liste->nombre);
        Maillon * william = creerPerso(((ClasseD*)chasseur_prime)->classe,nom_william,2,liste->nombre);
        Maillon *tardif   = creerPerso(((ClasseD*)chien)->classe,nom_tardif,3,liste->nombre);
        Maillon *Alhazred = creerPerso(((ClasseD*)medecin_peste)->classe,nom_Alhazred,4,liste->nombre);


        if(!budicca || !junia|| !william|| !tardif || !Alhazred)return -1;
        free(nom_boudicca);
        free(nom_junia);
        free(nom_william);
        free(nom_tardif);
        free(nom_Alhazred);
        ajoutFin(&liste->personnage_dispo,budicca);
        ajoutFin(&liste->personnage_dispo,junia);
        ajoutFin(&liste->personnage_dispo,william);

        ajoutFin(&liste->personnage_dispo,tardif);

        ajoutFin(&liste->personnage_dispo,Alhazred);
        liste->nombre->perso_dispo = liste->nombre->perso_total;

        char* nom_pendentif = (char*)malloc(sizeof(char)*50);
        char* nom_calice    = (char*)malloc(sizeof(char)*50);
        char* nom_anneau    = (char*)malloc(sizeof(char)*50);
        char* nom_manteau   = (char*)malloc(sizeof(char)*50); 

        if(!nom_pendentif || !nom_calice ||!nom_anneau ||!nom_manteau )return -1;
        strcpy(nom_pendentif,"pendentif_tranchant");
        strcpy(nom_calice,"calice_de_jeunesse");
        strcpy(nom_anneau,"Anneau_de_concentration");
        strcpy(nom_manteau,"Manteau_solaire");


        MaillonD* pendentif_tranchant     = creerAccessoire(nom_pendentif,0,2,5,2,3,1,0);
        MaillonD* calice_de_jeunesse      = creerAccessoire(nom_calice,1,55,13,10,16,0,5);
        MaillonD* Anneau_de_concentration = creerAccessoire(nom_anneau,2,5,7,0,5,0,10);
        MaillonD* Manteau_solaire         = creerAccessoire(nom_manteau,3,89,17,5,18,5,0);
        free(nom_pendentif);
        free(nom_calice);
        free(nom_anneau);
        free(nom_manteau);
        if(!pendentif_tranchant || !calice_de_jeunesse ||!Anneau_de_concentration || !Manteau_solaire)return -1;
        ajoutDebutDcirc(&liste->accessoire_roulotte,pendentif_tranchant);
        ajoutDebutDcirc(&liste->accessoire_roulotte,calice_de_jeunesse);
        ajoutDebutDcirc(&liste->accessoire_roulotte,Anneau_de_concentration);
        ajoutDebutDcirc(&liste->accessoire_roulotte,Manteau_solaire);
        liste->nombre->accessoire_roulotte = 4;
        liste->nombre->accessoire_total = 4; 
    }
    
   
    
    


    return 0;
}
