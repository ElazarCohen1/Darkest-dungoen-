#include "donnee.h"
#include "master.h"
#include <stdio.h>
#include <stdlib.h>

void afficherPerso(Perso perso){
    printf("%-3d | %-12s | %-16s | %-3d | %-3d | %4d/ %-4d | %-4d | %-3d | %-6d |\n",
       perso.num,        
       perso.nom,        
       perso.classe.nom, 
       perso.att,        
       perso.def,       
       perso.HP,
       perso.HPmax,         
       perso.rest,       
       perso.str,       
       perso.nbcomb);
}


void afficherAccessoire(Acc acc){
    printf("%-3d | %-25s | %3d or | %-8d | %-8d | %-7d | %-9d | %-7d |\n",
       acc.num,        
       acc.nom,   
       acc.prix,     
       acc.attbonus, 
       acc.defbonus,        
       acc.HPbonus,       
       acc.restbonus,         
       acc.strred);
}


void afficherAccPersoC(List_circ perso_c){  
    if(!perso_c)
        return;
    
    Maillon* debut = perso_c;
    do{
        PersoC* perso = (PersoC*)perso_c;
        printf("les accessoires de %s sont :\n",perso->personnage.nom);
        printf("%-3s | %-25s | %-6s | %-8s | %-8s | %-7s | %-9s | %-7s |\n",
        "Num",
        "Nom",
        "prix",
        "attbonus",
        "defbonus",
        "HPbonus",
        "restbonus",
        "strred");
        printf("-----------------------------------------------------------------------------------------------|\n");

        if(perso->personnage.acc1){
            afficherAccessoire(perso->personnage.acc1->accessoire);
        }
        if(perso->personnage.acc2){
            afficherAccessoire(perso->personnage.acc2->accessoire);
        }
        perso_c = perso_c->next;
        printf("\n");
    }while(perso_c != debut);
}

void afficherPersoD(List liste){

    if(!liste)return;

    printf("%-3s | %-12s | %-16s | %-3s | %-3s | %4s/%-4s | %-4s | %-3s | %-6s |\n",
        "Num",
        "Nom",
        "Classe",
        "att",
        "def",
        "HP",
        "HPmax",
        "rest",
        "str",
        "nbcomb");
    printf("-------------------------------------------------------------------------------------|\n");

    for(; liste; liste = liste->next){

        PersoD* perso = (PersoD*)liste;
        afficherPerso(perso->personnage);
        
    }
    printf("-------------------------------------------------------------------------------------|\n");

}


void afficherClasseD(List liste){
    printf("%-4s | %-16s | %-4s | %-4s | %-5s | %-4s |\n",
        "num",
        "classes",
        "att",
        "def",
        "HPmax",
        "rest");
    printf("-----------------------------------------------------|\n");

    for (; liste; liste = liste->next) {
        ClasseD *lst_classe = (ClasseD *)liste;

        printf("%-4d | %-16s | %-4d | %-4d | %-5d | %-4d |\n",
            lst_classe->classe.num,
            lst_classe->classe.nom,    
            lst_classe->classe.att,    
            lst_classe->classe.def,    
            lst_classe->classe.HPmax,  
            lst_classe->classe.rest);  
    }
    printf("-----------------------------------------------------|\n");

        
}


void afficherPersoC(List_circ perso_c){
    if (!perso_c) {
        printf("La liste des personnages est vide.\n");
        return;
    }
    Maillon* debut = perso_c;
    printf("%-3s | %-12s | %-10s | %-3s | %-3s | %3s/%3s  | %-4s | %-3s | %-6s|\n",
        "Num",
        "Nom",
        "Classe",
        "att",
        "def",
        "HP",
        "HPmax",
        "rest",
        "str",
        "nbcomb");
    printf("------------------------------------------------------------------------------|\n");

    do{
        PersoC* perso = (PersoC*)perso_c;
        afficherPerso(perso->personnage);
        perso_c = perso_c->next;

    }while(perso_c != debut);
    printf("------------------------------------------------------------------------------|\n");

}


void afficherAccDAscii(List liste){
    if(!liste){
        printf("il n'y a aucun accessoire\n");
        return;
    }
    printf("%-3s | %-25s | %-6s | %-8s | %-8s | %-7s | %-9s | %-7s |\n",
        "Num",
        "Nom",
        "prix",
        "attbonus",
        "defbonus",
        "HPbonus",
        "restbonus",
        "strred");
    printf("-----------------------------------------------------------------------------------------------|\n");

    for(;liste; liste = liste->next){
        AccD* acc = (AccD*)liste;
        afficherAccessoire(acc->accessoire);
        
    }
    printf("-----------------------------------------------------------------------------------------------|\n");
}


void afficherAccRoulotteAscii(ListD_circ acc_roulotte){
    if(!acc_roulotte){
        printf("il n'y a aucun accessoire dans la roulotte\n");
        return;
    }
    MaillonD* debut = acc_roulotte;
    ListD_circ tmp = acc_roulotte;
    printf("%-3s | %-25s | %-6s | %-8s | %-8s | %-7s | %-9s | %-7s |\n",
        "Num",
        "Nom",
        "prix",
        "attbonus",
        "defbonus",
        "HPbonus",
        "restbonus",
        "strred");
    printf("-----------------------------------------------------------------------------------------------|\n");
    
    do{
        AccR* lst_acc = (AccR*)tmp;

        afficherAccessoire(lst_acc->accessoire);

        tmp = tmp->next;
    }while(tmp != debut);
    printf("-----------------------------------------------------------------------------------------------|\n");


}

