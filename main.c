#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <MLV/MLV_all.h>

#include "donnee.h"
#include "game.h"
#include "sauvegarde.h"
#include "master.h"
#include "graphics.h"




Param gererParam(int argc,char** argv){
    Param param = {ASCII,"save.txt",""};
    if(argc == 1){
        printf("pas de parametre\n");
    }else{
        for(int i = 0;i<argc;i++){
            if(!strcmp(*(argv+i),"-g"))param.aff = GRAPHICS;
            if(!strcmp(*(argv+i),"-a"))param.aff = ASCII;

            if(!strcmp(*(argv+i),"-s")){
                if( i+1 < argc && strcmp(&argv[i+1][0],"-") != 0){
                    if(!strcmp(*argv+i+1,"save.txt") || !strcmp(*argv+i+1,""))param.fichier_sauvegarde = "save.txt";
                    else param.fichier_sauvegarde = *(argv+i+1);
                }
                
            }
            if(!strcmp(*(argv+i),"-c")){
                if( i+1 < argc && strcmp(&argv[i+1][0],"-") != 0){
                    if(!strcmp(*argv+i+1,"save.txt"))param.fichier_chargement = "save.txt";
                    else param.fichier_chargement = *(argv+i+1);
                }
            }
        }
    }
    return param;
}

void wrapperSauvegarderPartie(void* data) {
    Execute* execute = (Execute*)data;
    if (execute) {
        int res = sauvegarderPartie(execute->liste, *(execute->joueur), execute->fichier, execute->fichier_sauvegarde);
        if(res == -1)return;

    }
    
}

Execute* initialiserExecute(Type_Liste*liste,Joueur* joueur,FILE**fichier,char*fichier_sauvegarde,char* fichier_chargement){
    Execute* execute = (Execute*)malloc(sizeof(Execute));
    if(!execute)return NULL;
    execute->liste = liste;
    execute->joueur = joueur;
    execute->fichier = fichier;
    execute->fichier_sauvegarde = fichier_sauvegarde;
    execute->fichier_chargement = fichier_chargement;
    if(joueur->niveau == 0)
        execute->sauvegarde_milieu = 0;
    else
        execute->sauvegarde_milieu = 1;

    return execute;

}

int main(int argc,char** argv){
    srand(time(NULL));

    // listes chainee
    Type_Liste *liste = initialiser_liste();
    FILE* fichier = NULL;
    Joueur* joueur;
    Execute* execute;

    Param param = gererParam(argc,argv);
    mainMaster(liste,param);

    if(*param.fichier_chargement != '\0'){
        int res = lancerSauvegarde(liste,&fichier,param.fichier_chargement,&joueur);
        if(res == -1){
            fprintf(stderr,"erreur de fichier\n");
            return -1;
        }
    }
    else{
        joueur = initialiserJoueur(param.aff);

    }
        
    execute = initialiserExecute(liste,joueur,&fichier,param.fichier_sauvegarde,param.fichier_chargement);

    printf("bienvenue dans le jeu  %s\n",joueur->nom);

    if(param.aff == GRAPHICS){
     
        
        // MLV_execute_at_exit(wrapperSauvegarderPartie,(void*)execute);
        
        initialiserFenetre();
    }
    mainGame(liste,param.aff,joueur,execute);
    
    int res = sauvegarderPartie(liste,*joueur,&fichier,param.fichier_sauvegarde);
    if(res == -1){
        fprintf(stderr,"erreur de fichier\n");
        return -1;

    }
    if(param.aff == GRAPHICS){
        MLV_wait_seconds(2);
        MLV_free_window();
    }
    
    LibererTypeListe(liste);
    libererJoueur(joueur);
    if(execute)
        free(execute);
    return 0;
}
