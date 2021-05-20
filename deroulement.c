#include "deroulement.h"

int deroulement(int tabJoueur[], int tabJoueurInit[], int tabRole[], int tabVote[], int tabEgalite[], int tabAssignationRole[], int nJoueur, int nLoupgarou)
{
	int tabRoleInit[TTR];
	int* tabCupidon[2]; //indique les deux joueurs en couple
	int* nLoupgarouEnVie = nLoupgarou;
	int* nJoueurEnVie = nJoueur;
	int joueurMortLoup;
	int joueurMortSorciere;
	int caseCapitaine;
	bool* sortEmpoisonnementSorciereUtilise_i = FAUX;
	bool* sortGuerisonSorciereUtilise_i = FAUX;
	bool* coupleVie_i = VRAI;
	bool* finParti_i = FAUX;
	//---
	copieTab(tabJoueurInit, tabJoueur, nJoueur);
	copieTab(tabRoleInit, tabRole, TTR);
	initTab(tabCupidon, 2, -1);
	//--------
	
	caseCapitaine = voteCapitaine(tabJoueur, tabRole, tabVote, tabEgalite, nJoueur);
	printf("C'est la nuit. Le vilage s'endort.\n");

	if (tabRole[rvoleur] != MORT)
	{
		fVoleur(tabJoueur, tabRole, tabAssignationRole, nJoueur, nLoupgarou);
	}
	if (tabRole[rcupidon] != MORT)
	{
		fCupidon(tabJoueur, tabRole, tabCupidon);
	}
	
	
	do {
		joueurMortLoup = -2;
		joueurMortSorciere = -1;
		//Voyante
		if (tabRole[rvoyante] != MORT);
		{
			fVoyante(tabJoueur, tabRole, nJoueur);
		}
		//LoupGarou
		joueurMortLoup = fLoupgarou(tabJoueur, tabRole, tabVote, tabEgalite, nLoupgarou, nJoueur);
		afficherTableau(tabJoueur, nJoueur);
		nJoueurEnVie = -1;
		nJoueurEnVie = fCoupleVie(tabJoueur, tabCupidon, coupleVie_i);
		fPartiFini(nLoupgarouEnVie, nJoueurEnVie, finParti_i);
		printf("\nTEST\n");
		//Petite fille
		if (tabRole[rpetite_fille] != MORT)
		{
			fPetite_fille(tabRole);	
		}
		//Sorciere
		if (tabRole[rsorciere] != MORT || joueurMortLoup == tabRole[rsorciere])
		{
			joueurMortSorciere = fSorciere(tabJoueur, tabJoueurInit, tabRole, joueurMortLoup, nLoupgarouEnVie, nJoueur, nJoueurEnVie, sortEmpoisonnementSorciereUtilise_i, sortGuerisonSorciereUtilise_i);
			afficherTableau(tabJoueur, nJoueur);
			nJoueurEnVie = fCoupleVie(tabJoueur, tabCupidon, coupleVie_i);
			fPartiFini(nLoupgarouEnVie, nJoueurEnVie, finParti_i);
		}
		///Fin de tour
		if (joueurMortSorciere == -1)
		{
			printf("Le joueur %d est elimine.\n", joueurMortLoup);
		}
		else
		{
			printf("Les joueur %d et %d sont elimine.\n", joueurMortLoup, joueurMortSorciere);
		}

		if (coupleVie_i == FAUX)
		{
			printf("Les joueurs %p et %p etait en couple. Ils sont donc tous deux elimine.\n", tabCupidon[0], tabCupidon[1]);
		}

		if (joueurMortLoup == tabRole[rchasseur] || joueurMortSorciere == tabRole[rchasseur])
		{
			fChasseur(tabJoueur, tabRole, tabRoleInit, nJoueur, nLoupgarouEnVie);
			nJoueurEnVie = -1;
			nJoueurEnVie = fCoupleVie(tabJoueur, tabCupidon, coupleVie_i);
			fPartiFini(nLoupgarouEnVie, nJoueurEnVie, finParti_i);
		}

		caseCapitaine = capitaineMort(tabJoueur, tabRole, caseCapitaine, nJoueur);

		afficherTableau(tabJoueur, nJoueur);

		voteMort(tabJoueur, tabRole, tabVote, tabEgalite, nJoueur);
		fPartiFini(nLoupgarouEnVie, nJoueurEnVie, finParti_i);
	} while (finParti_i == VRAI);
}

