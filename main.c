/**
 * @file main.c
 * @brief Programme principal pour le TP 10 de SDA1
 * @author nsalez
 * @version 0.1
 * @date 22/04/2018
 * @todo PArtie 3 :  afficher les commandes, les factures d'un client, faire toutes les factures des clients
 */

#include "./include/calculerCA.h"
//#define __DEBUG__


//Pour créerCOmmande
typedef struct {
    int code;
    int quantite;
}T_Stock;

typedef struct {
    int nbProduits;
    T_Stock listeStock[14];
}T_StockTotal;

typedef enum {disponible,nonDisponible}T_EtatProduit;


int afficherMenuParties();
int afficherMenuPartie3();

void viderBuffer();

short afficherStock(T_EtatProduit etat);
void creerCommande(char *nomClient, int* nombreVentes);
T_StockTotal getStockTotal(FILE * fStock,int maxLigneStock);
void setStockTotal(T_StockTotal stockTotal);
short enleverQuantiteStock(int code, int quantiteChoisie);
void chercherCommandesClient(char *nomClient);

int main() {
    int choixPartie,choixPartie3,nombreVentes;
    FILE *fProduits=fopen("./files/produits.txt","r");
    FILE *fVentes,*fFacture;
    float totalCumule;
    char cheminFichierVente[MAXCAR];
    char cheminFichierFacture[MAXCAR];
    char nomClient[MAXCAR];


    fprintf(stdout,"\n-----------------------------------\nBienvenue dans le programme du TP 10.\n-----------------------------------\n");
    do {
        DIR * rep = opendir("./files");
        choixPartie = afficherMenuParties();
        totalCumule=0;
        switch(choixPartie) {
            // Partie 1
            case 1 : fVentes=fopen("./files/ventes.txt","r");
                     if( fVentes && fProduits ) {
                         calculerCAPartie1(fProduits,fVentes);
                     }
                     else {
                         fprintf(stderr,"\n Erreur lors de l'ouverture des fichiers.");
                     }
                     fclose(fVentes);
                     break;

            // Partie 2
            case 2 : if (rep != NULL) {
                        fprintf(stdout," Quel est le nom du client (MAJUSCULES SVP) ? ");
                        scanf("%s",nomClient);
                        strcpy(cheminFichierFacture,"./files/factures/facture");
                        strcat(cheminFichierFacture,nomClient);
                        strcat(cheminFichierFacture,".txt");
                        remove(cheminFichierFacture);
                        struct dirent * ent;

                        while ( (ent = readdir(rep)) != NULL) {
#ifdef __DEBUG__
                            fprintf(stdout,"%s\n", ent->d_name);
#endif
                            if (strstr(ent->d_name,"ventes") !=NULL) {
                                strcpy(cheminFichierVente,"./files/");
                                strcat(cheminFichierVente,ent->d_name);
#ifdef __DEBUG__
                                fprintf(stdout," ------>c est un fichier vente !\n\n");
                                fprintf(stdout," On veut ouvrir le fichier dont le chemin est %s\n",cheminFichierVente);
#endif
                                fVentes=fopen(cheminFichierVente,"r");
                                if( fVentes && fProduits && filestr(fVentes,nomClient) ) {
#ifdef __DEBUG__
                                    fprintf(stdout," main - partie 2 - La chaine '%s' a été trouvé dans le fichier.\n",nomClient);
#endif
                                    calculerCAPartie2(fProduits,fVentes,cheminFichierFacture,&totalCumule,nomClient);
                                }
                                fclose(fVentes);
                            }
                        }

                        fFacture=fopen(cheminFichierFacture,"a");
                        if( fFacture ) {
                            fprintf(fFacture,"\n\t\tCoût total cumulé des factures : %.2f", totalCumule);
                        }
                        fclose(fFacture);
                }
                break;

            // Partie 3
            case 3 :
                do {
                    nombreVentes=filesearch("./files","ventes");
                    choixPartie3 = afficherMenuPartie3();
                    totalCumule = 0;

                    switch (choixPartie3) {
                        // On veut créer une nouvelle commande : on affiche le stock disponible
                        case 1 :
                            fprintf(stdout, " Nom du client ? ");
                            fscanf(stdin, "%s", nomClient);
                            creerCommande(nomClient,&nombreVentes);
                            break;

                        // Créer la facture d'un client, on demande son nom :
                        case 2 :
                            fprintf(stdout," Nom du client ?");
                            fscanf(stdin,"%s", nomClient);
                            strcpy(cheminFichierFacture,"./files/factures/facture");
                            strcat(cheminFichierFacture,nomClient);
                            strcat(cheminFichierFacture,".txt");
                            remove(cheminFichierFacture);
                            struct dirent * ent;

                            while ( (ent = readdir(rep)) != NULL) {
#ifdef __DEBUG__
                                fprintf(stdout,"%s\n", ent->d_name);
#endif
                                if (strstr(ent->d_name,"ventes") !=NULL) {
                                    strcpy(cheminFichierVente,"./files/");
                                    strcat(cheminFichierVente,ent->d_name);
#ifdef __DEBUG__
                                    fprintf(stdout," ------>c est un fichier vente !\n\n");
                                    fprintf(stdout," On veut ouvrir le fichier dont le chemin est %s\n",cheminFichierVente);
#endif
                                    fVentes=fopen(cheminFichierVente,"r");
                                    if( fVentes && fProduits && filestr(fVentes,nomClient) ) {
#ifdef __DEBUG__
                                        fprintf(stdout," main - partie 2 - La chaine '%s' a été trouvé dans le fichier.\n",nomClient);
#endif
                                        calculerCAPartie2(fProduits,fVentes,cheminFichierFacture,&totalCumule,nomClient);
                                    }
                                    fclose(fVentes);
                                }
                            }

                            fFacture=fopen(cheminFichierFacture,"a");
                            if( fFacture ) {
                                fprintf(fFacture,"\n\t\tCoût total cumulé des factures : %.2f", totalCumule);
                            }
                            fclose(fFacture);
                            break;

                            //Donner les noms de fichiers des commandes du client
                        case 3 :
                            fprintf(stdout, " Nom du client ? ");
                            fscanf(stdin, "%s", nomClient);
                            chercherCommandesClient(nomClient);
                            break;

                        case 4 :
                            if (!afficherStock(disponible))
                                fprintf(stderr, " Problème d'affichage des fichiers stock.txt/produits.txt\n");
                            break;

                        case 5 :
                            if (!afficherStock(nonDisponible))
                                fprintf(stderr, " Problème d'affichage des fichiers stock.txt/produits.txt\n");
                            break;


                        default:
                            choixPartie3 = 0;
                    }

                }while(choixPartie3!=0);
            break;


            //Test de filesearch
            case 5 :
                fprintf(stdout," Nombre de fichiers ventes : %d\n",filesearch("./files","ventes") );
                break;

            default : choixPartie=0;
                      break;
        }
        closedir(rep);
    }while(choixPartie!=0);
    fclose(fProduits);
    return 0;
}


