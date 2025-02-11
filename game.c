#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "donnee.h"
#include "master.h"
#include "ascii.h"
#include "graphics.h"
#include <MLV/MLV_all.h>
#include "sauvegarde.h"



void gererPersoMort(List_circ* liste_perso,Nb* nombre){
    Maillon* debut = *liste_perso;
    List_circ tmp = *liste_perso;
    if(!(*liste_perso))return;
    do{
        PersoC* perso = (PersoC*)tmp;
        tmp = (tmp)->next;

        if(perso->personnage.HP <= 0){
            Maillon* cel = extraireListCirc(liste_perso,perso->personnage);
            PersoC* p = (PersoC*)cel;
            printf("%s a atteint les profondeur du dongeon, mais nous entendrons ses souffrance pour l'eternité\n\n\n",p->personnage.nom);

            libererAccessoireNomPerso(cel);
            free(cel);// on supprime totalement le perso des qu'il est mort
            nombre->nb_combattant -= 1;
            nombre->perso_total -= 1;
            if(!*liste_perso)break;
            if(cel == debut){
                debut = *liste_perso;
            }
        }
        
    }while(tmp != debut);
    
}


void gererAttaque(Perso *perso,Ennemis *ennemis,Attaquant attaquant){
    // nombre aleatoire pour roll
    int strred=0;
    int accbonus = 0;
    float tab_chiffre[LEN_ROLL];
    float chiffre = 0.80;

    for (int i = 0;i< LEN_ROLL;i++ ){
        *(tab_chiffre+i) = chiffre;
        chiffre+= 0.01;
    }
    float attaque_contre_ennemis;
    float attaque_contre_joueur;

   

    if (attaquant == PERSONNAGE){
        if(perso->acc1)
            accbonus += perso->acc1->accessoire.attbonus;
        if(perso->acc2)
            accbonus += perso->acc2->accessoire.attbonus;

        int atttotal = perso->att + accbonus;
        
        if((atttotal - ennemis->defenn) > 0){
            float roll = tab_chiffre[rand()%LEN_ROLL];
            attaque_contre_ennemis = (atttotal - ennemis->defenn)*roll;

        }else{

            attaque_contre_ennemis = 1;
        }

        ennemis->HPenn -= attaque_contre_ennemis;
        printf("dommage a l'ennemis %s : %.2f HP , %d HP restant \n",ennemis->nom,attaque_contre_ennemis,ennemis->HPenn);
    
    }else{
        int type_attaque = rand()%2;
        if(type_attaque == 0){
            float roll = tab_chiffre[rand()%LEN_ROLL]; 
            if(perso->activer_defense == 1){
                attaque_contre_joueur = (ennemis->atten - (perso->def+ (perso->def*0.1)))*roll;
            }else
                attaque_contre_joueur = (ennemis->atten - perso->def)*roll;

            perso->HP -= attaque_contre_joueur;

        
        }else{
            if (perso->acc1)
                strred += perso->acc1->accessoire.strred;
            if (perso->acc2)
                strred += perso->acc2->accessoire.strred;
            int attstresse = ((ennemis->attstrenn - strred) >= 100)?100:(ennemis->attstrenn - strred)<0?0:(ennemis->attstrenn - strred);
            perso->str = attstresse;
            printf("le joueur a prit une att de str de %.2d , il a %d  de stresse\n",((ennemis->attstrenn - strred) >= 100)?100:(ennemis->attstrenn - strred)<0?0:(ennemis->attstrenn - strred),perso->str);

        }
        
    }
}


