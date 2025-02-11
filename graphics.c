#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "donnee.h"
#include "master.h"


void initialiserFenetre(){
    MLV_create_window("Darkest dungeon", "darkest dungeon", WINDOW_WIDTH, WINDOW_HEIGHT);
}


void afficherTexteFormate(int x, int y, const char* texte, int valeur, MLV_Font* font, MLV_Color couleur){
    char buffer[100];
    sprintf(buffer, texte, valeur);
    MLV_draw_text_with_font(x, y, buffer, font, couleur);
}


void afficherInfoAccG(Acc accessoire){
    int x = 260;
    int y = 120;
    MLV_Font* font = MLV_load_font( "font/Creepster-Regular.ttf",30);
    
    //le fond gris
    MLV_draw_filled_rectangle(100,100,WINDOW_WIDTH-200,WINDOW_HEIGHT-200,MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(105,105,WINDOW_WIDTH-210,WINDOW_HEIGHT-210,MLV_COLOR_DARK_GRAY);
    //pour fermer
    MLV_Image*image = MLV_load_image("image/croix5.png");
    MLV_draw_image(image,802,95);

    //afficher l'acc suivant
    MLV_draw_filled_rectangle(610,525,100,60,MLV_COLOR_BLUE);
    MLV_draw_text_with_font(620,535,"Next",font,MLV_COLOR_WHITE);
    
    // le fond noir pour ecrir
    MLV_draw_filled_rectangle(250,120,500,300 ,MLV_COLOR_BLACK);

    // pour ajouter l'acc
    MLV_draw_filled_rectangle(400,455,200,60,MLV_COLOR_BLUE);
    MLV_draw_text_with_font(440,465,"ajouter",font,MLV_COLOR_WHITE);   

    MLV_draw_text_with_font(x,y,"Nom : ",font,MLV_COLOR_WHITE);
    MLV_draw_text_with_font(x+100,y,accessoire.nom,font,MLV_COLOR_WHITE);
    afficherTexteFormate(x,y+50,"attBonus: %d",accessoire.attbonus,font,MLV_COLOR_WHITE);
    afficherTexteFormate(x,y+100,"defbonus: %d",accessoire.defbonus,font,MLV_COLOR_WHITE);
    afficherTexteFormate(x,y+150,"HPbonus: %d",accessoire.HPbonus,font,MLV_COLOR_WHITE);
    afficherTexteFormate(x,y+200,"restbonus: %d",accessoire.restbonus,font,MLV_COLOR_WHITE);
    afficherTexteFormate(x,y+250,"strred: %d",accessoire.strred,font,MLV_COLOR_WHITE);

    MLV_actualise_window();
    MLV_free_font(font);
    MLV_free_image(image); 

}


Maillon* gererAccessoireG(List* acc_dispo){
    List tmp = *acc_dispo;
    Point p;
    while(tmp){
        AccD* acc = (AccD*)tmp;
        afficherInfoAccG(acc->accessoire);
        MLV_wait_mouse(&p.x,&p.y);
        if(p.x >= 809 && p.x <= 895 && p.y >= 105 && p.y <= 190){
            break;
        }
        if(p.x >= 400 && p.x <= 600 && p.y >= 455 && p.y <= 515){
            Maillon* cel = extraitAccD(acc_dispo,acc->accessoire.num);
            return cel;
        }if(p.x >= 610 && p.x <= 710 && p.y >= 525 && p.y <= 585){
                tmp = tmp->next;
        }
    }
    return NULL;
}


void afficherEnnemisG(Ennemis ennemis){
    MLV_Image* image = NULL;
    if(strcmp(ennemis.nom,"brigand") == 0)
        image = MLV_load_image("image/brigand.png"); 

    else if(strcmp(ennemis.nom,"squelette") == 0)
        image = MLV_load_image("image/squelette2.png"); 

    else if(strcmp(ennemis.nom,"goule") == 0)
        image = MLV_load_image("image/goule.png"); 

    else if(strcmp(ennemis.nom,"gargouille") == 0)
        image = MLV_load_image("image/gargouille.png"); 

    else if(strcmp(ennemis.nom,"bagarreur") == 0)
        image = MLV_load_image("image/bagarreur.png"); 

    else if(strcmp(ennemis.nom,"brigand_raideur") == 0)
        image = MLV_load_image("image/brigand_raideur.png"); 
    
    else if(strcmp(ennemis.nom,"fou") == 0)
        image = MLV_load_image("image/fou.png"); 

    else if(strcmp(ennemis.nom,"ancetre") == 0)
        image = MLV_load_image("image/ancetre.png"); 

    else if(strcmp(ennemis.nom,"collectionneur") == 0)
        image = MLV_load_image("image/collectionneur.png"); 

    else if(strcmp(ennemis.nom,"fanatique") == 0)
        image = MLV_load_image("image/fanatique.png"); 
        
    MLV_resize_image_with_proportions(image,200,300);
    // barre de vie 
    MLV_draw_rectangle(600,130,100,10,MLV_COLOR_WHITE);
    int vie = (int)(((float)ennemis.HPenn / (float)ennemis.HPennMax) * 100);
    printf("la vie de l'ennemis : %d\n",ennemis.HPenn);
    MLV_draw_filled_rectangle(601,131,vie-1,9,MLV_COLOR_GREEN);

    MLV_draw_image(image,600,150); 
    MLV_free_image(image);    

}


void afficherPersoG(Perso perso){
    MLV_Font* font = MLV_load_font( "font/Creepster-Regular.ttf",40);
    MLV_Image* image;
    int x = 370;
    int y = 120;
    if(strcmp(perso.classe.nom,"chasseur_prime") == 0){
        image = MLV_load_image("image/chasseur_prime.png");
        MLV_resize_image_with_proportions(image,300,600);
        MLV_draw_image(image,50,60);

    }else if(strcmp(perso.classe.nom,"chien") == 0){
        image = MLV_load_image("image/chien2.png");
        MLV_resize_image_with_proportions(image,500,700);
        MLV_draw_image(image,0,100);
    }else if (strcmp(perso.classe.nom,"furie") == 0){
        image = MLV_load_image("image/furie.png");
        MLV_resize_image_with_proportions(image,400,700);
        MLV_draw_image(image,0,100);
    }else if (strcmp(perso.classe.nom,"vestale") == 0){
        image = MLV_load_image("image/vestale2.png");
        MLV_resize_image_with_proportions(image,400,700);
        MLV_draw_image(image,0,100);
    }else if(strcmp(perso.classe.nom,"medecin_peste") == 0){
        image = MLV_load_image("image/medecin_peste2.png");
        MLV_resize_image_with_proportions(image,300,700);
        MLV_draw_image(image,50,100);
    }else if (strcmp(perso.classe.nom,"evade") == 0){
        image = MLV_load_image("image/evade.png");
        MLV_resize_image_with_proportions(image,300,700);
        MLV_draw_image(image,100,100);
    
    }else{
        return;
    }

    MLV_draw_text_with_font(x,y,"Nom : ",font,MLV_COLOR_WHITE);
    MLV_draw_text_with_font(x+100,y,perso.nom,font,MLV_COLOR_WHITE);

    afficherTexteFormate(x,y+50,"Attaque : %d",perso.att,font,MLV_COLOR_WHITE);
    afficherTexteFormate(x,y+100,"Defense : %d",perso.def,font,MLV_COLOR_WHITE);
    afficherTexteFormate(x,y+150,"HP : %d",perso.HP,font,MLV_COLOR_WHITE);
    afficherTexteFormate(x+100,y+150,"/ %d",perso.HPmax,font,MLV_COLOR_WHITE);
    afficherTexteFormate(x,y+200,"Rest : %d",perso.rest,font,MLV_COLOR_WHITE);
    afficherTexteFormate(x,y+250,"Stress : %d",perso.str,font,MLV_COLOR_WHITE);
    afficherTexteFormate(x,y+300,"Nombre de combat : %d",perso.nbcomb,font,MLV_COLOR_WHITE);

    MLV_actualise_window();
    MLV_free_font(font);
    MLV_free_image(image);    

}


void afficherHameauG(){
    MLV_Image* image_hameau = MLV_load_image("image/hameau.jpg");
    MLV_draw_image(image_hameau,0,0);
    // MLV_draw_rectangle(917,600,75,55,MLV_COLOR_RED);

    MLV_actualise_window(); 

    MLV_free_image(image_hameau);
}


Hameau gererHameauG(){
    Point p ;
    MLV_wait_mouse(&p.x,&p.y);  
    if(p.x >=31 && p.x <= 280 && p.y >= 415 && p.y <= 600){
        return ROULOTTE;
            
    }else if (p.x >= 138 && p.x <= 740 && p.y >= 34 && p.y <= 330){
        return DONJON;
        
    }else if (p.x>= 917 && p.x <=992 && p.y >= 600 && p.y <= 655){
        return INFO;
    
    }else
        return -1;
    
}


int gererRestGraphics(List_circ *perso_combat){
    Point p;
    List_circ combattants = *perso_combat;
    Maillon* debut = *perso_combat;
    MLV_draw_rectangle(352,518,50,50,MLV_COLOR_DARK_GRAY);
    MLV_actualise_window();
    MLV_wait_mouse(&p.x,&p.y);
    do{
        PersoC* perso = (PersoC*)combattants;
        if(
            p.x >=perso->personnage.zone_graphics.x && p.x<=perso->personnage.zone_graphics.x+RECTANGLE_PERSO_W &&
            p.y >=perso->personnage.zone_graphics.y && p.y <=perso->personnage.zone_graphics.y + RECTANGLE_PERSO_H  
        ){
            printf("vous voulez guerir : %s\n",perso->personnage.nom);
            return perso->personnage.num;
        }
        combattants = combattants->next;
    }while(combattants != debut);
    gererRestGraphics(perso_combat);
    return -1;
    

}


void afficherPersoCombatG(List_circ perso_combat){
    if(!perso_combat)return;
    Maillon*debut = perso_combat;
    MLV_Image* image;
    int x_perso = 100;
    int y_perso = 120;

    
    do{
        PersoC* perso = (PersoC*)perso_combat;
        if(strcmp(perso->personnage.classe.nom,"furie") == 0)
            image = MLV_load_image("image/furie_combat.png");

        else if(strcmp(perso->personnage.classe.nom,"vestale") == 0)
            image = MLV_load_image("image/vestale_combat.png");

        else if(strcmp(perso->personnage.classe.nom,"medecin_peste") == 0)
            image = MLV_load_image("image/medecin_peste_combat.png");
        else if (strcmp(perso->personnage.classe.nom,"evade") == 0)
            image = MLV_load_image("image/evade_combat.png");
        else if (strcmp(perso->personnage.classe.nom,"chasseur_prime") == 0)
            image = MLV_load_image("image/chasseur_prime_combat.png");
        else if (strcmp(perso->personnage.classe.nom,"chien") == 0)
            image = MLV_load_image("image/chien.png");

        //barre de vie
        int vie = (int)(((float)perso->personnage.HP/(float)perso->personnage.HPmax)*100) ;
        MLV_draw_rectangle(x_perso,y_perso-20,100,10,MLV_COLOR_WHITE);
        MLV_draw_filled_rectangle(x_perso+1,y_perso-19,vie-2,8,MLV_COLOR_GREEN);

        //barre de stresse
        int stresse = perso->personnage.str;
        MLV_draw_rectangle(x_perso,y_perso-50,100,10,MLV_COLOR_WHITE);
        MLV_draw_filled_rectangle(x_perso+1,y_perso-49,stresse-1,9,MLV_COLOR_BLUE);

        MLV_resize_image_with_proportions(image,200,300);
        MLV_draw_image(image,x_perso,y_perso);
        perso->personnage.zone_graphics.x = x_perso;
        perso->personnage.zone_graphics.y = y_perso;
        x_perso += 150;
        perso_combat = perso_combat->next;
    }while(perso_combat != debut);
    MLV_free_image(image);    

}


void afficherCombat(List_circ perso_combat,Ennemis ennemis){
    int x = 200;
    int y = 520;
    MLV_Font* font = MLV_load_font( "font/Creepster-Regular.ttf",30);

    MLV_Image* image = MLV_load_image("image/arene.jpg");
    MLV_draw_image(image,0,0);
    MLV_Image* croix = MLV_load_image("image/croix5.png");
    MLV_draw_image(croix,910,10);
    // attaquer
    MLV_draw_filled_rectangle(x,y,50,50,MLV_COLOR_DARK_GRAY);
    MLV_draw_text_with_font(x+15,y+10,"A",font,MLV_COLOR_BLACK);
    // defendre
    MLV_draw_filled_rectangle(x+75,y,50,50,MLV_COLOR_DARK_GRAY);
    MLV_draw_text_with_font(x+90,y+10,"D",font,MLV_COLOR_BLACK);

    // rest
    MLV_draw_filled_rectangle(x+150,y,50,50,MLV_COLOR_DARK_GRAY);
    MLV_draw_text_with_font(x+170,y+10,"R",font,MLV_COLOR_BLACK);

    afficherPersoCombatG(perso_combat);
    afficherEnnemisG(ennemis);
    MLV_actualise_window();
    MLV_free_image(image);    
}




void afficherInfo(Joueur joueur,int en_combat){
    MLV_Font* info_font = MLV_load_font( "font/Creepster-Regular.ttf",30);
    MLV_Image* img_or = NULL;
    MLV_Image* image = NULL;
    // le fond
    MLV_draw_filled_rectangle(100,100,WINDOW_WIDTH-200,WINDOW_HEIGHT-200,MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(105,105,WINDOW_WIDTH-210,WINDOW_HEIGHT-210,MLV_COLOR_DARK_GRAY);

    // le fond du texte en noir
    MLV_draw_filled_rectangle(360,120,350,350 ,MLV_COLOR_BLACK);


    // le bord
    MLV_draw_rectangle(100,100,WINDOW_WIDTH-200,WINDOW_HEIGHT-200,MLV_COLOR_WHITE);

    // pour le titre
    MLV_draw_filled_rectangle(100,50,200,50,MLV_COLOR_DARK_GRAY);
    if(en_combat == 0)
        MLV_draw_text_with_font(110,55,"Information",info_font,MLV_COLOR_BLACK);
    else 
        MLV_draw_text_with_font(110,55,"Nouveau",info_font,MLV_COLOR_BLACK);

    // l'image pour fermer
    if(en_combat == 0){
        image = MLV_load_image("image/croix5.png");
        MLV_draw_image(image,802,95);
    }
   

    //pour separer la photo du perso et les info du perso
    MLV_draw_line(295,105,295,598,MLV_COLOR_WHITE);

    //fleche pour suivant
    if(en_combat == 0){
        MLV_draw_filled_rectangle(610,525,100,60,MLV_COLOR_BLUE);
        MLV_draw_text_with_font(620,535,"Next",info_font,MLV_COLOR_WHITE);
    }
    //ajouter_combat ou perso_dispo
    MLV_draw_filled_rectangle(750,400,100,60,MLV_COLOR_BLUE);
    MLV_draw_text_with_font(760,410,"Combat",info_font,MLV_COLOR_WHITE);
    
    // ajout sanni 
    
    MLV_draw_filled_rectangle(750,300,100,60,MLV_COLOR_BLUE);
    if(en_combat == 0)
        MLV_draw_text_with_font(760,310,"Sanni",info_font,MLV_COLOR_WHITE);
    else
        MLV_draw_text_with_font(760,310,"Dispo",info_font,MLV_COLOR_WHITE);

    // ajout taverne
    MLV_draw_filled_rectangle(750,200,100,60,MLV_COLOR_BLUE);
    MLV_draw_text_with_font(760,210,"Taverne",info_font,MLV_COLOR_WHITE);

    //acc1
    MLV_draw_filled_rectangle(750,510,50,50,MLV_COLOR_BLUE);
    MLV_draw_text_with_font(750,520,"ACC1",info_font,MLV_COLOR_WHITE);

    //acc2
    MLV_draw_filled_rectangle(810,510,50,50,MLV_COLOR_BLUE);
    MLV_draw_text_with_font(810,520,"ACC2",info_font,MLV_COLOR_WHITE);

    // l'or du joueur 
    if(en_combat == 0){
        img_or = MLV_load_image("image/or4.png");
        MLV_draw_image(img_or,350,500);
        afficherTexteFormate(450,530," %d",joueur.or,info_font,MLV_COLOR_BLACK);

    }
    
    MLV_actualise_window();
    if(image)
        MLV_free_image(image);
    MLV_free_font(info_font);
    if(img_or)
        MLV_free_image(img_or);

}


int gererNvPerso(Type_Liste* liste,Joueur* joueur){
    Point p;
    
    while(1){
        MLV_wait_mouse(&p.x,&p.y);
        if (p.x >= 750 && p.x <= 850 && p.y >= 300 && p.y <= 360){//dispo
            return 1;
        }if(p.x >= 750 && p.x <= 850 && p.y >= 200 && p.y <= 260){//taverne
            return 3;
        }if (p.x >= 750 && p.x <= 850 && p.y >= 400 && p.y <= 460){// en combat
            return 2;
        }if(p.x >= 750 && p.x <= 800 && p.y >= 510 && p.y <= 560){
            return 5; // pour le premier acc
        }if(p.x >= 810 && p.x <= 860 && p.y >= 510 && p.y <= 560){
            return 6;// pour le deuxieme acc
        }
    }
    return -1;

}


void gererInfo(Type_Liste* liste,Joueur* joueur){
    afficherInfo(*joueur,0);
    List perso_d = liste->personnage_dispo;
    Point p;

    do{
        if(!perso_d)return;
        MLV_clear_window(MLV_COLOR_BLACK);
        afficherHameauG();
        afficherInfo(*joueur,0);
        MLV_actualise_window();
        PersoD* perso = (PersoD*)perso_d;
        afficherPersoG(perso->personnage);
        MLV_wait_mouse(&p.x,&p.y);
        if(p.x >= 809 && p.x <= 895 && p.y >= 105 && p.y <= 190){// la croix
            break;

        }if (p.x >= 750 && p.x <= 850 && p.y >= 400 && p.y <= 460){// en combat
            if( (liste->nombre->nb_combattant <= 2 && joueur->niveau <= 5 ) || liste->nombre->nb_combattant <= 3 ){
                Maillon* cel = extraitPerso(&liste->personnage_dispo,perso->personnage.num);
                ajoutFinCirc(&liste->perso_combat,cel);
                liste->nombre->nb_combattant++;
                liste->nombre->perso_dispo--;
            }
            break;
        }if (p.x >= 750 && p.x <= 850 && p.y >= 300 && p.y <= 360){//sanniturium
            if(liste->nombre->perso_sanni <2){
                Maillon* cel1 = extraitPerso(&liste->personnage_dispo,perso->personnage.num);
                MaillonD* cel_double = MaillonToMaillonD(cel1);
                ajoutDebutDcirc(&liste->perso_sanitarium,cel_double);
                liste->nombre->perso_sanni++;
                liste->nombre->perso_dispo--;
                break;
            }
            

            
        }if(p.x >= 750 && p.x <= 850 && p.y >= 200 && p.y <= 260){//taverne
            if(liste->nombre->perso_taverne <2){
                Maillon* cel2 = extraitPerso(&liste->personnage_dispo,perso->personnage.num);
                MaillonD* cel_double = MaillonToMaillonD(cel2);
                ajoutDebutDcirc(&liste->perso_taverne,cel_double);
                liste->nombre->perso_taverne++;
                liste->nombre->perso_dispo--;
                break;

            }
            
        }if(p.x >= 750 && p.x <= 800 && p.y >= 510 && p.y <= 560){//acc1
            Maillon* acc1 = gererAccessoireG(&liste->accessoire_dispo);
            if(acc1){
                    MaillonAcc* accessoire = (MaillonAcc*)acc1;
                    perso->personnage.acc1 = accessoire;
                    perso->personnage.HPmax += accessoire->accessoire.HPbonus;
                    perso->personnage.HP += accessoire->accessoire.HPbonus;
                }
        }if(p.x >= 810 && p.x <= 860 && p.y >= 510 && p.y <= 560){//acc2
            Maillon* acc2 = gererAccessoireG(&liste->accessoire_dispo);
            if(acc2){
                    MaillonAcc* accessoire = (MaillonAcc*)acc2;
                    perso->personnage.acc2 = accessoire;
                    perso->personnage.HPmax += accessoire->accessoire.HPbonus;
                    perso->personnage.HP += accessoire->accessoire.HPbonus;
                }
        }if(p.x >= 610 && p.x <= 710 && p.y >= 525 && p.y <= 585){// boutton suivant
                perso_d = perso_d->next;
        }        
    }while(perso_d);
   
   
}


TypeAction ActionGraphique(){
    Point p;
    while(1){
        MLV_wait_mouse(&p.x,&p.y);
        if(p.x >= 920 && p.x <= 995 && p.y >= 25 && p.y <= 100)
            return QUITTE;
        else if (p.x>=199 && p.x <= 250 && p.y >= 520 && p.y <= 570)
            return ATTAQUE;
        else if(p.x>=275 && p.x <= 325 && p.y >= 520 && p.y <= 570)
            return DEFENSE;
        else if (p.x>=350 && p.x <= 400 && p.y >= 520 && p.y <= 570)
            return REST;
    }
    
    
    
}

int gererRoulotteG(ListD_circ acc_roulotte){
    
    if(!acc_roulotte)return -1;
    Point p;
    MaillonD* debut = acc_roulotte;
    while(1){
        MLV_wait_mouse(&p.x,&p.y);
        if(p.x >= 860 && p.x <= 947 && p.y >= 55 && p.y <=143)
            return -1;
        do{
            AccR* acc = (AccR*)acc_roulotte;
            if(p.x>= acc->accessoire.zone_roulotte.x && p.x <=acc->accessoire.zone_roulotte.x + 100 &&
                p.y >= acc->accessoire.zone_roulotte.y && p.y <= acc->accessoire.zone_roulotte.y +30){
                    printf("j'achetteeee\n");
                    return acc->accessoire.num;
                }
            acc_roulotte = acc_roulotte->next;
        }while(acc_roulotte != debut);
        return -1;

        printf("x: %d, y:%d",p.x,p.y);
    }

}

void afficherRoulotteG(ListD_circ accessoire_roulotte){
    MLV_Font* r_fond = MLV_load_font( "font/Creepster-Regular.ttf",20);
    MaillonD* debut = accessoire_roulotte;

    int x = 150;
    int y = 60;
    int index = 0;
    Point zone_acc;
    // le fond
    MLV_draw_filled_rectangle(50,50,WINDOW_WIDTH-100,WINDOW_HEIGHT-100,MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(55,55,WINDOW_WIDTH-110,WINDOW_HEIGHT-110,MLV_COLOR_DARK_GRAY);
    MLV_Image* image = MLV_load_image("image/croix5.png");
    MLV_draw_image(image,850,47);
    MLV_draw_rectangle(860,55,87,88,MLV_COLOR_BLUE);

    do{
        if(index % 2 == 0 && index !=0){
            y += 310;
            x = 150;

        }
        MLV_draw_filled_rectangle(x,y,250,210,MLV_COLOR_BLACK);
        AccR* acc = (AccR*)accessoire_roulotte;
        MLV_draw_text_with_font(x,y,"Nom : ",r_fond,MLV_COLOR_WHITE);
        MLV_draw_text_with_font(x+50,y,acc->accessoire.nom,r_fond,MLV_COLOR_WHITE);
        afficherTexteFormate(x,y+30,"prix : %d",acc->accessoire.prix,r_fond,MLV_COLOR_WHITE);
        MLV_draw_text_with_font(x+30,y,"Or",r_fond,MLV_COLOR_WHITE);

        afficherTexteFormate(x,y+60,"attbonus : %d ",acc->accessoire.attbonus,r_fond,MLV_COLOR_WHITE);
        afficherTexteFormate(x,y+90,"defbonus : %d ",acc->accessoire.defbonus,r_fond,MLV_COLOR_WHITE);
        afficherTexteFormate(x,y+120,"HPbonus : %d",acc->accessoire.HPbonus,r_fond,MLV_COLOR_WHITE);
        afficherTexteFormate(x,y+150,"restbonus : %d",acc->accessoire.restbonus,r_fond,MLV_COLOR_WHITE);
        afficherTexteFormate(x,y+180,"strred : %d",acc->accessoire.strred,r_fond,MLV_COLOR_WHITE);
        MLV_draw_filled_rectangle(x+80,y+215,100,30,MLV_COLOR_BLUE);
        MLV_draw_text_with_font(x+100,y+220,"ACHETEZ",r_fond,MLV_COLOR_WHITE);
        zone_acc.x = x+80;
        zone_acc.y = y+215;
        acc->accessoire.zone_roulotte = zone_acc;
        x+=400;
        accessoire_roulotte = accessoire_roulotte->next;
        index++;
    }while(accessoire_roulotte != debut);
    MLV_actualise_window();
    MLV_wait_seconds(2);
    // MLV_free_font(r_fond);

}




