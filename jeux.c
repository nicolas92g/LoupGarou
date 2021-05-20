#include "jeux.h"
#include "fonction.h"

void attribution(Role* tabRoles, unsigned short nbrDeJoueurs) {
	int caseRoleAlea = 0;
	int flecheJoueur = nbrDeJoueurs - 1;
	int flecheRole = 0;
	int joueurAlea = 0;
	int roleAlea = 0;

	//ALea
	time_t t;
	srand((unsigned)time(&t));

	///Voyante
	int caseJoueurAlea = rand() % (flecheJoueur + 1);
	int tabAttributionJoueur[18];
	initTab2(tabAttributionJoueur, nbrDeJoueurs, 0);
	joueurAlea = tabAttributionJoueur[caseJoueurAlea];

	tabJoueur[joueurAlea] = ivoyante;
	echangeCase(tabAttributionJoueur, caseJoueurAlea, flecheJoueur);
	flecheJoueur = flecheJoueur - 1;

	///LoupGarou
	for (int i = 0; i < nLoupgarou; i++)
	{
		caseJoueurAlea = rand() % (flecheJoueur + 1);
		joueurAlea = tabAttributionJoueur[caseJoueurAlea];

		tabJoueur[joueurAlea] = iloupgarou1 + i;
		echangeCase(tabAttributionJoueur, caseJoueurAlea, flecheJoueur);
		flecheJoueur = flecheJoueur - 1;
	}

	///Reste

	flecheRole = TTRB - 1;
	while (flecheJoueur > 0) {
		caseJoueurAlea = rand() % (flecheJoueur + 1);
		caseRoleAlea = rand() % (flecheRole + 1);
		joueurAlea = tabAttributionJoueur[caseJoueurAlea];
		roleAlea = tabAttributionRole[caseRoleAlea];

		tabJoueur[joueurAlea] = roleAlea;
		tabRole[roleAlea] = joueurAlea;
		echangeCase(tabAttributionJoueur, caseJoueurAlea, flecheJoueur);
		echangeCase(tabAttributionRole, caseRoleAlea, flecheRole);

		flecheJoueur = flecheJoueur - 1;
		flecheRole = flecheRole - 1;
	}
	caseJoueurAlea = 0;
	caseRoleAlea = rand() % (flecheRole + 1);
	joueurAlea = tabAttributionJoueur[caseJoueurAlea];
	roleAlea = tabAttributionRole[caseRoleAlea];

	tabJoueur[joueurAlea] = roleAlea;
	tabRole[roleAlea] = joueurAlea;
}