void gererRest(List_circ* perso_combat,Perso* perso,AFFICHAGE aff){
    int perso_choisi = 0;
    int accbonus = 0;
    int nv_hp;
    Maillon* debut = *perso_combat;
    List_circ tmp = *perso_combat;
    if(aff == ASCII){
        do{
            afficherPersoC(*perso_combat);
            printf("quelle joueur voulez vous guerir (num) ? ");

            if(scanf("%d",&perso_choisi)!=1){
                printf("mauvaise entree\n");
                while(getchar() != '\n');
                return;
            }
            if(recherchePersoCirc(*perso_combat,perso_choisi) == 1)break;
            else{
                printf("je ne le trouve pas dans la liste\n");
                while(getchar() != '\n');
                continue;
            }
        }while(1);
        
    }else{
        perso_choisi = gererRestGraphics(perso_combat);
    }
    do{
        PersoC* p = (PersoC*)tmp;
        if (perso->acc1)
            accbonus += perso->acc1->accessoire.restbonus;
        if (perso->acc2)
            accbonus += perso->acc2->accessoire.restbonus;
        
        int rest = perso->rest + accbonus;
        if(p->personnage.num == perso_choisi){
            printf("l'ancien  HP du personnage: %d\n\n",p->personnage.HP);

            nv_hp = (p->personnage.HP + rest >= p->personnage.classe.HPmax)?(p->personnage.classe.HPmax): p->personnage.HP + rest;
            p->personnage.HP  = nv_hp;
            printf("le nouveau HP du personnage: %d\n\n",p->personnage.HP);
            return;
        }
        tmp = tmp->next;
    }while(tmp != debut);
    gererRest(perso_combat,perso,aff);


}


void gererDefense(Perso* perso){
    perso->activer_defense = 1;
}


void attaqueAleatoirePerso(Ennemis * ennemis,List_circ* perso_combat,Nb* nombre){
    int perso_attaque_aleatoire = rand()% nombre->nb_combattant;
    Maillon * debut = *perso_combat;
    List_circ tmp = *perso_combat;
    int i = 0;
    do{
        PersoC* perso = (PersoC*)tmp;
        if(i == perso_attaque_aleatoire){
            gererAttaque(&perso->personnage,ennemis,1);
            printf("l'ennemis %s  a attaqué le perso %s : il lui reste : %d \n",ennemis->nom,perso->personnage.nom,perso->personnage.HP);
        }
        tmp = tmp->next;
        i++;

    }while(tmp != debut);
    
}


void tourEnnemis(Ennemis* ennemis,List_circ* perso_combat,Nb* nombre){

    attaqueAleatoirePerso(ennemis,perso_combat,nombre);
    gererPersoMort(perso_combat,nombre);
}


TypeAction tourPerso(List_circ* perso_combat,Ennemis* ennemis,AFFICHAGE aff){
    List_circ tmp = *perso_combat;
    Maillon* debut = *perso_combat;
    TypeAction action;

    do{
        if(aff == GRAPHICS){
            MLV_clear_window(MLV_COLOR_BLACK);
            afficherCombat(*perso_combat,*ennemis);
        }
        PersoC* perso_c = (PersoC*)tmp;
        if(perso_c->personnage.str == 100){
            
            printf("tu ne peu plus jouer %s\n",perso_c->personnage.nom);
            tmp = tmp->next;
            continue;
        }
        if(aff == ASCII)
            action = demandeActionAscii(perso_c->personnage);
        else 
            action  = ActionGraphique(perso_c->personnage);

        switch(action){
            case QUITTE:
                return QUITTE;
            case ATTAQUE:
                if(aff == GRAPHICS){
                    MLV_draw_rectangle(198,518,50,50,MLV_COLOR_DARK_GRAY);
                    MLV_actualise_window();
                }
                gererAttaque(&perso_c->personnage,ennemis,0);
                break;

            case DEFENSE:
                if(aff == GRAPHICS){
                    MLV_draw_rectangle(273,518,50,50,MLV_COLOR_DARK_GRAY);
                    MLV_actualise_window();
                    }
                gererDefense(&perso_c->personnage);
                break;

            case REST:
                if(aff == GRAPHICS){
                    MLV_draw_rectangle(352,518,50,50,MLV_COLOR_DARK_GRAY);
                    MLV_actualise_window();
                }

                gererRest(perso_combat,&perso_c->personnage,aff);
        
        }
        tmp = tmp->next;


    }while(tmp != debut && ennemis->HPenn > 0);
    return -1;
}


