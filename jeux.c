#include "jeux.h"

void attribution(Role* tabRoles, unsigned short nbrDeJoueurs) {
	int caseRoleAlea = 0;
	int flecheJoueur = nbrDeJoueurs - 1;
	int flecheRole = 16;
	int joueurAlea = 0;
	int roleAlea = 0;
	int nLoupgarou = 0;
	int i;
	//Tab
	int tabAttributionJoueur[18];
	int tabAttributionRoles[17];
	//ALea
	time_t t;
	srand((unsigned)time(&t));
	//InitTab
	initTab2(tabAttributionJoueur, nbrDeJoueurs, 0);
	
	for (i = 0; i < 12; i++)
	{
		tabAttributionRoles[i] = ROLE_VILLAGEOIS;
	}
	int initRole = 3;
	for (i = 12 ; i < 17 ; i++)
	{
		tabAttributionRoles[i] = initRole;
		initRole += 1;
	}

	if (nbrDeJoueurs < 12)
	{
		nLoupgarou = 2;
	}
	else
	{
		nLoupgarou = 3;
	}

	///Voyante
	int caseJoueurAlea = rand() % (flecheJoueur + 1);
	joueurAlea = tabAttributionJoueur[caseJoueurAlea];
	tabRoles[joueurAlea] = ROLE_VOYANTE;
	echangeCase(tabAttributionJoueur, caseJoueurAlea, flecheJoueur);
	flecheJoueur = flecheJoueur - 1;

	///LoupGarou
	for (i = 0; i < nLoupgarou; i++)
	{
		caseJoueurAlea = rand() % (flecheJoueur + 1);
		joueurAlea = tabAttributionJoueur[caseJoueurAlea];

		tabRoles[joueurAlea] = ROLE_LOUP_GAROU;
		echangeCase(tabAttributionJoueur, caseJoueurAlea, flecheJoueur);
		flecheJoueur = flecheJoueur - 1;
	}

	///Reste

	while (flecheJoueur > 0) {
		caseJoueurAlea = rand() % (flecheJoueur + 1);
		caseRoleAlea = rand() % (flecheRole + 1);
		joueurAlea = tabAttributionJoueur[caseJoueurAlea];
		roleAlea = tabAttributionRoles[caseRoleAlea];

		tabRoles[joueurAlea] = roleAlea;
		echangeCase(tabAttributionJoueur, caseJoueurAlea, flecheJoueur);
		echangeCase(tabAttributionRoles, caseRoleAlea, flecheRole);

		flecheJoueur = flecheJoueur - 1;
		flecheRole = flecheRole - 1;
	}
	caseJoueurAlea = 0;
	caseRoleAlea = rand() % (flecheRole + 1);
	joueurAlea = tabAttributionJoueur[caseJoueurAlea];
	roleAlea = tabAttributionRoles[caseRoleAlea];

	tabRoles[joueurAlea] = roleAlea;
}

int voteCapitaine(GUI* input) {
	int i = 0;
	int caseAyantLePLusDeVote = 0;
	int nCaseAyantLeMemeNombreDeVote = 0;
	int joueurElu = 0;
	unsigned short nbrDeJoueurs = input->nombreDeJoueur;
	bool egalite_i = FAUX; // _i = ?
	bool vote_i = FAUX; // _i = ?
	//tab
	int tabEgalite[18] = { -1 };
	int tabVote[18] = { 0 };
	//Alea
	time_t t;
	srand((unsigned)time(&t));
	//

	int caseJoueur = 0;
	unsigned short tabJoueur[18] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };
	for (i = 0; i < nbrDeJoueurs; i++)
	{
		vote_i = FAUX;

		while (!vote_i)
		{
			char text[42];
			sprintf_s(text, 42, "Le Joueur %d doit voter pour un capitaine", i + 1);
			caseJoueur = choisirUnJoueur(input, tabJoueur, nbrDeJoueurs, text, .45) - 1;

			if (caseJoueur <= nbrDeJoueurs)
			{
				tabVote[caseJoueur] = tabVote[caseJoueur] + 1;
				//afficherTableau(tabVote, nbrDeJoueurs);
				vote_i = VRAI;
			}
		}
	}

	// Recherche du joueur le plus vote
	tabEgalite[0] = caseAyantLePLusDeVote;
	nCaseAyantLeMemeNombreDeVote = 1;
	for (i = 1; i < nbrDeJoueurs; i++)
	{
		if (tabVote[i] > tabVote[caseAyantLePLusDeVote])
		{
			if (egalite_i)
			{
				initTab(tabEgalite, 18, -1);
			}

			egalite_i = FAUX;
			caseAyantLePLusDeVote = i;
		}
		else if (tabVote[caseAyantLePLusDeVote] == tabVote[i])
		{
			if (!egalite_i)
			{
				initTab(tabEgalite, 18, -1);
				nCaseAyantLeMemeNombreDeVote = 1;
				tabEgalite[nCaseAyantLeMemeNombreDeVote - 1] = caseAyantLePLusDeVote;
			}

			egalite_i = VRAI;
			nCaseAyantLeMemeNombreDeVote += 1;
			tabEgalite[nCaseAyantLeMemeNombreDeVote - 1] = i;
		}
		//afficherTableau(tabEgalite, 18);
	}
	joueurElu = caseAyantLePLusDeVote;

	if (egalite_i)
	{
		printf("Des joueurs ont le meme nombres de vote. Le capitaine va etre defini de maniere aleatoire.\n");
		joueurElu = tabEgalite[rand() % (nCaseAyantLeMemeNombreDeVote + 1)];
	}

	printf("Le joueur %d est elu capitaine.\n", joueurElu + 1);
	return joueurElu;
}

