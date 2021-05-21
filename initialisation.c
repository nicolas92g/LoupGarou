#include "initialisation.h"

/*int initialisation(int tabJoueur[], int tabAttributionJoueur[], int tabAttributionRole[], int nJoueur) {
	
	////Assignement des roles

	if (nJoueur < 12) 
	{
		attribution(tabJoueur, tabRole, tabAttributionJoueur, tabAttributionRole, nJoueur, 2);
	}
	else 
	{
		attribution(tabJoueur, tabRole, tabAttributionJoueur, tabAttributionRole, nJoueur, 3);
	}

	//Annoncement des roles
	//annoncementRole(tabJoueur, nJoueur);
}

int attribution(int tabJoueur[], int tabRole[], int tabAttributionJoueur[], int tabAttributionRole[], int nJoueur, int nLoupgarou) {
	int caseJoueurAlea = 0;
	int caseRoleAlea = 0;
	int flecheJoueur = nJoueur - 1;
	int flecheRole = 0;
	int joueurAlea = 0;
	int roleAlea = 0;
	int j = 0;
	int i = 0;
	//ALea
	time_t t;
	srand((unsigned)time(&t));
	
	///Voyante
	caseJoueurAlea = rand() % (flecheJoueur + 1);
	joueurAlea = tabAttributionJoueur[caseJoueurAlea];

	tabJoueur[joueurAlea] = ivoyante;
	tabRole[ivoyante] = joueurAlea;
	echangeCase(tabAttributionJoueur, caseJoueurAlea, flecheJoueur);
	flecheJoueur = flecheJoueur - 1;
	
	///LoupGarou
	for (i = 0; i < nLoupgarou; i++)
	{
		caseJoueurAlea = rand() % (flecheJoueur + 1);
		joueurAlea = tabAttributionJoueur[caseJoueurAlea];

		tabJoueur[joueurAlea] = iloupgarou1 + i;
		tabRole[iloupgarou1 + i] = joueurAlea;
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
	

	afficherTableau(tabAttributionJoueur, nJoueur);
	afficherTableau(tabAttributionRole, TTRB);
	afficherTableau(tabJoueur, nJoueur);
	afficherTableau(tabRole, TTR);	
}

int annoncementRole(int tabJoueur[], int nJoueur) {
	int i;

	for (i = 0; i < nJoueur; i++)
	{
		printf("Role du joueur %d: ", i);
		switch (tabJoueur[i])
		{
		case iloupgarou1:
			printf("Loup Garou");
			break;

		case iloupgarou2:
			printf("Loup Garou");
			break;

		case iloupgarou3:
			printf("Loup Garou");
			break;

		case ivoyante:
			printf("Voyante");
			break;

		case icapitaine:
			printf("Maire");
			break;

		case icupidon:
			printf("Cupidon");
			break;

		case ichasseur:
			printf("Chasseur");
			break;

		case isorciere:
			printf("Sorciere");
			break;

		case ipetite_fille:
			printf("Petite fille");
			break;

		case ivoleur:
			printf("Voleur");
			break;

		case -1:
			printf("ERREUR");
			break;

		default:
			printf("Villageois");
		}
		printf(".\n");
	}
}/*/