TypeAction niveau(List_circ *perso_combat,Ennemis *ennemis,Nb *nombre,AFFICHAGE aff){
    if(!*perso_combat || !ennemis)return -1;
    Attaquant attaquant = rand()%2;
    while(nombre->nb_combattant > 0  && ennemis->HPenn > 0){
        if (attaquant == 1)
            tourEnnemis(ennemis,perso_combat,nombre);
        else{
            TypeAction action  = tourPerso(perso_combat,ennemis,aff);
            if (action == QUITTE)
                return QUITTE;
        }
            
        attaquant = 1 - attaquant;
    }

}  


void reintegrerPersoDispo(Type_Liste* liste,Nb* nombre){
    if(!liste->perso_combat)return;
    List_circ tmp = liste->perso_combat;
    Maillon* debut = liste->perso_combat;
    Maillon* courant = liste->perso_combat; 

    do{
        if(!liste->perso_combat)return;
        tmp = courant;
        courant = courant->next;
        Maillon* cel = extraireListCirc(&liste->perso_combat,((PersoC*)tmp)->personnage);
        PersoC* p = (PersoC*)cel;
        
        if(p->personnage.acc1){
            p->personnage.HPmax -= p->personnage.acc1->accessoire.HPbonus;
            p->personnage.HP -= p->personnage.acc1->accessoire.HPbonus;
            ajoutDebut(&liste->accessoire_dispo,(Maillon*)p->personnage.acc1);
            p->personnage.acc1 = NULL;

        }
        if (p->personnage.acc2){
            p->personnage.HPmax -= p->personnage.acc2->accessoire.HPbonus;
            p->personnage.HP -= p->personnage.acc2->accessoire.HPbonus;
            ajoutDebut(&liste->accessoire_dispo,(Maillon*)p->personnage.acc2);
            p->personnage.acc2  = NULL;
        }
        if(p->personnage.HP <= 0)p->personnage.HP = 1;


        nombre->nb_combattant -= 1;
        ajoutFin(&liste->personnage_dispo,cel);
        printf("le perso %s a ete reintegrer\n",((PersoC*)cel)->personnage.nom);
        afficherPersoC(liste->perso_combat);
        nombre->perso_dispo += 1;

    }while(courant != debut);


}

void debloquerAcc(Type_Liste* liste,int roulotte_dispo){
    char* nom_acc = (char*)malloc(sizeof(char)*50);
    int indice_du_nom = rand()%49;
    int prix;
    int attbonus = rand()% 20;
    int defbonus = rand() % 20;
    int HPbonus = rand() % 20;
    int restbonus = rand() %20;
    int strred = rand() % 20;
    if(attbonus >= 16 && HPbonus >= 16)
        prix = 80 + rand()% 20;
    else if (attbonus < 16 &&attbonus >10 && HPbonus >= 15)
        prix  = 50 + rand()% 30;
    else if (attbonus <= 15 && attbonus >10 && HPbonus <= 15 && HPbonus > 10)
        prix = 40 + rand()% 10;
    else if (attbonus <= 10 && attbonus >5 && HPbonus <= 15 && HPbonus > 10)
        prix = 30 + rand()% 10;
    else if (attbonus <= 10 && attbonus >5 && HPbonus <= 10 && HPbonus > 5)
        prix = 20 + rand()% 10;
    else    
        prix = rand()% 20;

    strcpy(nom_acc,*(liste->nom_acc+indice_du_nom));
    MaillonD* nv_acc = creerAccessoire(nom_acc,liste->nombre->accessoire_total,prix,attbonus,defbonus,HPbonus,restbonus,strred);
    liste->nombre->accessoire_total++;

    if(roulotte_dispo == 0){
        ajoutDebutDcirc(&liste->accessoire_roulotte,nv_acc);
        liste->nombre->accessoire_roulotte ++;
        return;
    }else{
        Maillon* nv_acc_simple = AccDToAcc(nv_acc);
        ajoutDebut(&liste->accessoire_dispo,nv_acc_simple);
        liste->nombre->accessoire_dispo++;
    }
    free(nom_acc);

    
}