bool fPartiFini(int nLoupgarouEnVie, int nJoueurEnVie, bool finPart_i)
{
	if (nLoupgarouEnVie == 0 || nJoueurEnVie == 0)
	{
		finPart_i = VRAI;
	}
}

int fCoupleVie(int tabJoueur[], int tabCupidon[], bool coupleVie_i)
{
	if (tabJoueur[tabCupidon[0]] == MORT)
	{
		tabJoueur[tabCupidon[1]] = MORT;
		coupleVie_i = FAUX;
		return -1;
	}
	else if (tabJoueur[tabCupidon[1]] == MORT)
	{
		tabJoueur[tabCupidon[0]] = MORT;
		coupleVie_i = FAUX;
		return -1;
	}

	return 0;
}

int capitaineMort(int tabJoueur[], int tabRole[], int caseCapitaine, int nJoueur)
{
	bool vote_i = FAUX; // _i = ?

	if (tabJoueur[caseCapitaine] == MORT)
	{
		caseCapitaine = voteSolo(tabJoueur, nJoueur);
	}
	return caseCapitaine;
}

int vote(int tabJoueur[], int tabVote[], int nJoueur)
{
	int i = 0;
	bool vote_i = FAUX; // _i = ?
	int caseJoueur = 0;
	//------
	initTab(tabVote, nJoueur, 0);
	//Vote
	
	for (i = 0; i < nJoueur; i++)
	{
		vote_i = FAUX;

		if (tabJoueur[i] != MORT)
		{
			while (vote_i == FAUX)
			{
				printf("Joueur %d pour quelle joueur voulez vous votez ?", i);
				scanf_s("%d", &caseJoueur);
				if (tabJoueur[caseJoueur] != MORT && caseJoueur < nJoueur)
				{
					tabVote[caseJoueur] = tabVote[caseJoueur] + 1;
					afficherTableau(tabVote, nJoueur);
					vote_i = VRAI;
				}
				else
				{
					printf("Vous devez saisir un joueur encore en vie.\n");
				}
			}
		}
	}
}

int voteCapitaine(int tabJoueur[], int tabRole[], int tabVote[], int tabEgalite[], int nJoueur)
{
	int i = 0;
	int caseAyantLePLusDeVote = 0;
	int nCaseAyantLeMemeNombreDeVote = 0;
	int joueurElu = 0;
	bool egalite_i = FAUX; // _i = ?
	//Alea
	time_t t;
	srand((unsigned)time(&t));
	//
	initTab(tabEgalite, nJoueur, -1);

	printf("\nC'est le moment de voter pour le capitaine.\n");

	vote(tabJoueur, tabVote, nJoueur);

	// Recherche du joueur le plus vote

	egalite_i = FAUX;
	caseAyantLePLusDeVote = 0;
	tabEgalite[0] = caseAyantLePLusDeVote;
	nCaseAyantLeMemeNombreDeVote = 1;
	for (i = 1; i < nJoueur; i++)
	{
		if (tabVote[i] > tabVote[caseAyantLePLusDeVote])
		{
			if (egalite_i == VRAI)
			{
				initTab(tabEgalite, nJoueur, -1);
			}

			egalite_i = FAUX;
			caseAyantLePLusDeVote = i;
		}
		else if (tabVote[caseAyantLePLusDeVote] == tabVote[i])
		{
			if(egalite_i == FAUX)
			{
				initTab(tabEgalite, nJoueur, -1);
				nCaseAyantLeMemeNombreDeVote = 1;
				tabEgalite[nCaseAyantLeMemeNombreDeVote - 1] = caseAyantLePLusDeVote;
			}

			egalite_i = VRAI;
			nCaseAyantLeMemeNombreDeVote += 1;
			tabEgalite[nCaseAyantLeMemeNombreDeVote - 1] = i;
		}
	}
	joueurElu = caseAyantLePLusDeVote;

	if (egalite_i == VRAI)
	{
		printf("Des joueurs ont le meme nombres de vote. Le capitaine va etre defini de maniere aleatoire.\n");
		joueurElu = tabEgalite[rand() % (nCaseAyantLeMemeNombreDeVote + 1)];
	}

	printf("Le joueur %d est elu capitaine.\n", joueurElu);
	tabRole[rcapitaine] = joueurElu;
	return joueurElu;
}

