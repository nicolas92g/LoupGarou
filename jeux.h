#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface.h"
#include "fonction.h"

void attribution(Role* tabRoles, unsigned short nbrDeJoueurs);
int voteFinDeTour(GUI* input, Role* tabRoles, unsigned short nbrDeJoueurs, unsigned short nbrDeJoueursEnVie, int caseCapitaine);
int fLoupgarou(GUI* input, Role* tabRoles, unsigned short nbrDeJoueurs, unsigned short nbrDeJoueursEnVie);