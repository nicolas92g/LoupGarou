#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TTRB 18
#define MORT -1
#define VRAI 1
#define FAUX 0

int* initTab(int tab[], int taille, int a);
int* initTab2(int tab[], int taille, int a);
void afficherTableau(int tab[], int taille);
void echangeCase(int tab[], int a, int b);
int* copieTab(int tabA[], int tabB[], int taille);
int voteSolo(int tabJoueur[], int nJoueur);