int voteFinDeTour(GUI* input, Role* tabRoles, unsigned short nbrDeJoueursEnVie, int caseCapitaine) {
	int i = 0;
	int j = 0;
	int caseAyantLePLusDeVote = 0;
	int nCaseAyantLeMemeNombreDeVote = 0;
	int joueurElimine = 0;
	unsigned short nbrDeJoueurs = input->nombreDeJoueur;
	bool egalite_i = FAUX; // _i = ?
	bool vote_i = FAUX; // _i = ?
	//tab
	unsigned short tabEgalite[18];
	int tabVote[18] = { 0 };
	unsigned short tabJoueurEnVie[18];
	//Alea
	time_t t;
	srand((unsigned)time(&t));
	//creation Tableau joueur en vie
	for (i = 0; i < nbrDeJoueurs; i++)
	{
		if (tabRoles[i] != -1)
		{
			tabJoueurEnVie[j] = i+1;
			j += 1;
		}
	}
	
	int caseJoueur = 0;
	for (i = 0; i < nbrDeJoueurs; i++)
	{
		vote_i = FAUX;

		if (tabRoles[i] != -1)
		{
			while (!vote_i)
			{
				char text[49];
				sprintf_s(text, 49, "Le Joueur %d doit voter pour un Joueur a elimine", i + 1);	
				caseJoueur = choisirUnJoueur(input, tabJoueurEnVie, nbrDeJoueursEnVie, text, .5) - 1;

				if (tabRoles[caseJoueur] != -1 && caseJoueur <= nbrDeJoueurs)
				{
					tabVote[caseJoueur] = tabVote[caseJoueur] + 1;
					afficherTableau(tabVote, nbrDeJoueurs);
					vote_i = VRAI;
				}
			}
		}
	}

	// Recherche du joueur le plus voté
	tabEgalite[0] = caseAyantLePLusDeVote;
	nCaseAyantLeMemeNombreDeVote = 1;
	for (i = 1; i < nbrDeJoueurs; i++)
	{
		if (tabVote[i] > tabVote[caseAyantLePLusDeVote])
		{
			if (egalite_i)
			{
				initTabShort(tabEgalite, 18, 20);
			}

			egalite_i = FAUX;
			caseAyantLePLusDeVote = i;
		}
		else if (tabVote[caseAyantLePLusDeVote] == tabVote[i])
		{
			if (!egalite_i)
			{
				initTabShort(tabEgalite, 18, 20);
				nCaseAyantLeMemeNombreDeVote = 1;
				tabEgalite[nCaseAyantLeMemeNombreDeVote - 1] = caseAyantLePLusDeVote;
			}

			egalite_i = VRAI;
			nCaseAyantLeMemeNombreDeVote += 1;
			tabEgalite[nCaseAyantLeMemeNombreDeVote - 1] = i;
		}
		afficherTableau2(tabEgalite, 18);
	}
	joueurElimine = caseAyantLePLusDeVote;

	if (egalite_i)
	{
		vote_i = FAUX;
		for (i = 0; i < nCaseAyantLeMemeNombreDeVote; i++)
		{
			tabEgalite[i] += 1;
		}

		while (!vote_i)
		{
			char text[48];
			sprintf_s(text, 48, "Le capitaine, Joueur %d, doit eliminer un Joueur", i + 1);
			joueurElimine = choisirUnJoueur(input, tabEgalite, nCaseAyantLeMemeNombreDeVote, text, .45) - 1;

			if (tabVote[joueurElimine] == tabVote[caseAyantLePLusDeVote])
			{
				vote_i = VRAI;
			}
		}
	}
	return joueurElimine;
}