void gererSanitarium(Type_Liste* liste){
    if(!liste->perso_sanitarium)return;
    MaillonD* debut = liste->perso_sanitarium;
    ListD_circ tmp = liste->perso_sanitarium;
    do{
        if(!tmp)return;
        PersoS* sanni = (PersoS*)tmp;
        tmp = tmp->next;

        printf("le personnage avant %d\n",sanni->personnage.HP);
        
        sanni->personnage.HP += 10;
        printf("le personnage %d\n",sanni->personnage.HP);
        if(sanni->personnage.HP >= sanni->personnage.HPmax){
            sanni->personnage.HP = sanni->personnage.HPmax;
            MaillonD* cel = extraireListDcirc2(&liste->perso_sanitarium,sanni->personnage.num,1);
            Maillon* maillon_simple = MaillonDToMaillon(cel);
            ajoutDebut(&liste->personnage_dispo,maillon_simple);
            liste->nombre->perso_sanni-=1;

        }
       
    }while(tmp != debut);

}


void gererTaverne(Type_Liste* liste){
    if(!liste->perso_taverne)return;
    MaillonD* debut = liste->perso_taverne;
    ListD_circ tmp = liste->perso_taverne;
    do{
        if(!tmp)return;

        PersoT* taverne = (PersoT*)tmp;
        tmp = tmp->next;
        taverne->personnage.str -= 25;
        if(taverne->personnage.str <= 0){
            taverne->personnage.str = 0;
            MaillonD* cel = extraireListDcirc2(&liste->perso_taverne,taverne->personnage.num,1);
            Maillon* maillon_simple = MaillonDToMaillon(cel);
            ajoutDebut(&liste->personnage_dispo,maillon_simple);
            liste->nombre->perso_taverne -=1;
            printf("on a reintegré le perso %s de la taverne %d\n",((PersoD*)maillon_simple)->personnage.nom,((PersoD*)maillon_simple)->personnage.num);
        }
        

    }while(tmp != debut);
}


void remplirRoulotte(Type_Liste* liste){
    if(!liste)return;
    int nb_acc = rand()%4;
    for(int i = 0; i < nb_acc; i++){
        debloquerAcc(liste,0);
    }
}


void gererRoulotte(Type_Liste* liste,AFFICHAGE aff,Joueur* joueur){
    if(!liste->accessoire_roulotte){
        printf("la roulotte est vide\n");
        remplirRoulotte(liste);
        return;
    }
    int achat = 0;
    if(aff == ASCII){
        afficherAccRoulotteAscii(liste->accessoire_roulotte);
        do{ 
            printf("que voulez vous achetez?");
            if(scanf("%d",&achat) != 1){
                return;
            }
            if(rechercheAccR(liste->accessoire_roulotte,achat) == 1 && canAffordAccessory(liste->accessoire_roulotte,*joueur,achat) == 1)break;
            else{
                printf("je ne le trouve pas dans la liste ou tu n'a pas assez d'argent\n");
                printf("tu as %d or\n",joueur->or);
                while(getchar() != '\n');
                continue;
            }
        }while(1);
    }else{
        MLV_clear_window(MLV_COLOR_BLACK);
        afficherHameauG();
        afficherRoulotteG(liste->accessoire_roulotte);
        achat = gererRoulotteG(liste->accessoire_roulotte);
        if(achat == -1)return;
        if(canAffordAccessory(liste->accessoire_roulotte,*joueur,achat) == 0)return;
        
    }
    MaillonD* acc_double = extraitAccR(&liste->accessoire_roulotte,achat);
    if(!acc_double)return;
    liste->nombre->accessoire_roulotte -=1;
    joueur->or -= ((AccR*)acc_double)->accessoire.prix;

    Maillon* acc_simple = AccDToAcc(acc_double);

    ajoutDebut(&liste->accessoire_dispo,acc_simple);
    liste->nombre->accessoire_dispo +=1;   
    
    if(aff == ASCII){
        afficherAccRoulotteAscii(liste->accessoire_roulotte);
        afficherAccDAscii(liste->accessoire_dispo);
    }
    
}


