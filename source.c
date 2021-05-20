#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "initialisation.h"
#include "fonction.h"
#include "deroulement.h"
#include "interface.h"

int main2() {

	int nJoueur = 0;
	int nLoupgarou = 0;
	//------
	int* tabJoueur = NULL;
	int* tabJoueurInit = NULL;
	int* tabAttributionJoueur = NULL;
	int* tabRole[TTR];
	int* tabAttributionRole[TTRB];

	//--Partie
	int* tabVote = NULL; //indique combien de fois les joueur ont été vote.
	int* tabEgalite = NULL; //indique quelle joueur ont été voté de maniere egal.

	//intilisationTab
	initTab(tabRole, TTR, -1);
	initTab2(tabAttributionRole, TTRB, 5);

	////Creation des tableaux en fonctions du nombre de joueur

	GLFWwindow* fenetre;
	creerLaFenetre(&fenetre);

	GUI input = make_GUI(fenetre);
	recupererLeNombreDeJoueurs(&input);
	nJoueur = input.nombreDeJoueur;

	tabJoueur = malloc(sizeof(int) * nJoueur);
	tabAttributionJoueur = malloc(sizeof(int) * nJoueur); //
	tabVote = malloc(sizeof(int) * nJoueur);			  // on peut peut-être recyclé tabAttributionRole
	tabEgalite = malloc(sizeof(int) * nJoueur);
	tabJoueurInit = malloc(sizeof(int) * nJoueur);

	if (nJoueur == 0) 
	{
		exit(EXIT_FAILURE); 
	}

	initTab(tabJoueur, nJoueur, -1);
	initTab2(tabAttributionJoueur, nJoueur, 0);
	initTab(tabVote, nJoueur, 0);
	initTab(tabEgalite, nJoueur, -1);

	initialisation(tabJoueur, tabAttributionJoueur, tabRole, tabAttributionRole, nJoueur, nLoupgarou);
	annoncementRole(tabJoueur, nJoueur);

	////Deroulement
	deroulement(tabJoueur, tabJoueurInit, tabRole, tabVote, tabEgalite, tabAttributionRole, nJoueur, nLoupgarou);
	
	
	//
	//afficherTableau(tabJoueur, nJoueur);
	//afficherTableau(tabRole, TTR);
	//afficherTableau(tabCupidon, 2);
	//---
	printf("o");
	free(tabJoueur);
	free(tabAttributionJoueur);
	free(tabJoueurInit);
	free(tabVote);
	free(tabEgalite);
	return 0;
}