int fLoupgarou(GUI* input, Role* tabRoles, unsigned short nbrDeJoueursEnVie)
{
	int i;
	int j = 0;
	int caseJoueur = 0;
	int caseAyantLePLusDeVote = 0;
	int nCaseAyantLeMemeNombreDeVote = 0;
	int joueurVote = 0;
	unsigned short nbrDeJoueurs = input->nombreDeJoueur;
	//tab
	unsigned short tabEgalite[18];
	int tabVote[18] = { 0 };
	unsigned short tabJoueurEnVie[18];
	//bool
	bool egalite_i = FAUX; // _i = ?
	bool vote_i = FAUX; // _i = ?
	//creation Tableau joueur en vie
	for (i = 0; i < nbrDeJoueurs; i++)
	{
		if (tabRoles[i] != -1)
		{
			tabJoueurEnVie[j] = i+1;
			j += 1;
		}
	}
	afficherTableau2(tabJoueurEnVie, nbrDeJoueursEnVie);

	for (i = 0; i < nbrDeJoueurs; i++)
	{
		vote_i = FAUX;

		if (tabRoles[i] != -1)
		{
			if (tabRoles[i] == ROLE_LOUP_GAROU)
			{
				while (!vote_i)
				{
					char text[49];
					sprintf_s(text, 49, "Le Joueur %d doit voter pour un Joueur a elimine", i + 1);
					caseJoueur = choisirUnJoueur(input, tabJoueurEnVie, nbrDeJoueursEnVie, text, .5) - 1;
					printf("TEST");

					if (tabRoles[caseJoueur] != -1 && tabRoles[caseJoueur] != ROLE_LOUP_GAROU && caseJoueur <= nbrDeJoueurs)
					{
						tabVote[caseJoueur] = tabVote[caseJoueur] + 1;
						afficherTableau(tabVote, nbrDeJoueurs);
						vote_i = VRAI;
					}
				}
			}	
		}
	}

	for (i = 0; i < nbrDeJoueurs; i++)
	{
		if (tabRoles[i] = ROLE_LOUP_GAROU)
		{
			vote_i = FAUX;
			while (!vote_i)
			{
				char text[68];
				sprintf_s(text, 68, "Le Joueur %d doit voter pour le joueur qu'il souhaite voir elimine.", i + 1);
				caseJoueur = choisirUnJoueur(input, tabJoueurEnVie, nbrDeJoueursEnVie, text, .45) - 1;
				if (tabRoles[caseJoueur] != -1 && caseJoueur < nbrDeJoueurs && tabRoles[caseJoueur] != ROLE_LOUP_GAROU)
				{
					tabVote[caseJoueur] = tabVote[caseJoueur] + 1;
					vote_i = VRAI;
				}
				else
				{
					printf("Vous devez saisir un joueur ennemie encore en vie.\n");
				}
			}
		}
	}

	// Recherche du joueur le plus voté
	tabEgalite[0] = caseAyantLePLusDeVote;
	nCaseAyantLeMemeNombreDeVote = 1;
	for (i = 1; i < nbrDeJoueurs; i++)
	{
		if (tabVote[i] > tabVote[caseAyantLePLusDeVote])
		{
			if (egalite_i)
			{
				initTabShort(tabEgalite, 18, 20);
			}

			egalite_i = FAUX;
			caseAyantLePLusDeVote = i;
		}
		else if (tabVote[caseAyantLePLusDeVote] == tabVote[i])
		{
			if (!egalite_i)
			{
				initTabShort(tabEgalite, 18, 20);
				nCaseAyantLeMemeNombreDeVote = 1;
				tabEgalite[nCaseAyantLeMemeNombreDeVote - 1] = caseAyantLePLusDeVote;
			}

			egalite_i = VRAI;
			nCaseAyantLeMemeNombreDeVote += 1;
			tabEgalite[nCaseAyantLeMemeNombreDeVote - 1] = i;
		}
		afficherTableau2(tabEgalite, 18);
	}
	joueurVote = caseAyantLePLusDeVote;
	

	if (egalite_i == VRAI)
	{
		printf("Des joueurs ont le meme nombres de vote. Le joueur elimine va etre defini de maniere aleatoire.\n");
		joueurVote = tabEgalite[rand() % (nCaseAyantLeMemeNombreDeVote + 1)];
	}

	printf("Vous avez eliminez le joueur: %d.\n", joueurVote);
	tabRoles[joueurVote] = -1;
	return joueurVote;
}