void ajouterAccPersoC(Type_Liste* liste,AFFICHAGE aff,Maillon* nv_perso){
    int accessoire = 0;
    if(is_list_empty(liste->accessoire_dispo) == 0){
            if(aff == ASCII){
                printf("voulez vous lui donner des accessoires ?\n");
                printf("1: oui\n");
                printf("2: non\n");
                    do{
                    if(scanf("%d",&accessoire) != 1){
                        printf("vous n'avez pas entre un chiffre\n");
                        while(getchar() != '\n');
                        continue;
                    }
                    if (accessoire == 1 || accessoire == 2)
                        break;
                    else
                        printf("choix indisponible\n");
                }while(1);
            }
            if(accessoire == 1){
                for(int i = 0; i < 2; i++){
                    if(aff == ASCII){
                        afficherAccDAscii(liste->accessoire_dispo);
                        printf("quel accessoire voulez vous lui donner ? ");
                        do{
                            if(scanf("%d",&accessoire) != 1){
                            printf("vous n'avez pas entre un chiffre\n");
                            while(getchar() != '\n');
                            continue;
                            }
                            if(rechercheAcc(liste->accessoire_dispo,accessoire) == 1)
                                break;
                            else
                                printf("accessoire indisponible\n");
                        }while(1);
                        
                    }
                    PersoD* perso = (PersoD*)nv_perso;
                    if(!perso->personnage.acc1){
                        Maillon* acc1 = extraitAccD(&liste->accessoire_dispo,accessoire);
                        perso->personnage.acc1 = (MaillonAcc*)acc1;
                        perso->personnage.HPmax += perso->personnage.acc1->accessoire.HPbonus;
                        perso->personnage.HP += perso->personnage.acc1->accessoire.HPbonus;

                    }else if(!perso->personnage.acc2){
                        Maillon* acc2 = extraitAccD(&liste->accessoire_dispo,accessoire);
                        perso->personnage.acc2 = (MaillonAcc*)acc2;
                        perso->personnage.HPmax += perso->personnage.acc2->accessoire.HPbonus;
                        perso->personnage.HP += perso->personnage.acc2->accessoire.HPbonus;
                    }
                }
                
            }
    }
}


