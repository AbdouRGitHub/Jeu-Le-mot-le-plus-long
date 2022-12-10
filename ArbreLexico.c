#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ArbreLexico.h"

//CREATION ArbreLexicographique
ArbreLex CreerDictionnaire(ArbreLex ArbreDico){
    ArbreLex ArbreRetour = ArbreDico;     //mémoire tempon pour revenir à la première lettre (Buffer)
    ArbreLex ArbreLexico = ArbreDico;   //mémoire qui sert à revenir au début de chaque mot
    FILE *dico = NULL;     //fichier contenant le dictionnaire
    char lettreDico=0;    //variable contenant une lettre du dictionnaire
    int nbMot=0;
    if((dico=fopen("dictionnaire.txt","r"))!=NULL){ //la variable dico contient les données du fichier dictionnaire
        while ((lettreDico=fgetc(dico)) != EOF){   //Tant que le fichier n'est pas vide (Incrémentaion à chaque fcget dans le fichier)        
          if((lettreDico=='\n') || (lettreDico==' ')){
                ArbreLexico=ArbreRetour;
                ArbreLexico->suivant=CreerArbreLexico();
                ArbreLexico=ArbreLexico->suivant;
                ArbreRetour=ArbreLexico;              //Il enregistre sa dernière postion dans l'arbre avant remplissage d'un nouvea mot
                nbMot++;
            }else{
                ArbreLexico->lettre=lettreDico;
                ArbreLexico->suffixe=CreerArbreLexico();
                ArbreLexico=ArbreLexico->suffixe;
            }
        }
    }else{
        printf("Dictionnaire non existant ou vide");
        fclose(dico);
    }

    printf("\nnombre de mot:%d \n",nbMot);
    fclose(dico);
    printf("Dictionnaire créer avec succès\n");
    return ArbreDico;
}

ArbreLex queue(ArbreLex L){
    return(L->suivant);
}

ArbreLex queueSuffixe(ArbreLex L){
    return(L->suffixe);
}

//AFFICHAGE Arbre
void AfficheArbre(ArbreLex L) {
    ArbreLex P = L;
    ArbreLex Pbis = L;              //mémoire tempon pour revenir à la première lettre
    while(P != NULL){
        if(P->suffixe!=NULL){
            printf("%c",P->lettre);
            P=queueSuffixe(P);
        }else{
            printf("%c\n",P->lettre);
            P=Pbis;
            P=queue(P);
            Pbis=P;
        }
    }
    printf("Arbre affiché \n");
}

ArbreLex CreerArbreLexico(){            //Création du dictionnaire (mise en place des données)
    ArbreLex L=malloc(sizeof(ArbreLex));
    L->lettre='\0';
    L->suffixe=NULL;
    L->suivant=NULL;
    return L;
}

int RechercheDictionnaire(ArbreLex Arbl,char mot[], int cpt){
    int existe=0;
    int i=0;
    ArbreLex P=Arbl;
    ArbreLex Pbis=Arbl;     //mémoire tempon pour revenir à la première lettre
    while (P!=NULL){
        if((P->lettre==mot[i]) && (i<cpt+1)){
            P=queueSuffixe(P);
            i++;
            if((P->lettre==mot[i]) && (i==cpt+1)){
                return 1; 
            }
        }else{
            P=Pbis;
            P=queue(P);
            Pbis=P;
            i=0;
        }
    }
    return 0;
}

int Manche(ArbreLex Arbl){
    srand(time(NULL));
    int pointjoueur1=0;         //point des joueurs 1 
    int pointjoueur2=0;         //point des joueurs 2
    char lettrealeatoire[7];
    char lettrealeatoireconsomne[]={"bcdfghjklmnpqrstvwxz"};    //consomne aléatoire
    char lettrealeatoirevoyelle[]={"aeiouy"};                   //voyelle aléatoire
    char saisieJoueur1[25];     //réponse du joueur 1 
    char saisieJoueur2[25];     //réponse du joueur 2

        for(int j=0;j<4;j++){
            lettrealeatoire[j]=lettrealeatoireconsomne[rand()%20];
            for(int i=0; i<j+1;i++){              //Permet la suppresion des doublons 
                if(lettrealeatoire[j]==lettrealeatoire[i]){
                    lettrealeatoire[j]=lettrealeatoireconsomne[rand()%20];
                }
            }
        }
        for(int j=4;j<7;j++){
            lettrealeatoire[j]=lettrealeatoirevoyelle[rand()%6];
            for(int i=4; i<j+1;i++){              //Permet la suppresion des doublons 
                if(lettrealeatoire[j]==lettrealeatoire[i]){
                    lettrealeatoire[j]=lettrealeatoirevoyelle[rand()%6];
                }
            }
        }

        printf("\nPrésentateur : Les lettres a utilisés sont %c, %c, %c, %c, %c, %c et %c \n",lettrealeatoire[0],lettrealeatoire[1],
            lettrealeatoire[2],lettrealeatoire[3],lettrealeatoire[4],lettrealeatoire[5],lettrealeatoire[6]);

        printf("\nPrésentateur : Joueur 1, choisissez un mot le plus long \n");
        scanf("%s",saisieJoueur1);                                                                                        //SAISIE DU JOUEUR 1
            if(RechercheDictionnaire(Arbl,saisieJoueur1,strlen(saisieJoueur1)-1)==1){
                printf("\nPrésentateur : Merci joueur 1\n");
            }else{
                printf("\nPrésentateur : le mot n'existe pas dans le dictionnaire\n");
                saisieJoueur1[0]='\0';
            }
        
        printf("\nPrésentateur : Joueur 2, choisissez un mot le plus long \n");
        scanf("%s",saisieJoueur2);
            if(RechercheDictionnaire(Arbl,saisieJoueur2,strlen(saisieJoueur2)-1)==1){
                printf("\nPrésentateur : Merci joueur 2\n");
            }else{
                printf("\nPrésentateur : le mot n'existe pas dans le dictionnaire\n");
                saisieJoueur2[0]='\0';
            }

        if(strlen(saisieJoueur1)>strlen(saisieJoueur2)){
            printf("\nPrésentateur : le joueur 1 remporte la manche\n");
            return 1;
        }
        if(strlen(saisieJoueur1)<strlen(saisieJoueur2)){
            printf("\nPrésentateur : Le joueur 2 remporte la manche\n");
            return 2;
        }
        if(strlen(saisieJoueur1)==strlen(saisieJoueur2)){
            printf("\nPrésentateur : Egalité dans cette manche\n");
            return 3;
        }
        free(Arbl);

}
