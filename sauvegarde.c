#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "donnee.h"
#include "master.h"



void ecrireJoueur(Joueur joueur,FILE* fichier){
    if(!joueur.nom || !fichier)return;
    fprintf(fichier,"%d %s %d %d\n",
            0,
            joueur.nom,
            joueur.or,
            joueur.niveau
        );
}

void ecrireAcc(Acc acc,FILE* fichier,int numero_lst){
    fprintf(fichier,"%d %d %s %d %d %d %d %d %d\n",
            numero_lst,
            acc.num,
            acc.nom,
            acc.prix,
            acc.attbonus,
            acc.defbonus,
            acc.HPbonus,
            acc.restbonus,
            acc.strred
    );      
}

void ecrireAccD(List acc_dispo,FILE*fichier){
    if(!acc_dispo)return;
    for(;acc_dispo;acc_dispo = acc_dispo->next){
        AccD* acc = (AccD*)acc_dispo;
        ecrireAcc(acc->accessoire,fichier,1);
    }
}

void ecrireAccR(ListD_circ acc_roulotte,FILE* fichier){
    if(!acc_roulotte)return;
    MaillonD* debut = acc_roulotte;
    do{
        AccR* lst_acc = (AccR*)acc_roulotte;
        ecrireAcc(lst_acc->accessoire,fichier,2);
        acc_roulotte = acc_roulotte->next;
    }while(acc_roulotte != debut);
}



void ecrirePerso(Type_Liste*liste,Perso perso,FILE*fichier,int numero_lst){
    fprintf(fichier,"%d %s %d %d %d %d %d %d %d %d %d %d %d %d\n",
                numero_lst,
                perso.nom,
                perso.num,
                perso.classe.num,
                perso.att,
                perso.def,
                perso.HP,
                perso.HPmax,
                perso.rest,
                perso.str,
                perso.nbcomb,
                perso.activer_defense,
                perso.acc1?perso.acc1->accessoire.num:-1,
                perso.acc2?perso.acc2->accessoire.num:-1
        );

        if(perso.acc1)
            ajoutDebut(&liste->accessoire_dispo,(Maillon*)perso.acc1);
        if(perso.acc2)
            ajoutDebut(&liste->accessoire_dispo,(Maillon*)perso.acc2);

}


void ecrirePersoD(Type_Liste* liste,FILE* fichier){
    List perso_dispo = liste->personnage_dispo;
    if(!perso_dispo)return;

    for(;perso_dispo; perso_dispo = perso_dispo->next){
        PersoD* lst_perso = (PersoD*)perso_dispo;
        ecrirePerso(liste,lst_perso->personnage,fichier,3);
    }
   
}


void ecrirePersoC(Type_Liste* liste,FILE* fichier){
    if(!liste->perso_combat)return;
    List_circ perso_combat = liste->perso_combat;
    if(!perso_combat)return;
    Maillon* debut = perso_combat;
    do{
        PersoC* lst_perso = (PersoC*)perso_combat;
        ecrirePerso(liste,lst_perso->personnage,fichier,4);
        perso_combat = perso_combat->next;
    }while(perso_combat != debut);
}


void ecrirePersoST(Type_Liste* liste,FILE* fichier,int sanni_taverne){
    ListD_circ perso_sanni = sanni_taverne == 0?liste->perso_sanitarium:liste->perso_taverne;
    if(!perso_sanni)return;
    MaillonD* debut = perso_sanni;
    do{
        PersoS* perso = (PersoS*)perso_sanni;
        if(sanni_taverne == 0)
            ecrirePerso(liste,perso->personnage,fichier,5);
        else
            ecrirePerso(liste,perso->personnage,fichier,6);
        perso_sanni = perso_sanni->next;

    }while(perso_sanni != debut);
}


void ecrireNombre(Nb* nombre,FILE* fichier){
    if(!nombre)return;
    fprintf(fichier,"%d %d %d %d %d %d %d %d %d %d %d\n",
        7,
        nombre->perso_total,
        nombre->perso_dispo,
        nombre->nb_combattant,
        nombre->nb_classe,
        nombre->accessoire_dispo,
        nombre->accessoire_roulotte,
        nombre->nb_ennemis,
        nombre->perso_sanni,
        nombre->perso_taverne,
        nombre->accessoire_total
    );
}


int sauvegarderPartie(Type_Liste* liste,Joueur joueur,FILE** fichier,const char* chemin){
    *fichier = fopen(chemin,"w");
    if(!*fichier || !liste)return -1;
    ecrireJoueur(joueur,*fichier);
    ecrirePersoD(liste,*fichier);
    ecrirePersoC(liste,*fichier);
    ecrirePersoST(liste,*fichier,0);
    ecrirePersoST(liste,*fichier,1);
    ecrireAccD(liste->accessoire_dispo,*fichier);
    ecrireAccR(liste->accessoire_roulotte,*fichier);
    ecrireNombre(liste->nombre,*fichier);
    fclose(*fichier);
    return 0;
}


void lireJoueur(Joueur **joueur,char*ligne){
    int num;
    *joueur = (Joueur*)malloc(sizeof(Joueur));
    (*joueur)->nom = (char*)malloc(sizeof(char)*50);
    if(!*joueur || !(*joueur)->nom)return;
    sscanf(ligne,"%d %s %d %d\n",
            &num,
            (*joueur)->nom,
            &(*joueur)->or,
            &(*joueur)->niveau
        );
}


