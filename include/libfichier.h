#ifndef __LIBFICHIER__
#define __LIBFICHIER__

#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define TRUE 1
#define FALSE 0

//Pour afficher un fichier
void fileprintf(FILE *);

//Pour copier le contenu d'un fichier dans un autre
int filecopy(FILE *ficdest, FILE *ficsrc);

//Pour compter le nombre de lignes dans un fichier
int filelines(FILE *);

//Pour rechercher une chaîne de caractères dans un fichier.
int filestr(FILE *,char *);


// Pour trouver le nombre de fichiers dont le titre contient la chaîne de caractère mis en paramètre.
int filesearch(char * cheminRepertoire, char* titre);


#endif
