#ifndef __CALCULERCA__
#define __CALCULERCA__

#include "libfichier.h"
#define MAXCAR 100
typedef struct {
    int codeProduit;
    int nbProduits;
}T_Vente;

typedef struct {
    int code;
    int stock;
    char nom[MAXCAR];
    float prix;
}T_Produit;


void calculerCAPartie1(FILE *fProduits, FILE* fVentes);
void calculerCAPartie2(FILE *fProduits, FILE* fVentes,char *cheminFichierFacture,float *totalCumule,char *nomClient);

#endif