int afficherMenuParties() {
    int choix;
    fprintf(stdout,"\n\t1 : Elaboration de facture.txt à partir de la liste des produits et de ventes.txt");
    fprintf(stdout,"\n\t2 : Elaboration de la facture d'un client à partir de plusieurs ventes.");
    fprintf(stdout,"\n\t3 : Menu de la partie 3.");
    fprintf(stdout,"\n\t0 : Quitter le programme.");
    fprintf(stdout,"\n Quelle partie voulez-vous tester ? ");
    scanf("%d",&choix);
    viderBuffer();
    return choix;
}

void viderBuffer() {
    int c=0;
    while(c!='\n'&&c!=EOF)	c=getchar();
}


int afficherMenuPartie3() {
    int choix;
    fprintf(stdout,"\n\t1 : Saisir une nouvelle commande");
    fprintf(stdout,"\n\t2 : Créer la facture d'un client");
    fprintf(stdout,"\n\t3 : Lister les commandes d'un client");
    fprintf(stdout,"\n\t4 : Afficher le stock disponible");
    fprintf(stdout,"\n\t5 : Afficher les produits en rupture de stock");
    fprintf(stdout,"\n\t0 : Revenir au menu précédent.");
    fprintf(stdout,"\n Quelle fonction voulez-vous tester ? ");
    scanf("%d",&choix);
    viderBuffer();
    return choix;
}


