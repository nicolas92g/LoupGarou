#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface.h"
#include "fonction.h"

void attribution(Role* tabRoles, unsigned short nbrDeJoueurs);
int voteCapitaine(GUI* input);
int voteFinDeTour(GUI* input, Role* tabRoles, unsigned short nbrDeJoueursEnVie, int caseCapitaine);
int fLoupgarou(GUI* input, Role* tabRoles, unsigned short nbrDeJoueurs, unsigned short nbrDeJoueursEnVie);
void fVoyante(GUI* input, Role* tabRoles);
