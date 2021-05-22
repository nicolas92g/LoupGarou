#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface.h"
#include "fonction.h"
#include <assert.h>

void attribution(Role* tabRoles, unsigned short nbrDeJoueurs);
int voteCapitaine(GUI* input);
int voteFinDeTour(GUI* input, Role* tabRoles, unsigned short nbrDeJoueursEnVie, int caseCapitaine);
void fVoyante(GUI* input, Role* tabRoles);
int fLoupgarou(GUI* input, Role* tabRoles, unsigned short nbrDeJoueursEnVie);
void fCupidon(GUI* input, Role* tabRoles, unsigned short tabCupidon[]);
void fVoleur(GUI* input, Role* tabRoles);
void fSorciere(GUI* input, Role* tabRoles, bool peutTuer, bool peutSauver, short joueurTuee, unsigned short nbrDeJoueurEnVie);