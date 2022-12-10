#include <stdio.h>
#include <stdlib.h>


//Structure de l'arbre lexicographique

struct ArbreLex{
    char lettre;
    struct ArbreLex *suffixe;
    struct ArbreLex *suivant;    
};
typedef struct ArbreLex * ArbreLex;


ArbreLex CreerDictionnaire(ArbreLex reste);

ArbreLex queue(ArbreLex L);

ArbreLex queueSuffixe(ArbreLex L);

void AfficheArbre(ArbreLex L);

void lecturefichier();

ArbreLex CreerArbreLexico();

int RechercheDictionnaire(ArbreLex Arbl,char mot[],int cpt);

int Manche();

