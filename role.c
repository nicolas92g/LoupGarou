#include "role.h"

int reconaissanceRole(int role)
{
	switch (role)
	{
	case rloupgarou1:
		printf("Loup Garou");
		break;

	case rloupgarou2:
		printf("Loup Garou");
		break;

	case rloupgarou3:
		printf("Loup Garou");
		break;

	case rvoyante:
		printf("Voyante");
		break;

	case rcapitaine:
		printf("Maire");
		break;

	case rcupidon:
		printf("Cupidon");
		break;

	case rchasseur:
		printf("Chasseur");
		break;

	case rsorciere:
		printf("Sorciere");
		break;

	case rpetite_fille:
		printf("Petite fille");
		break;

	case rvoleur:
		printf("Voleur");
		break;

	case -1:
		printf("ERREUR");
		break;

	default:
		printf("Villageois");
	}
}

int fLoupgarou(int tabJoueur[], int tabRole[], int tabVote[], int tabEgalite[], int nLoupgarou, int nJoueur)
{
	int i;
	int j;
	int caseJoueur;
	int caseAyantLePLusDeVote = 0;
	int nCaseAyantLeMemeNombreDeVote = 0;
	int joueurVote = 0;
	bool egalite_i = FAUX; // _i = ?
	bool vote_i = FAUX; // _i = ?

	initTab(tabVote,nJoueur, 0);

	printf("\nLes loupgarou se reveille (Soit les joueurs suivants:");
	identificationLoupGarouEnVie(tabRole);
	printf(").\n");

	for (j = 0; j < nLoupgarou; j++)
	{
		vote_i = FAUX;

		if (tabRole[j] != MORT)
		{
			while (vote_i == FAUX)
			{
				printf("Les joueurs ennemi en vie sont les suivants:");
				for (i = 0; i < nJoueur; i++)
				{
					if (tabJoueur[i] != MORT && tabJoueur[i] != rloupgarou1 && tabJoueur[i] != rloupgarou2 && tabJoueur[i] != rloupgarou3)
					{
						printf(" [%d]", i);
					}
				}
				printf(".\n");

				printf("Joueur %d contre quelle joueur voulez vous votez ?", tabRole[j]);
				scanf_s("%d", &caseJoueur);
				if (tabJoueur[caseJoueur] != MORT && caseJoueur < nJoueur && tabJoueur[caseJoueur] != rloupgarou1 && tabJoueur[caseJoueur] != rloupgarou2 && tabJoueur[caseJoueur] != rloupgarou3)
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
			if (egalite_i == FAUX)
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
	joueurVote = caseAyantLePLusDeVote;

	if (egalite_i == VRAI)
	{
		printf("Des joueurs ont le meme nombres de vote. Le joueur elimine va etre defini de maniere aleatoire.\n");
		joueurVote = tabEgalite[rand() % (nCaseAyantLeMemeNombreDeVote + 1)];
	}

	printf("Vous avez eliminez le joueur: %d.\n", joueurVote);
	tabRole[tabJoueur[joueurVote]] = MORT;
	tabJoueur[joueurVote] = MORT;
	return joueurVote;
}

int fVoyante(int tabJoueur[], int tabRole[], int nJoueur) {
	int joueur;
	printf("\nLa Voyante se reveille (soit le Joueur %d.)\n", tabRole[rvoyante]);

	printf("De quelle joueur voulez vous connaitre le role ?");
	
	joueur = voteSolo(tabJoueur, nJoueur);

	reconaissanceRole(tabJoueur[joueur]);
	printf(".\n");
}

int fCupidon(int tabJoueur[], int tabRole[], int tabCupidon[]) {
	printf("\nCupidon se reveille (soit le Joueur %d).\n", tabRole[rcupidon]);

	printf("Quelle joueur seront en couple ?\n");
	printf("Joueur 1: ");
	scanf_s("%d", &tabCupidon[0]);

	do {
		printf("Joueur 2: ");
		scanf_s("%d", &tabCupidon[1]);
	} while (tabCupidon[0] != tabCupidon[1] && tabCupidon[1] != -1);

	printf("Le joueur %d et le joueur %d sont en couple.\n", tabCupidon[0], tabCupidon[1]);
}

int fSorciere(int tabJoueur[], int tabJoueurInit[], int tabRole[], int joueurMortLoup, int nJoueur, int nJoueurEnVie, int nLoupEnVie, bool sortEmpoisonnementSorciereUtilise_i, bool sortGuerisonSorciereUtilise_i)
{
	int reponse = -1;
	int joueur;
	int i;
	bool vote_i = FAUX;
	bool sortUtilise_i = FAUX;

	printf("\nLa sorciere se reveille (soit le Joueur %d).\n)", tabRole[rsorciere]);
	printf("Le joueur %d est mort cette nuit.\n", joueurMortLoup);

	if (sortGuerisonSorciereUtilise_i == FAUX)
	{
		printf("Voulez vous guerire quelqu'un (Saisir: 1 pour OUI et 0 pour NON)?");
		while (reponse != 0 && reponse != 1)
		{
			scanf_s("%d", &reponse);
		}

		sortGuerisonSorciereUtilise_i = reponse;
		if (sortGuerisonSorciereUtilise_i == VRAI)
		{
			sortUtilise_i = VRAI;
			while (vote_i != VRAI)
			{
				printf("Choisisez un joueur à guerir parmis les suivants:");
				for (i = 0; i < nJoueur; i++)
				{
					if (tabJoueur[i] == MORT)
					{
						printf(" [%d]", i);
					}
				}
				printf(".\n");

				scanf_s("%d", &joueur);
				if (tabJoueur[joueur] == MORT)
				{
					vote_i = VRAI;
					printf("Le joueur %d est guerit.", joueur);
					tabJoueur[joueur] = tabJoueurInit[joueur];
					tabRole[tabJoueur[joueur]] = joueur;
				}
			}
		}
	}

	reponse = -1;
	vote_i = FAUX;
	if (sortEmpoisonnementSorciereUtilise_i == FAUX && sortUtilise_i == FAUX)
	{
		printf("Voulez vous eliminer quelqu'un ?");
		while (reponse != 0 && reponse != 1)
		{
			printf("(Saisir: 1 pour OUI et 0 pour NON");
			scanf_s("%d", &reponse);
		}

		sortEmpoisonnementSorciereUtilise_i = reponse;
		if (sortEmpoisonnementSorciereUtilise_i == VRAI)
		{
			printf("Choisisez un joueur à eliminez parmis les suivants:");
			for (i = 0; i < nJoueur; i++)
			{
				if (tabJoueur[i] != MORT)
				{
					printf(" [%d]", i);
				}
			}
			printf(".\n");

			joueur = voteSolo(tabJoueur, nJoueur);

			printf("Le joueur %d est elimine.", joueur);
			nLoupEnVie = mortLoup(tabRole, joueur);

			tabJoueur[joueur] = MORT;
			tabRole[tabJoueur[joueur]] = MORT;
			nJoueurEnVie -= 1;
			return joueur;
		}
	}

	return -1;
}

int fChasseur(int tabJoueur[], int tabRole[], int tabRoleInit[], int nJoueur, int nLoupEnVie)
{
	int joueur;
	int i;
	bool vote_i = FAUX;

	printf("\nLe joueur %d qui ete le chasseur doit tue quelqu'un.\n", tabRoleInit[rchasseur]);

	while (vote_i != VRAI)
	{
		printf("Choisisez un joueur à eliminez parmis les suivants:");
		for (i = 0; i < nJoueur; i++)
		{
			if (tabJoueur[i] != MORT)
			{
				printf(" [%d]", i);
			}
		}
		printf(".\n");

		scanf_s("%d", &joueur);
		if (tabJoueur[joueur] != MORT)
		{
			vote_i = VRAI;
			printf("Le joueur %d est elimine par le chasseur.", joueur);
			nLoupEnVie = mortLoup(tabRole, joueur);

			tabJoueur[joueur] = MORT;
			tabRole[tabJoueur[joueur]] = MORT;
			return joueur;
		}
	}


}

int fPetite_fille(int tabRole[])
{
	printf("\nLa Petite fille (qui est le joueur %d) observant discrementent les loups garous appercoient les joueurs suivants:", tabRole[rpetite_fille]);
	identificationLoupGarouEnVie(tabRole);
	printf(").\n");
}

int fVoleur(int tabJoueur[], int tabRole[], int tabAttributionRole[], int nJoueur, int nLoupgarou)
{
	int flecheRole;
	int caseRoleALea;
	int roleALea;
	int roleChoisi;
	int i;
	int role[2];
	bool vote_i = FAUX;
	printf("\nLe voleur se reveille (soit le Joueur %d).\n", tabRole[rvoleur]);
	
	//determination des 2 roles de maniere aleatoire parmi ceux non distirbué
	flecheRole = TTRB - 1 -(nJoueur + 1 + nLoupgarou);
	
	caseRoleALea = rand() % (flecheRole + 1);
	roleALea = tabAttributionRole[caseRoleALea];
	role[0] = roleALea;

	echangeCase(tabAttributionRole, caseRoleALea, flecheRole);
	flecheRole = flecheRole - 1;

	caseRoleALea = rand() % (flecheRole + 1);
	roleALea = tabAttributionRole[caseRoleALea];
	role[1] = roleALea;
		
	//Choix
	while (vote_i == FAUX)
	{

		printf("Si voulez voler un des deux roles suivant saisant leur nemuero correspondant. Sinon saisise -1.\n");
		printf("Les deux roles sont ");
		reconaissanceRole(role[0]);
		printf(" soit le numero %d ", role[0]);
		printf("et ");
		reconaissanceRole(role[1]);
		printf(" soit le numero %d", role[1]);
		printf(".\n");

		scanf_s("%d", &roleChoisi);
		if (roleChoisi == role[0] || roleChoisi == role[1])
		{
			tabRole[roleChoisi] = tabRole[rvoleur];
			tabJoueur[tabRole[rvoleur]] = roleChoisi;
			tabRole[rvoleur] = -1;
			vote_i = VRAI;
		}
		else if(roleChoisi == -1)
		{
			printf("Vous ne changez pas de role.");
			vote_i = VRAI;
		}
		else
		{
			printf("Vous devez saisir un ou aucun des roles propose.\n");
		}
	}
}

int identificationLoupGarouEnVie(int tabRole[])
{
	if (tabRole[rloupgarou1] != MORT)
	{
		printf(" [%d] ", tabRole[rloupgarou1]);
	}
	if (tabRole[rloupgarou2] != MORT)
	{
		printf(" [%d] ", tabRole[rloupgarou2]);
	}
	if (tabRole[rloupgarou3] != MORT)
	{
		printf(" [%d]", tabRole[rloupgarou3]);
	}
}

int mortLoup(int tabRole[], int joueur)
{
	if (tabRole[rloupgarou1] == joueur || tabRole[rloupgarou2] == joueur || tabRole[rloupgarou3] == joueur)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}