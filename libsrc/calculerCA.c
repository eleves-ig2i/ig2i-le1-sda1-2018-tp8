#include "../include/calculerCA.h"



void calculerCAPartie1(FILE *fProduits, FILE* fVentes) {
    T_Vente vente={0,0};
    T_Produit produit={0,0,"",0};
    int nbLigneProduit=0,nbLigneVente=0;
    short produitSaute=FALSE;
    float totalVente=0;
    int maxLigneVente = filelines(fVentes);
    int maxLigneProduit = filelines(fProduits);
#ifdef __DEBUG__CA__
    fprintf(stdout,"\n fVentes : %d lignes - fProduits %d lignes\n",maxLigneVente,maxLigneProduit);
#endif

    FILE *fFacture=fopen("files/factures/facture.txt","w");

    if (fFacture != NULL) {
        fprintf(stdout," Chemin du fichier facture crée : ./files/factures/facture.txt\n");
        fprintf(fFacture, "Facture XXX\n\nListe des produits achetés :");

        // Tant qu'on a pas traité tout le fichier des ventes.
        T_Vente venteAnnexe={0,0};
        while(nbLigneVente < maxLigneVente+1) {


            if( produitSaute == FALSE) {
                fscanf(fVentes, "%d %d", &(vente.codeProduit), &(vente.nbProduits));
                nbLigneVente++;
            }
            else {
                vente=venteAnnexe;
                produitSaute=TRUE;
            }


            venteAnnexe.codeProduit=vente.codeProduit;
            venteAnnexe.nbProduits=0;

#ifdef __DEBUG__CA__
            printf(" Tant qu'on est sur le même produits dans fVentes (Départ : ligne %d)\n",nbLigneVente+1);
#endif
            //Tant qu'on est sur le même produit dans fVentes
            while( nbLigneVente < maxLigneVente+1 && vente.codeProduit == venteAnnexe.codeProduit){
                fscanf(fVentes, "%d %d", &(venteAnnexe.codeProduit), &(venteAnnexe.nbProduits));
#ifdef __DEBUG__CA__
                fprintf(stdout," Tant que PRODUIT : codeProduit = %d && nbProduits = %d (Ligne %d)\n",venteAnnexe.codeProduit,venteAnnexe.nbProduits,nbLigneVente+1);
#endif
                if( venteAnnexe.codeProduit == vente.codeProduit) {
#ifdef __DEBUG__CA__
                    fprintf(stdout," Tant que PRODUIT : produit présent plusieurs fois ! (Ligne %d)\n",nbLigneVente+1);
#endif
                    vente.nbProduits += venteAnnexe.nbProduits;
                }
                else {
#ifdef __DEBUG__CA__
                    fprintf(stdout," Tant que MEME PRODUIT : un produit a été sauté à la ligne %d !\n",nbLigneVente+1);
#endif
                    produitSaute=TRUE;
                }
                nbLigneVente++;
            }


            // On recherche le produit associé à la vente.
            while (nbLigneProduit != maxLigneProduit && produit.code != vente.codeProduit) {
                fscanf(fProduits, "%d %s %f", &(produit.code), produit.nom, &(produit.prix));
                nbLigneProduit++;
#ifdef __DEBUG__CA__
                printf(" TANT QUE VENTE : Ligne %d  : code = %d && nom = %s && prix = %f\n", nbLigneProduit, produit.code, produit.nom,
                       produit.prix);
#endif
            }
            // On écrit dans la facture
            fprintf(fFacture,
                    "\nproduit %d - intitulé : %s - nombre de ventes : %d - prix unitaire : %.2f - prix total : %.2f",
                    produit.code, produit.nom, vente.nbProduits, produit.prix, produit.prix * vente.nbProduits);
            totalVente += produit.prix * vente.nbProduits;
        }
        // On écrit le coût total
        fprintf(fFacture,"\n\nCoût total : %.2f",totalVente);
    }

}