short afficherStock(T_EtatProduit etat) {
    FILE *fStock =fopen("./files/stock.txt","r");
    FILE *fProduits = fopen("./files/produits.txt","r");

    if( fStock && fProduits ) {
        int maxLignesStock = filelines(fStock);
        int maxLignesProduits = filelines(fProduits);
        T_Produit produitEnStock;

        fprintf(stdout,"-------------------------------------------------\n");
        int numeroLigneProduits=1;

        short ETATNONDISPONIBLE=0;
        if( etat == nonDisponible)
            ETATNONDISPONIBLE=1;


        for(int numeroLigneStock=1;numeroLigneStock<maxLignesStock+1+ETATNONDISPONIBLE;numeroLigneStock++) {
            fscanf(fStock,"%d %d",&(produitEnStock.code),&(produitEnStock.stock));
            short produitTrouve=FALSE;

            while( numeroLigneProduits != maxLignesProduits+1 && produitTrouve != TRUE ) {
                    T_Produit produitActuel;
                fscanf(fProduits,"%d %s %f",&(produitActuel.code),produitActuel.nom,&(produitActuel.prix));
#ifdef __DEBUG__
                fprintf(stdout," Debug - code %d : produitActuel.code = %d & produitEnStock = %d\n",produitEnStock.code,produitActuel.code,produitEnStock.code);
#endif
                switch(etat) {
                    case disponible :
                        if( produitActuel.code == produitEnStock.code ) {
                            produitActuel.stock=produitEnStock.stock;
                            fprintf(stdout,"Produit trouvé : code %d - nom %s - prix %.2f - stock disponible : %d\n",produitActuel.code,produitActuel.nom,produitActuel.prix,produitActuel.stock);
                            produitTrouve = TRUE;
                        }
                        break;

                    case nonDisponible :
                        if( produitActuel.code != produitEnStock.code) {
                            fprintf(stdout,"Rupture de stock : code %d - nom %s - prix %.2f\n",produitActuel.code,produitActuel.nom,produitActuel.prix);
                        }
                        else {
#ifdef __DEBUG__
                            fprintf(stdout," Debug - code %d :produitActuel == produitEnStock\n",produitEnStock.code);
#endif
                            produitTrouve=TRUE;
                        }
                        break;

                    default : fprintf(stderr," Problème d'utilisation de la fonction afficherStock \n");
                }


                numeroLigneProduits++;
            }
        }
        fprintf(stdout,"-------------------------------------------------\n");
        return 1;
    }
    else return FALSE;
}



void creerCommande(char *nomClient, int* nombreVentes) {
    char cheminFichierVente[MAXCAR]="./files/ventes";
    char buffer[5];
    sprintf(buffer,"%03d.txt",*nombreVentes);
    strcat(cheminFichierVente,buffer);
    fprintf(stdout," Chemin du fichier vente : %s && nomCLient = %s",cheminFichierVente,nomClient);

    FILE *fVente = fopen(cheminFichierVente,"w");
    if ( fVente ) {
        // On écrit la 1ere ligne
        fprintf(fVente,"%s",nomClient);

        FILE *fProduits = fopen("./files/produits.txt","r");
        if (fProduits) {
            int maxLigneProduits = filelines(fProduits);
            for(int ligneProduit=1; ligneProduit<maxLigneProduits+1;ligneProduit++) {
                T_Produit produitActuel;
                int quantiteChoisie;
                fscanf(fProduits,"%d %s %f",&(produitActuel.code),produitActuel.nom,&(produitActuel.prix));

                ecritureCommande:
                fprintf(stdout," Produit %d - %s - prix : %.2f\n",produitActuel.code,produitActuel.nom,produitActuel.prix);
                fprintf(stdout," Quantité ? (Tapez -1 pour quitter la commande) : ");
                viderBuffer();
                fscanf(stdin,"%d",&quantiteChoisie);
#ifdef __DEBUG__
                fprintf(stdout," Debug - quantité choisie : %d\n",quantiteChoisie);
#endif
                if( quantiteChoisie != -1 ) {
                    if (quantiteChoisie != 0) {
                        if (enleverQuantiteStock(produitActuel.code, quantiteChoisie)) {
                            fprintf(fVente, "\n%d %d", produitActuel.code, quantiteChoisie);
                        }
                        else {
                            fprintf(stdout, " Pas assez de stock pour ce produit. Veuillez recommencer.\n");
                            goto ecritureCommande;
                        }
                    }
                    else
                        continue;      // L'utilisateur veut passer au produit suivante
                }
                // L'utilisateur veut arreter la commande
                else
                    break;

            }

            fclose(fProduits);
        }
        fclose(fVente);
        //On n'oublie pas d'incrémenter le nombre de ventes
        (*nombreVentes)++;
    }

}