void choisirCombattantAscii(Type_Liste *liste){
    int choix_tmp;
    int nb_combattant;
    int nb_combattant_tmp; 

    do{
        printf("combien voulez vous de combattants ? ");
        if (scanf("%d",&nb_combattant_tmp) != 1){
            printf("vous n'avez pas entre un chiffre ");
            while (getchar() != '\n');
            continue;
        }
        if (liste->nombre->perso_dispo < 2){
            printf("vous n'avez pas assez de combattants\n");
            continue;
        }
        if(nb_combattant_tmp > 0 && liste->nombre->perso_dispo >= 2 && nb_combattant_tmp <= 2)
            break;
        else
            printf("veuillez choisir un nombre de combattants valides (on ne peut pas choisir plus de 2 persos)\n");
    }while(1);

    nb_combattant = nb_combattant_tmp;
    liste->nombre->nb_combattant = nb_combattant;
    
    // le choix des combattants
    for(int i = 0; i < nb_combattant; i++){
        do{
            printf("choix du combattant %d :",i);
            if (scanf("%d",&choix_tmp)!= 1){
                printf("vous n'avez pas entre un chiffre ");
                while (getchar() != '\n');
                continue;
            }
            if (recherchePerso(liste->personnage_dispo,choix_tmp) == 1)
                break;
            else{
                printf("personnage indisponible\n");
            }
        }while(1);
       

        Maillon* maillon = extraitPerso(&liste->personnage_dispo,choix_tmp);
        ajoutFinCirc(&liste->perso_combat,maillon);

    }
}


void affichagePersoChoisi(List_circ perso_c){
    Maillon* debut = perso_c;
    do{

        PersoC* perso = (PersoC*)perso_c;
        printf("%s : %d HP %d str \n",perso->personnage.nom,perso->personnage.HP,perso->personnage.str);
        perso_c = perso_c->next;
    }while(perso_c != debut);
}


void choisirAccessoireAscii(Type_Liste*liste){
    if(!liste->accessoire_dispo){
        printf("vous n'avez aucun accessoire...\n");
        return;
    }
    int choix_combattant = 0;
    Maillon* debut = liste->perso_combat;
    List_circ acc_dispo = liste->accessoire_dispo;
    afficherAccDAscii(acc_dispo);
    afficherPersoC(liste->perso_combat);
    do{
        AccD* lst_acc = (AccD*)acc_dispo;
        List_circ perso_combat = liste->perso_combat;
        acc_dispo = acc_dispo->next;

        if(verrifAccPersoCRempli(perso_combat) == 1){
            printf("les accessoires sont deja rempli\n");
            return;
        }

        printf("A qui voulez vous attribuer l'accessoire %d (une lettre/mauvais chiffre pour personne): ",lst_acc->accessoire.num);
        if(scanf("%d",&choix_combattant)!= 1){
            while(getchar() != '\n');
            continue;
        }

        if(recherchePersoCirc(perso_combat,choix_combattant) == 1){
            Maillon* maillon = extraitAccD(&liste->accessoire_dispo,lst_acc->accessoire.num);
            MaillonAcc* acc = (MaillonAcc*)maillon;
            do{
                PersoC* perso = (PersoC*)perso_combat;

                if(perso->personnage.num == choix_combattant){
                    if(!perso->personnage.acc1){
                        perso->personnage.acc1 = acc;
                    }else if(!perso->personnage.acc2){
                        perso->personnage.acc2 = acc;
                    }else{
                        printf("les accessoires de ce perso sont deja rempli\n");
                        ajoutDebut(&liste->accessoire_dispo,maillon);
                        choisirAccessoireAscii(liste);
                    }

                    perso->personnage.HP += acc->accessoire.HPbonus;
                    perso->personnage.HPmax += acc->accessoire.HPbonus;
                }
                perso_combat = perso_combat->next;
            }while(perso_combat != debut);
        }

    
    }while(acc_dispo);
    
}


TypeAction demandeActionAscii(Perso p){
    char choix_tmp;
    do{
        printf("Action de %s (A,D,R,Q):",p.nom);
        scanf(" %c",&choix_tmp);

        switch(choix_tmp){
            case 'A':
                return  ATTAQUE;
            case 'D':
                return DEFENSE;
            case 'R':
                return REST;
            case 'Q':
                return QUITTE;
            default:
                printf("mauvaise entrée je ne peux rien faire\n");
                choix_tmp = 0;
                break;
        }
    }while(choix_tmp == 0);
    return -1;
}


int affichageDebutAscii(List perso_dispo, List classe_dispo){
    afficherClasseD(classe_dispo);

    printf("\n");
    printf("voici les personnage dispo au debut\n");
    afficherPersoD(perso_dispo);  



    return 0;
}