void calculerCAPartie2(FILE *fProduits, FILE* fVentes,char *cheminFichierFacture,float *totalCumule,char *nomClient) {
    T_Vente vente = {0, 0};
    T_Produit produit = {0,0, "", 0};
    short produitSaute = FALSE;
    int nbLigneProduit = 0, nbLigneVente = 0;
    float totalVente = 0;
    int maxLigneVente = filelines(fVentes);
    int maxLigneProduit = filelines(fProduits);
#ifdef __DEBUG__CA__
    printf("\n fVentes : %d lignes - fProduits %d lignes", maxLigneVente, maxLigneProduit);
#endif

    fscanf(fVentes, "%s", produit.nom);



    FILE *fFacture = fopen(cheminFichierFacture, "a");

    if (fFacture != NULL) {
        fprintf(stdout," Chemin du fichier facture modifié : %s\n",cheminFichierFacture);
        fprintf(fFacture, "Facture XXX - Client : %s\n\nListe des produits achetés :", produit.nom);

        // Tant qu'on a pas traité tout le fichier des ventes.
        while (nbLigneVente != maxLigneVente + 1) {
            T_Vente venteAnnexe = {0, 0};
            while (nbLigneVente < maxLigneVente + 1) {


                if (produitSaute == FALSE) {
                    fscanf(fVentes, "%d %d", &(vente.codeProduit), &(vente.nbProduits));
                    nbLigneVente++;
                } else {
                    vente = venteAnnexe;
                    produitSaute = TRUE;
                }


                venteAnnexe.codeProduit = vente.codeProduit;
                venteAnnexe.nbProduits = 0;

#ifdef __DEBUG__CA__
                printf(" Tant qu'on est sur le même produits dans fVentes (Départ : ligne %d)\n", nbLigneVente + 1);
#endif
                //Tant qu'on est sur le même produit dans fVentes
                while (nbLigneVente < maxLigneVente + 1 && vente.codeProduit == venteAnnexe.codeProduit) {
                    fscanf(fVentes, "%d %d", &(venteAnnexe.codeProduit), &(venteAnnexe.nbProduits));
#ifdef __DEBUG__CA__
                    fprintf(stdout, " Tant que PRODUIT : codeProduit = %d && nbProduits = %d (Ligne %d)\n",
                            venteAnnexe.codeProduit, venteAnnexe.nbProduits, nbLigneVente + 1);
#endif
                    if (venteAnnexe.codeProduit == vente.codeProduit) {
#ifdef __DEBUG__CA__
                        fprintf(stdout, " Tant que PRODUIT : produit présent plusieurs fois ! (Ligne %d)\n",
                                nbLigneVente + 1);
#endif
                        vente.nbProduits += venteAnnexe.nbProduits;
                    } else {
#ifdef __DEBUG__CA__
                        fprintf(stdout, " Tant que MEME PRODUIT : un produit a été sauté à la ligne %d !\n",
                                nbLigneVente + 1);
#endif
                        produitSaute = TRUE;
                    }
                    nbLigneVente++;
                }


                // On recherche le produit associé à la vente.
                while (nbLigneProduit != maxLigneProduit && produit.code != vente.codeProduit) {
                    fscanf(fProduits, "%d %s %f", &(produit.code), produit.nom, &(produit.prix));
                    nbLigneProduit++;
                    //printf("\n Ligne %d  : code = %d && nom = %s && prix = %f", nbLigneProduit, produit.code, produit.nom,
                    //produit.prix);
                }
                // On écrit dans la facture
                fprintf(fFacture,
                        "\nproduit %d - intitulé : %s - nombre de ventes : %d - prix unitaire : %.2f - prix total : %.2f",
                        produit.code, produit.nom, vente.nbProduits, produit.prix, produit.prix * vente.nbProduits);
                totalVente += produit.prix * vente.nbProduits;
            }
            // On écrit le coût total
            fprintf(fFacture, "\n\nCoût total : %.2f\n-----------------------------------------------\n", totalVente);

            *totalCumule += totalVente;
            fclose(fFacture);
        }

    }
}