void fVoyante(GUI* input, Role* tabRoles) {
	//alloue un tableau de tous les joueurs que peut voir la voyante
	unsigned short* joueursAVoir = (unsigned short*)calloc(input->nombreDeJoueur - 1, sizeof(unsigned short));
	
	//permet de stocker si on est déjà trouvé la voyante dans le tableau des roles
	bool trouverLaSorciere = false;

	//parcours le tableau des roles
	for (unsigned short i = 0; i < input->nombreDeJoueur; i++)
	{
		if (tabRoles[i] == ROLE_VOYANTE) {
			trouverLaSorciere = true;
			continue;
		}
		if (!trouverLaSorciere && i < input->nombreDeJoueur - 1)
			joueursAVoir[i] = (unsigned short)(i + 1);
		else
			joueursAVoir[i - 1] = (unsigned short)(i + 1);
	}

	//la yoyante choisit un joueurs
	unsigned short joueurAVoir = choisirUnJoueur(input, joueursAVoir, input->nombreDeJoueur - 1, "la voyante choisit un joueur a demasquer", .4);

	montrerLeRoleDuJoueur(input, tabRoles[joueurAVoir - 1], joueurAVoir);

	free(joueursAVoir);
}

void fCupidon(GUI* input, Role* tabRoles, int tabCupidon[])
{
	unsigned short nbrDeJoueurs = input->nombreDeJoueur;
	unsigned short caseJoueur;
	unsigned short caseCupidon = 0;
	unsigned short i;
	//tab
	unsigned short tabJoueur[18] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };
	//bool
	bool vote_i = FAUX; // _i = ?

	//Recherche de cupidon
	while (tabRoles[caseCupidon] == ROLE_CUPIDON)
	{
		caseCupidon += 1;
	}

	/*for (i = 0; i < 2; i++)
	{
		vote_i = FAUX;

		while (!vote_i)
		{
			char text[55];
			sprintf_s(text, 55, "Cupidon, Joueur %d doit choisir le Joueur %d du couple", caseCupidon + 1, i + 1);
			caseJoueur = choisirUnJoueur(input, tabJoueur, nbrDeJoueurs, text, .5);

			if (caseJoueur <= nbrDeJoueurs && tabCupidon[0] != caseJoueur)
			{
				tabCupidon[i] = caseJoueur;
				afficherTableau2(tabCupidon, 2);
				vote_i = VRAI;
			}
		}
	}*/

	vote_i = FAUX;

	while (!vote_i)
	{
		char text[55];
		sprintf_s(text, 55, "Cupidon, Joueur %d doit choisir le Joueur %d du couple", caseCupidon + 1, 0 + 1);
		caseJoueur = choisirUnJoueur(input, tabJoueur, nbrDeJoueurs, text, .5);

		if (caseJoueur <= nbrDeJoueurs && tabCupidon[0] != caseJoueur)
		{
			tabCupidon[0] = caseJoueur;
			afficherTableau2(tabCupidon, 2);
			vote_i = VRAI;
		}
	}

	vote_i = FAUX;

	while (!vote_i)
	{
		char text[55];
		sprintf_s(text, 55, "Cupidon, Joueur %d doit choisir le Joueur %d du couple", caseCupidon + 1, 1 + 1);
		caseJoueur = choisirUnJoueur(input, tabJoueur, nbrDeJoueurs, text, .5);

		if (caseJoueur <= nbrDeJoueurs && tabCupidon[0] != caseJoueur)
		{
			tabCupidon[1] = caseJoueur;
			afficherTableau2(tabCupidon, 2);
			vote_i = VRAI;
		}
	}
}