short enleverQuantiteStock(int code, int quantiteChoisie) {
   FILE *fStock=fopen("./files/stock.txt","r");

   if( fStock ) {
       int maxLigneStock=filelines(fStock);
       short trouve=FALSE;
       T_StockTotal stockTotal=getStockTotal(fStock,maxLigneStock);
       fclose(fStock);


       int i=0;
       //On cherche le code dans la structure
       while( i<stockTotal.nbProduits && stockTotal.listeStock[i].code != code) {
           i++;
       }
       // Si on a trouvé le code
       if(stockTotal.listeStock[i].code == code) {

          //On soustrait la quantité actuelle avec la quantité choisie si cette dernière est raisonnable
          if( stockTotal.listeStock[i].quantite - quantiteChoisie >= 0) {
              stockTotal.listeStock[i].quantite -= quantiteChoisie;
              // On réécrit le stock dans le fichier stock.txt
              setStockTotal(stockTotal);
              return TRUE;
          }

          else
              return FALSE;     //La quantité est trop importante.
       }
       else
           return FALSE;        //Le code n'a pas été trouvé.
   }
   else
       return FALSE;            //Le fichier n'a pas pu être ouvert.
}

T_StockTotal getStockTotal(FILE * fStock,int maxLigneStock) {
    T_StockTotal stockTotal;
    stockTotal.nbProduits=maxLigneStock;
    rewind(fStock);
    for(int ligneActuelleStock=1; ligneActuelleStock<maxLigneStock+1;ligneActuelleStock++) {
        fscanf(fStock,"%d %d",&(stockTotal.listeStock[ligneActuelleStock-1].code),&(stockTotal.listeStock[ligneActuelleStock-1].quantite));
    }
    rewind(fStock);
    return stockTotal;
}

void setStockTotal(T_StockTotal stockTotal) {
    FILE *fStock=fopen("./files/stock.txt","w");
    if( fStock ) {
        for(int i=0;i<stockTotal.nbProduits;i++) {
            //On ne met pas les produits qui ne sont plus en stock !
            if( stockTotal.listeStock[i].quantite != 0)
                fprintf(fStock,"\n%d %d",stockTotal.listeStock[i].code,stockTotal.listeStock[i].quantite);
        }
        fclose(fStock);
    }
}


void chercherCommandesClient(char *nomClient) {
    //On travaille dans le répertoire ./files pour trouver les fichiers ventesXXX.txt où se trouvent <nomCLient>
    DIR *rep = opendir("./files");
    if (rep != NULL) {
        struct dirent *ent;
        fprintf(stdout,"\n Les fichiers des commandes du client sont les suivants :\n");
        while ((ent = readdir(rep)) != NULL) {
            if (strstr(ent->d_name,"ventes") != NULL) {
                char cheminFichier[MAXCAR]="./files/";
                strcat(cheminFichier,ent->d_name);
                FILE *fActuel = fopen(cheminFichier,"r");
                if( fActuel ) {
                    if( filestr(fActuel,nomClient) ) {
                        fprintf(stdout,"- %s\n",ent->d_name);
                    }
                }
            }

        }
        closedir(rep);
    }
}
