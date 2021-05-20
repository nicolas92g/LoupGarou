#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

#define TTRB 18
#define MORT -1
#define VRAI 1
#define FAUX 0

enum {
	rloupgarou1,//0  
	rloupgarou2,//1
	rloupgarou3,//2
	rvoyante,//3
	rcapitaine,//4
	rcupidon,//5
	rchasseur,//6
	rsorciere,//7
	rpetite_fille,//8
	rvoleur,//9
	rvillageois1,//10
	rvillageois2,//11
	rvillageois3,//12
	rvillageois4,//13
	rvillageois5,//14
	rvillageois6,//15
	rvillageois7,//16
	rvillageois8,//17
	rvillageois9,//18
	rvillageois10,//19
	rvillageois11,//20
	rvillageois12,//21
	rvillageois13,//22
};

int reconaissanceRole(int role);
int fLoupgarou(int tabJoueur[], int tabRole[], int tabVote[], int tabEgalite[], int nLoupgarou, int nJoueur);
int fVoyante(int tabJoueur[], int tabRole[], int nJoueur);
int fCupidon(int tabJoueur[], int tabRole[], int tabCupidon[]);
int fSorciere(int tabJoueur[], int tabJoueurInit[], int tabRole[], int joueurMortLoup, int nLoupEnVie, int nJoueur, int nJoueurEnVie, bool sortEmpoisonnementSorciereUtilise_i, bool sortGuerisonSorciereUtilise_i);
int fChasseur(int tabJoueur[], int tabRole[], int tabRoleInit[], int nJoueur, int nLoupEnVie);
int fPetite_fille(int tabRole[]);
int fVoleur(int tabJoueur[], int tabRole[], int tabAssignationRole[], int nJoueur, int nLoupgarou);
////
int identificationLoupGarouEnVie(int tabRole[]);

int mortLoup(int tabRole[], int joueur);