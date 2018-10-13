#include "../include/libfichier.h"

//#define __DEBUG__libfichier__

#define initCursorFile() rewind(fic)

// Pour afficher un fichier
void fileprintf(FILE *fic) {
	int caractere;
	if(fic != NULL) {
		caractere = fgetc(fic);
		while( caractere != EOF ) {
			fputc(caractere,stdout);
			caractere = fgetc(fic);
			}
		fclose(fic);
		}
	else {
		fprintf(stderr,"\nfileprintf : impossible d'ouvrir le fichier.\n"); 
		}
}


// Pour copier le contenu d'un fichier dans un autre.
int filecopy(FILE *ficdest,FILE *ficsrc) {
	int c=64;
	if(ficdest != NULL && ficsrc != NULL ) {
		while (c != EOF) {
			c = fgetc(ficsrc); 
			if( c != EOF ) fputc(c,ficdest);
			}
		return TRUE; 
		}
	else 
		return FALSE;	
}


// Pour connaître le nombre de lignes d'un fichier.
int filelines(FILE *fic) {
	initCursorFile();
	int c=64;
	int nbLigne=0;
	if(fic != NULL) {
		while (c != EOF) {
			c=fgetc(fic);
			if( c == '\n' )
				nbLigne++;
			}
		initCursorFile();
		return nbLigne;
		}
	else
		return FALSE;
}

	
int filestr(FILE *fic,char *string) {
#ifdef __DEBUG__libfichier__
	fprintf(stdout,"filesearch - entrée dans la fonction.\n");
#endif
	int c='a';
	int trouve=FALSE;
	size_t taille=strlen(string)-1;
	initCursorFile();

	while ( c != EOF && !trouve) {
		c=fgetc(fic);
		if(c == string[0]) {
			int i=0;
			while ( c != EOF && i!=taille && c==string[i] ) {
				c=fgetc(fic);
				i++;
			}
			if( i == taille ) {
#ifdef __DEBUG__libfichier__
				fprintf(stdout,"filesearch - La chaîne '%s' est contenue dans le fichier.\n.",string);
#endif
				trouve = TRUE;
			}
		}
	}
	initCursorFile();
	return trouve;
}


int filesearch(char * cheminRepertoire, char* titre) {
    struct dirent *ent;
    int nombreFichiers=0;
    DIR *rep = opendir(cheminRepertoire);
    if (rep != NULL) {
        while ((ent = readdir(rep)) != NULL) {
            if (strstr(ent->d_name, titre) != NULL) {
                nombreFichiers++;
#ifdef __DEBUG__libfichier__
                fprintf(stdout, " Fichier : %s - correspondance avec le titre.\n",ent->d_name);
#endif
            }

        }
    }
    closedir(rep);
    return nombreFichiers;
}