void debloquerNouveauPerso(Type_Liste* liste,AFFICHAGE aff,int niveau,Joueur*joueur){
    int choix = 0;
    char *nom = (char*)malloc(sizeof(char)*50);

    MaillonD* cel;
    if (aff == ASCII){

        printf("vous avez débloqué un nouveau personnage que voulez vous en faire\n");
        printf("1: le mettre dans la liste de perso dispo\n");
        printf("2: le mettre dans la liste de perso en combat\n");
        printf("3: le mettre a la taverne \n");
        printf("4: le mettre au sanitarium : ");
        do{
            if(scanf("%d",&choix) != 1){
                printf("vous n'avez pas entre un chiffre\n");
                while(getchar() != '\n');
                continue;
            }
            if (choix >= 1 && choix <= 4)
                break;
            else
                printf("choix indisponible\n");
        }while(1);
        printf("comment voulez vous appelez votre nouveau personnage ? ");
        scanf("%49s",nom);
    }else{
        
        char* nom_tmp;
        MLV_draw_filled_rectangle(100,100,WINDOW_WIDTH-200,WINDOW_HEIGHT-200,MLV_COLOR_WHITE);
        MLV_draw_filled_rectangle(105,105,WINDOW_WIDTH-210,WINDOW_HEIGHT-210,MLV_COLOR_DARK_GRAY);
        MLV_wait_input_box(470,120,200,50,MLV_COLOR_BLACK,MLV_COLOR_WHITE,MLV_COLOR_BLACK,"Le nom du nouveau perso",&nom_tmp);
        strcpy(nom,nom_tmp);
    }
    
    Classe* classe_alea = choisirClasseAleatoire(liste->classe_dispo,*liste->nombre);
    if(!classe_alea)return;
    Maillon* nv_perso = creerPerso(*classe_alea,nom,liste->nombre->perso_total,liste->nombre);
    if(!nv_perso)return;
    if(aff == GRAPHICS){
        afficherInfo(*joueur,1); 
        afficherPersoG(((PersoD*)nv_perso)->personnage);
        choix = gererNvPerso(liste,joueur);
        printf("choix debut %d",choix);
        if(choix == -1)return;
    }
    
    if(choix == 5){
        if(aff == GRAPHICS){
            Maillon* acc1 = gererAccessoireG(&liste->accessoire_dispo);
            if(acc1){
                PersoD* perso = (PersoD*)nv_perso;
                MaillonAcc* accessoire = (MaillonAcc*)acc1;
                perso->personnage.acc1 = accessoire;
                perso->personnage.HPmax += accessoire->accessoire.HPbonus;
                perso->personnage.HP += accessoire->accessoire.HPbonus;
            }
            afficherInfo(*joueur,1); 
            afficherPersoG(((PersoD*)nv_perso)->personnage);
            choix = gererNvPerso(liste,joueur);
            printf("choix: %d",choix);

            if(choix == -1)return;
            }
    }if(choix == 6){
        if(aff == GRAPHICS){
            Maillon* acc2 = gererAccessoireG(&liste->accessoire_dispo);
            if(acc2){
                PersoD* perso = (PersoD*)nv_perso;
                MaillonAcc* accessoire = (MaillonAcc*)acc2;
                perso->personnage.acc2 = accessoire;
                perso->personnage.HPmax += accessoire->accessoire.HPbonus;
                perso->personnage.HP += accessoire->accessoire.HPbonus;
            }
            afficherInfo(*joueur,1); 
            afficherPersoG(((PersoD*)nv_perso)->personnage);
            choix = gererNvPerso(liste,joueur);
            printf("choix: %d",choix);
            if(choix == -1)return;
            }
    }
    if(choix == 1){
        liste->nombre->perso_dispo += 1;
        ajoutDebut(&liste->personnage_dispo,nv_perso);

    }else if (choix == 2){
        printf("le niveau %d\n",niveau);
        if((liste->nombre->nb_combattant >= 2 && niveau <= 5) || (liste->nombre->nb_combattant >= 3)){
            printf("vous avez atteint le nombre maximum de combattant\n");
            libererAccessoireNomPerso(nv_perso);
            free(nv_perso);
            debloquerNouveauPerso(liste,aff,niveau,joueur);
        }else{
            ajouterAccPersoC(liste,aff,nv_perso);
            ajoutFinCirc (&liste->perso_combat,nv_perso);
            liste->nombre->nb_combattant+=1;
            liste->nombre->perso_total+=1;

        }
    }else if(choix == 3){
        if(liste->nombre->perso_taverne >= 2){
            if (aff == ASCII){
                printf("il y'a deja trop de gens a la Taverne\n");
            }
            libererAccessoireNomPerso(nv_perso);
            free(nv_perso);
            debloquerNouveauPerso(liste,aff,niveau,joueur);                   
        }else{
            liste->nombre->perso_taverne += 1;
            liste->nombre->perso_total+=1;

            printf("numero di perso apres s'etre transformer avant la taverne %d\n",((PersoD*)nv_perso)->personnage.num);

            cel = MaillonToMaillonD(nv_perso);
            ajoutDebutDcirc(&liste->perso_taverne,cel);
        }
    }else if (choix == 4){
        if(liste->nombre->perso_taverne >= 2){
            if (aff == ASCII){
                printf("il y'a deja trop de gens au sanniturium\n");
            }
            libererAccessoireNomPerso(nv_perso);
            free(nv_perso);
            debloquerNouveauPerso(liste,aff,niveau,joueur);
        }else{
            liste->nombre->perso_sanni +=1;
            liste->nombre->perso_total+=1;

            cel = MaillonToMaillonD(nv_perso);
            ajoutDebutDcirc(&liste->perso_sanitarium,cel);
        }
    }else{
        if(aff == ASCII)
            printf("choix indisponible\n");
        libererAccessoireNomPerso(nv_perso);
        free(nv_perso);
        debloquerNouveauPerso(liste,aff,niveau,joueur);
    }
    free(nom);

}


