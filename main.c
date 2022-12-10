#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArbreLexico.h"

	ArbreLex Arbl;
	int existe=0;
	char mot[25];						//mot 
	int pointjoueur1=0,pointjoueur2=0;
	int NumManche=0;
	char manchesuivante;
	int manchevainqueur=0; //détermine le vainqueur d'une manche


void main(int argc, char *argv[]){
    Arbl=CreerArbreLexico();
    Arbl=CreerDictionnaire(Arbl);
    //AfficheArbre(Arbl);				Si vous voulez affiché le contenu de l'arbre (Tout les mots à l'intérieur)
    
    printf("\n!!!! JEU DU MOT LE PLUS LONG PAR SANI Abdou-Rahmane et EDDEROUICH Abdesamad !!!!\n");
    printf("\nPrésentateur : Le premier joueur à gagner 5 points remporte la partie. Prêt ? C'est parti !!! \n");
	printf("\nAppyer sur entrée pour commencer\n");
	
	//MANCHE 1
	scanf("%c",&manchesuivante);
	printf("\nDébut de la manche 1\n");
	if (manchesuivante='\n'){			
		manchevainqueur=Manche(Arbl);
		if(manchevainqueur==1){
			pointjoueur1++;
		}
		if(manchevainqueur==2){
			pointjoueur2++;
		}
	}									
	//MANCHE 2
	printf("\nDébut de la manche 2\n");			
	if (manchesuivante='\n'){			
		manchevainqueur=Manche(Arbl);
		if(manchevainqueur==1){
			pointjoueur1++;
		}
		if(manchevainqueur==2){
			pointjoueur2++;
		}
	}									
	//MANCHE 3
	printf("\nDébut de la manche 3\n");			
	if (manchesuivante='\n'){			
		manchevainqueur=Manche(Arbl);
		if(manchevainqueur==1){
			pointjoueur1++;
		}
		if(manchevainqueur==2){
			pointjoueur2++;
		}
	}
	//CHECK DU VAINQUEUR
	if(pointjoueur1>pointjoueur2){
		printf("\nLe joueur 1 remporte la partie, Félicitations, Vous remportez 0 euros !!!\n");
	}
	if(pointjoueur1<pointjoueur2){
		printf("\nLe joueur 2 remporte la partie, Félicitations, Vous remportez 0 euros !!!\n");
	}
	if(pointjoueur1==pointjoueur2){
		printf("\nEgalité dans cette partie !!!\n");
	}
	free(Arbl);											
}