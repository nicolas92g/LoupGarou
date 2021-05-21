#include "fonction.h"

int* initTab(int tab[], int taille, int a) {
	int i;
	for (i = 0;i < taille;i++)
	{
		tab[i] = a;
	}
	return 0; //bizzare
}

int* initTabShort(unsigned short tab[], int taille, int a) {
	int i;
	for (i = 0;i < taille;i++)
	{
		tab[i] = a;
	}
	return 0; //bizzare
}

int* initTab2(int tab[], int taille, int a) {
	int i;
	for (i = 0 ;i < taille;i++)
	{
		tab[i] = i+a;
	}
}

void afficherTableau(int tab[], int taille) {
	int i;

	for (i = 0; i < taille; i++)
	{
		printf("[%d] ", tab[i]);
	}

	printf("\n");
}

void afficherTableau2(unsigned short tab[], int taille) {
	int i;

	for (i = 0; i < taille; i++)
	{
		printf("[%d] ", tab[i]);
	}

	printf("\n");
}



void echangeCase(int tab[], int a, int b)
{
	int trans = tab[a];
	tab[a] = tab[b];
	tab[b] = trans;
}

int* copieTab(int tabA[], int tabB[], int taille)
{
	int i;
	for(i = 0; i < taille; i++)
	{
		tabA[i] = tabB[i];
	}
}

int voteSolo(int tabJoueur[], int nJoueur)
{
	int caseVote;
	bool vote_i = FAUX;

	while (vote_i == FAUX)
		{
			scanf_s("%d", &caseVote);
			if (tabJoueur[caseVote] != MORT && caseVote < nJoueur)
			{
				vote_i = VRAI;
				return caseVote;
			}
			else
			{
				printf("ERREUR.\n");
			}
		}
}