void enleverDefensePerso(List_circ* perso_combat){
    if(!*perso_combat)return;
    List_circ tmp = *perso_combat;
    Maillon* debut = *perso_combat;


    do{
        PersoC* perso = (PersoC*)tmp;
        if(perso->personnage.activer_defense == 1)
            perso->personnage.activer_defense = 0;

        tmp = tmp->next;
    }while(tmp != debut);
}


void revivreEnnemis(List *donjon){
    List tmp = *donjon;
    for(;tmp;tmp = tmp->next){
        Salle* salle = (Salle*)tmp;
        salle->ennemis.HPenn = salle->ennemis.HPennMax;
    }
}


void donjon(Type_Liste* liste, AFFICHAGE aff,Joueur* joueur,Execute* execute){
    if(execute->sauvegarde_milieu == 1){
        Type_Liste* liste2 = initialiser_liste();
        lancerSauvegarde(liste2,execute->fichier,execute->fichier_sauvegarde,&joueur);
        execute->sauvegarde_milieu = 0;
    }else{
        if (aff == ASCII){
            affichageDebutAscii(liste->personnage_dispo,liste->classe_dispo);
            choisirCombattantAscii(liste);
            printf("vous avez choisi %d combattants\n\n",liste->nombre->nb_combattant);
            choisirAccessoireAscii(liste);
            printf("le donjon commence !!!!\n\n");
            affichagePersoChoisi(liste->perso_combat);
            afficherAccPersoC(liste->perso_combat);
            printf("\n");
            afficherPersoC(liste->perso_combat);    

        }else{
            if(liste->nombre->nb_combattant > 2  ){
                printf("le nombre de personnage:%d",liste->nombre->nb_combattant);
                MLV_clear_window(MLV_COLOR_BLACK);
                MLV_draw_text(WINDOW_WIDTH/2-100,WINDOW_HEIGHT/2-100,"Tu n'a le bon nombre de personnage...",MLV_COLOR_WHITE);
                MLV_actualise_window();
                MLV_wait_seconds(2);
                reintegrerPersoDispo(liste,liste->nombre);
                return;
            }
           
        }
    }

    List tmp = liste->donjon;
    while(((Salle*)tmp)->ennemis.niveau != joueur->niveau)tmp = tmp->next;

    while(tmp){
        if (liste->nombre->nb_combattant == 0)
            break;
        if (!liste->perso_combat || !tmp || !liste->nombre)
            return; 
        Salle* salle = (Salle*)tmp;

        if (aff == GRAPHICS){
            MLV_clear_window(MLV_COLOR_BLACK);
            afficherCombat(liste->perso_combat,salle->ennemis);

        }
        TypeAction action = niveau(&liste->perso_combat,&salle->ennemis,liste->nombre,aff);
        if (action == QUITTE){
            sauvegarderPartie(liste,*joueur,execute->fichier,execute->fichier_sauvegarde);
            execute->sauvegarde_milieu = 1;
            return;
        }
        enleverDefensePerso(&liste->perso_combat);

        if (salle->ennemis.HPenn <= 0){// victoire des personnages
            tmp = tmp->next;  // on passe a l'ennemis suivant
            gererSanitarium(liste);
            gererTaverne(liste);
            ajouterNbcombat(&liste->perso_combat);
            if(aff == ASCII){
                printf("vous avez battu l'ennemis %s !!!!!\n\n" ,salle->ennemis.nom);
            }
            if (salle->ennemis.niveau % 2 == 0 && salle->ennemis.niveau != 0){
               
                debloquerNouveauPerso(liste,aff,salle->ennemis.niveau,joueur);
            }
            joueur->or +=10;
            joueur->niveau++;
            debloquerAcc(liste,1);
        }
    }
    joueur->niveau = 0;

    if(!tmp){
        if(aff == ASCII)
            printf("vous avez gagné !!!!\n");
    }else{
        if(aff == ASCII)
            printf("vous avez perdu !!!!\n");
    }

    reintegrerPersoDispo(liste,liste->nombre);
    revivreEnnemis(&liste->donjon);
}