int voteMort(int tabJoueur[], int tabRole[], int tabVote[], int tabEgalite[], int nJoueur)
{
	int i = 0;
	int j = 0;
	int caseAyantLePLusDeVote = 0;
	int nCaseAyantLeMemeNombreDeVote = 0;
	int joueurELimine = 0;
	int caseJoueur = 0;
	bool egalite_i = FAUX; // _i = ?
	bool vote_i = FAUX; // _i = ?
	//---
	initTab(tabEgalite, nJoueur, -1);

	vote(tabJoueur, tabVote, nJoueur);
	
	// Recherche du joueur le plus vote
	egalite_i = FAUX;
	caseAyantLePLusDeVote = 0;
	tabEgalite[0] = caseAyantLePLusDeVote;
	nCaseAyantLeMemeNombreDeVote = 1;
	afficherTableau(tabEgalite, nJoueur);
	for (i = 1; i < nJoueur; i++)
	{
		if (tabVote[i] > tabVote[caseAyantLePLusDeVote])
		{
			if (egalite_i == VRAI)
			{
				initTab(tabEgalite, nJoueur, -1);
			}

			egalite_i = FAUX;
			caseAyantLePLusDeVote = i;
			afficherTableau(tabEgalite, nJoueur);
		}
		else if (tabVote[caseAyantLePLusDeVote] == tabVote[i])
		{
			if (egalite_i == FAUX)
			{
				initTab(tabEgalite, nJoueur, -1);
				nCaseAyantLeMemeNombreDeVote = 1;
				tabEgalite[nCaseAyantLeMemeNombreDeVote - 1] = caseAyantLePLusDeVote;
			}

			egalite_i = VRAI;
			nCaseAyantLeMemeNombreDeVote += 1;
			tabEgalite[nCaseAyantLeMemeNombreDeVote - 1] = i;
			afficherTableau(tabEgalite, nJoueur);
		}
	}
	joueurELimine = caseAyantLePLusDeVote;
	printf("TEST");
	
	if (egalite_i == VRAI)
	{
		printf("Des joueurs ont le meme nombres de vote.\n Le joueur numero %d qui est le capitaine va choisir quelle joeur sera elimine.\n", tabRole[rcapitaine]);
	
		while (vote_i == FAUX)
		{
			printf("Les joueurs a egalite sont les joueurs: ");
			
			i = 0;
			while(tabEgalite[i] != -1)
			{
				if (i > 0)
				{
					printf(",");
				}
				printf(" %d", tabEgalite[i]);
				i += 1;
			}	
			printf(".\n");

			printf("Joueur %d quelle joueur sera elimine ?\n", tabRole[rcapitaine]);
			scanf_s("%d", &joueurELimine);
			if (tabVote[joueurELimine] == tabVote[caseAyantLePLusDeVote])
			{
				vote_i = VRAI;
			}
			else
			{
				printf("Vous devez saisir un joueur encore en vie.\n");
			}
		}
	}

	printf("Le joueur elimine est le joueur: %d.\n", joueurELimine);
	tabRole[tabJoueur[joueurELimine]] = MORT;
	tabJoueur[joueurELimine] = MORT;
}
