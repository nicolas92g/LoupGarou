#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction.h"

enum {
	iloupgarou1,//0  
	iloupgarou2,//1
	iloupgarou3,//2
	ivoyante,//3
	icapitaine,//4
	icupidon,//5
	ichasseur,//6
	isorciere,//7
	ipetite_fille,//8
	ivoleur,//9
	ivillageois1,//10
	ivillageois2,//11
	ivillageois3,//12
	ivillageois4,//13
	ivillageois5,//14
	ivillageois6,//15
	ivillageois7,//16
	ivillageois8,//17
	ivillageois9,//18
	ivillageois10,//19
	ivillageois11,//20
	ivillageois12,//21
	ivillageois13,//22
};

#define TTR 23 // TTR: Taille du TabRole
#define TTRB 18// TTR: Taille du la Seconde Parti duTabRole

int initialisation(int tabJoueur[], int tabAttributionJoueur[], int tabRole[], int tabAttributionRole[], int nJoueur);
int attribution(int tabJoueur[], int tabRole[], int tabAttributionJoueur[], int tabAttributionRole[], int nJoueur, int nLoupgarou);
int annoncementRole(int tabJoueur[], int nJoueur);