void rentrerSanniTaverne(Type_Liste*liste,AFFICHAGE aff,int sanniTaverne){
    int choix = 0;
    if(aff == ASCII){
        afficherPersoD(liste->personnage_dispo);
        do{
            printf("qui voulez vous rentrez lui redonner des forces?");
            if(scanf("%d",&choix) !=1){
                printf("mauvaise entree\n");
                while(getchar()!='\n');
                continue;
            }
            if(recherchePerso(liste->personnage_dispo,choix) == 1)break;
            else{
                printf("choix indisponible\n");
                while(getchar()!='\n');
                continue;
            }
        }while(1);
    }
    Maillon* perso = extraitPerso(&liste->personnage_dispo,choix);
    liste->nombre->perso_dispo -=1;
    MaillonD* cel = MaillonToMaillonD(perso);
    if(sanniTaverne == 0){
        ajoutDebutDcirc(&liste->perso_sanitarium,cel);
        liste->nombre->perso_sanni +=1;

    }else if (sanniTaverne == 1){
        ajoutDebutDcirc(&liste->perso_taverne,cel);
        liste->nombre->perso_taverne +=1;

    }
    afficherPersoD(liste->personnage_dispo);

}


int hameau(Type_Liste * liste,AFFICHAGE aff,Joueur* joueur,Execute* execute){
    int choix = 0;
    if(aff == ASCII){
        printf("vous êtes dans le hameau vous pouvez :\n");
        printf("1: allez en combat\n");
        printf("2: acceder a la roulotte\n");
        printf("3: rentrez quelqu'un au saniturium\n");
        printf("4: rentrez quelqu'un a la taverne\n");
        printf("5:quitter\n");
        do{
            if(scanf("%d",&choix) != 1){
                printf("vous avez fait une mauvaise entrée...\n");
                while(getchar()!= '\n')continue;   
            }
            if(choix <= 5 && choix > 0)
                break;
            else 
                printf("choix indisponible...");
        }while(1);
    }else{
        afficherHameauG();
        choix = gererHameauG();
    }
    switch(choix){

        case 0:
            if(aff == ASCII)
                printf("vous avez fait une mauvaise entrée...\n");
            else{
                afficherInfo(*joueur,0);
                gererInfo(liste,joueur);
            }
            break;
        case 1:
            afficherPersoC(liste->perso_combat);
            donjon(liste,aff,joueur,execute);
            break;
        case 2:
            gererRoulotte(liste,aff,joueur);
            break;
        case 3:
            rentrerSanniTaverne(liste,aff,0);
            break;
        case 4:
            rentrerSanniTaverne (liste,aff,1);
            break;
        case 5:
            return 5;

        default:
            printf("mauvaise entrée tu reste la...\n");
            hameau(liste,aff,joueur,execute);
    }
    return -1;
}



int mainGame(Type_Liste* liste,AFFICHAGE aff,Joueur*joueur,Execute* execute){
    int res  = 0;
    do{
        res = hameau(liste,aff,joueur,execute);
    }while(res != 5);
    
    return 0;

}
