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

int voteCapitaine(GUI* input, unsigned short nbrDeJoueurs) {
	int i = 0;
	int caseAyantLePLusDeVote = 0;
	int nCaseAyantLeMemeNombreDeVote = 0;
	int joueurElu = 0;
	bool egalite_i = FAUX; // _i = ?
	bool vote_i = FAUX; // _i = ?
	//tab
	int tabEgalite[18] = { -1 };
	int tabVote[18] = { 0 };
	//Alea
	time_t t;
	srand((unsigned)time(&t));
	//

	printf("\nC'est le moment de voter pour le capitaine.\n");

	int caseJoueur = 0;
	unsigned short tabJoueur[18] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };
	for (i = 0; i < nbrDeJoueurs; i++)
	{
		vote_i = FAUX;

		while (vote_i == FAUX)
		{
			char text[42];
			sprintf_s(text, 42, "Le Joueur %d doit voter pour un capitaine", i + 1);
			caseJoueur = choisirUnJoueur(input, tabJoueur, nbrDeJoueurs, text, .45) - 1;

			if (caseJoueur < nbrDeJoueurs)
			{
				tabVote[caseJoueur] = tabVote[caseJoueur] + 1;
				afficherTableau(tabVote, nbrDeJoueurs);
				vote_i = VRAI;
			}
			else
			{
				printf("Vous devez saisir un joueur encore en vie.\n");
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
		afficherTableau(tabEgalite, 18);
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

int voteFinDeTour(GUI* input, Role* tabRoles, unsigned short nbrDeJoueurs, unsigned short nbrDeJoueursEnVie, int caseCapitaine) {
	int i = 0;
	int j = 0;
	int caseAyantLePLusDeVote = 0;
	int nCaseAyantLeMemeNombreDeVote = 0;
	int joueurElimine = 0;
	bool egalite_i = FAUX; // _i = ?
	bool vote_i = FAUX; // _i = ?
	//tab
	int tabEgalite[18] = { -1 };
	int tabVote[18] = { 0 };
	int tabJoueurEnVie[18] = { -1 };
	//Alea
	time_t t;
	srand((unsigned)time(&t));
	//creation Tableau joueur en vie
	for (i = 0; i < nbrDeJoueurs; i++)
	{
		if (tabRoles[i] != -1)
		{
			tabJoueurEnVie[j] = i;
			j += 1;
		}
	}

	int caseJoueur = 0;
	unsigned short tabJoueur[18] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };
	for (i = 0; i < nbrDeJoueurs; i++)
	{
		vote_i = FAUX;

		if (tabRoles[i] != -1)
		{
			while (vote_i == FAUX)
			{
				char text[68];
				sprintf_s(text, 68, "Le Joueur %d doit voter pour le joueur qu'il souhaite voir elimine.", i + 1);	
				caseJoueur = choisirUnJoueur(input, tabJoueurEnVie, nbrDeJoueursEnVie, text, .45) - 1; //A changer

				if (tabRoles[i] != -1 && caseJoueur < nbrDeJoueurs)
				{
					tabVote[caseJoueur] = tabVote[caseJoueur] + 1;
					afficherTableau(tabVote, nbrDeJoueurs);
					vote_i = VRAI;
				}
				else
				{
					printf("Vous devez saisir un joueur encore en vie.\n");
				}
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
		afficherTableau(tabEgalite, 18);
	}
	joueurElimine = caseAyantLePLusDeVote;

	if (egalite_i)
	{
		printf("Des joueurs ont le meme nombres de vote.\n Le joueur numero %d qui est le capitaine va choisir quelle joueur sera elimine.\n", caseCapitaine);

		printf("Les joueurs a egalite sont les joueurs: ");

		i = 0;
		while (tabEgalite[i] != -1)
		{
			if (i > 0)
			{
				printf(",");
			}
			printf(" %d", tabEgalite[i]);
			i += 1;
		}
		printf(".\n");

		vote_i = FAUX;
		while (!vote_i)
		{
			char text[68];
			sprintf_s(text, 68, "Le Joueur %d doit voter pour le joueur qu'il souhaite voir elimine.", i + 1);
			joueurElimine = choisirUnJoueur(input, tabEgalite, nbrDeJoueurs, text, .45) - 1;

			if (tabVote[joueurElimine] == tabVote[caseAyantLePLusDeVote])
			{
				vote_i = VRAI;
			}
			else
			{
				printf("Vous devez saisir un joueur encore en vie.\n");
			}
		}
	}

	printf("Le joueur elimine est le joueur: %d.\n", joueurElimine);
	return joueurElimine;
}

int fLoupgarou(GUI* input, Role* tabRoles, unsigned short nbrDeJoueurs, unsigned short nbrDeJoueursEnVie)
{
	int i;
	int j = 0;
	int caseJoueur;
	int caseAyantLePLusDeVote = 0;
	int nCaseAyantLeMemeNombreDeVote = 0;
	int joueurVote = 0;
	//tab
	int tabEgalite[18] = { -1 };
	int tabVote[18] = { 0 };
	int tabJoueurEnVie[18] = { -1 };
	//bool
	bool egalite_i = FAUX; // _i = ?
	bool vote_i = FAUX; // _i = ?

	//creation Tableau joueur en vie
	for (i = 0; i < nbrDeJoueurs; i++)
	{
		if (tabRoles[i] != -1)
		{
			tabJoueurEnVie[j] = i;
			j += 1;
		}
	}

	printf("\nLes loupgarou se reveille (Soit les joueurs suivants:");
	for (i = 0; i < nbrDeJoueurs; i++)
	{
		if (tabRoles[i] = ROLE_LOUP_GAROU)
		{
			printf(" %d,", i + 1);
		}
	}
	printf(").\n");

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
		afficherTableau(tabEgalite, 18);
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

/*void fVoyante(GUI* input, Role* tabRoles, int nJoueur) {
	int joueur;
	int cVoyante = 0;
	while (tabRoles[cVoyante] != ROLE_VOYANTE)
	{
		cVoyante += 1;
	}

	printf("\nLa Voyante se reveille (soit le Joueur %d.)\n", cVoyante);

	printf("De quelle joueur voulez vous connaitre le role ?");

	joueur = voteSolo(tabJoueur, nJoueur);

	reconaissanceRole(tabJoueur[joueur]);
	printf(".\n");
}*/