Maillon* lireAcc(char*ligne){
    int num_lst;
    MaillonAcc* acc = (MaillonAcc*)malloc(sizeof(MaillonAcc));
    acc->accessoire.nom = (char*)malloc(sizeof(char)*50);
    if(!acc || !acc->accessoire.nom)return NULL;
    sscanf(ligne,"%d %d %s %d %d %d %d %d %d\n",
            &num_lst,
            &acc->accessoire.num,
            acc->accessoire.nom,
            &acc->accessoire.prix,
            &acc->accessoire.attbonus,
            &acc->accessoire.defbonus,
            &acc->accessoire.HPbonus,
            &acc->accessoire.restbonus,
            &acc->accessoire.strred
        );
    Maillon* maillon = (Maillon*)acc;
    maillon->next = NULL;
    return maillon;
}


Maillon* lirePerso(Type_Liste* liste,char*ligne){
    int num_lst;
    PersoD* perso_general = (PersoD*)malloc(sizeof(PersoD));
    perso_general->personnage.nom = (char*)malloc(sizeof(char)*50);
    if(!perso_general || !perso_general->personnage.nom)return NULL;
    int num_classe;
    int num_acc1;
    int num_acc2;
    List classe_tmp = liste->classe_dispo;
    List acc_tmp = liste->accessoire_dispo;
    sscanf(ligne,"%d %s %d %d %d %d %d %d %d %d %d %d %d %d\n",
                &num_lst,
                perso_general->personnage.nom,
                &perso_general->personnage.num,
                &num_classe,
                &perso_general->personnage.att,
                &perso_general->personnage.def,
                &perso_general->personnage.HP,
                &perso_general->personnage.HPmax,
                &perso_general->personnage.rest,
                &perso_general->personnage.str,
                &perso_general->personnage.nbcomb,
                &perso_general->personnage.activer_defense,
                &num_acc1,
                &num_acc2
        );

    for(;classe_tmp;classe_tmp = classe_tmp->next){

        ClasseD* classe = (ClasseD*)classe_tmp;
        if(classe->classe.num == num_classe){
            perso_general->personnage.classe = classe->classe;
            break;
        }
    }
    if(num_acc1 == -1){
        perso_general->personnage.acc1 = NULL;
    }
    if(num_acc2 == -1){
        perso_general->personnage.acc2 = NULL;
    }else{
        for(;acc_tmp;acc_tmp= acc_tmp->next){
            AccD* acc = (AccD*)acc_tmp;
            if(acc->accessoire.num == num_acc1){
                Maillon* maillon = extraitAccD(&liste->accessoire_dispo,num_acc1);
                perso_general->personnage.acc1 = (MaillonAcc*)maillon;
            }
            if(acc->accessoire.num == num_acc2){
                Maillon* maillon = extraitAccD(&liste->accessoire_dispo,num_acc2);
                perso_general->personnage.acc2 = (MaillonAcc*)maillon;
            }
        }
    }
    Maillon* maillon = (Maillon*)perso_general;
    maillon->next = NULL;
    return maillon;

}


void lireNombre(Nb* nombre,char*ligne){
    int num_lst;
    sscanf(ligne,"%d %d %d %d %d %d %d %d %d %d %d\n",
        &num_lst,
        &nombre->perso_total,
        &nombre->perso_dispo,
        &nombre->nb_combattant,
        &nombre->nb_classe,
        &nombre->accessoire_dispo,
        &nombre->accessoire_roulotte,
        &nombre->nb_ennemis,
        &nombre->perso_sanni,
        &nombre->perso_taverne,
        &nombre->accessoire_total
    );
}


int lancerSauvegarde(Type_Liste* liste,FILE**fichier,const char* chemin,Joueur** joueur){
    *fichier = fopen(chemin,"r");
    if(!*fichier )return -1;
    int c = fgetc(*fichier);
    if( c == EOF)return -1;
    ungetc(c,*fichier);
    char ligne[255];
    while(fgets(ligne,255,*fichier) != NULL){
        switch(ligne[0]){
            case '0':
                lireJoueur(joueur,ligne);
                break;
            case '1':{
                Maillon* acc = lireAcc(ligne);
                ajoutDebut(&liste->accessoire_dispo,acc);
                break;
            }
               
            case '2':{
                Maillon* acc = lireAcc(ligne);
                MaillonD* acc_roulotte = AccToAccD(acc);
                ajoutDebutDcirc(&liste->accessoire_roulotte,acc_roulotte);
                break;
            }
                
            case '3':{
                Maillon* perso = lirePerso(liste,ligne);
                ajoutDebut(&liste->personnage_dispo,perso);
                break;
            }
                
            case '4':{
                Maillon* perso = lirePerso(liste,ligne);
                ajoutFinCirc(&liste->perso_combat,perso);
                break;
            }
                
            case '5':{
                Maillon* perso = lirePerso(liste,ligne);
                MaillonD* perso_sanni = MaillonToMaillonD(perso);
                ajoutDebutDcirc(&liste->perso_sanitarium,perso_sanni);
                break;
            }
                
            case '6':{
                Maillon* perso = lirePerso(liste,ligne);
                MaillonD* perso_taverne = MaillonToMaillonD(perso);
                ajoutDebutDcirc(&liste->perso_taverne,perso_taverne);
                break;
            }
                
            case '7':
                lireNombre(liste->nombre,ligne);
                break;
        }
    }    
    fclose(*fichier);
    return 0;
}




