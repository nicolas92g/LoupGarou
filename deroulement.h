#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonction.h"
#include "role.h"

#define TTR 23 // TTR: Taille du TabRole
#define TTRB 18// TTR: Taille du la Seconde Parti duTabRole

#define MORT -1
#define VRAI 1
#define FAUX 0

int deroulement(int tabJoueur[], int tabJoueurInit[], int tabRole[], int tabVote[], int tabEgalite[], int tabAssignationRole[], int nJoueur, int nLoupgarou);
bool fPartiFini(int nLoupgarouEnVie, int nJoueurEnVie, bool finPart_i);
int fCoupleVie(int tabJoueur[], int tabCupidon[], bool coupleVie_i);
int capitaineMort(int tabJoueur[], int tabRole[], int caseCapitaine, int nJoueur);
int vote(int tabJoueur[], int tabVote[], int nJoueur);
int voteCapitaine(int tabJoueur[], int tabRole[], int tabVote[], int tabEgalite[], int nJoueur);
int voteMort(int tabJoueur[], int tabRole[], int tabVote[], int tabEgalite[], int nJoueur);


