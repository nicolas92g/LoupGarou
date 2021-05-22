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
		char text[42];
		sprintf_s(text, 42, "Le Joueur %d doit voter pour un capitaine", i + 1);
		caseJoueur = choisirUnJoueur(input, tabJoueur, nbrDeJoueurs, text, .45) - 1;

		tabVote[caseJoueur] = tabVote[caseJoueur] + 1;
		afficherTableau(tabVote, nbrDeJoueurs);
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

	//si egalite le capitaine est choisi aleatoirement
	if (egalite_i)
	{
		afficherMessage(input, "il y une egalite, Le capitaine va etre choisi aleatoirement", .55);
		joueurElu = tabEgalite[rand() % (nCaseAyantLeMemeNombreDeVote + 1)];
	}

	char buffer[31];
	sprintf_s(buffer, 31, "Le Joueur %d est elu capitaine", joueurElu + 1);
	afficherMessage(input, buffer, .3);

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
		if (tabRoles[i] != -1)
		{
			char text[49];
			sprintf_s(text, 49, "Le Joueur %d doit voter pour un Joueur a elimine", i + 1);	
			caseJoueur = choisirUnJoueur(input, tabJoueurEnVie, nbrDeJoueursEnVie, text, .5) - 1;

			tabVote[caseJoueur] = tabVote[caseJoueur] + 1;
			if (caseCapitaine == i)
			{
				tabVote[caseJoueur] = tabVote[caseJoueur] + 1;
			}
			afficherTableau(tabVote, nbrDeJoueurs);		
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
		//afficherTableau2(tabEgalite, 18);
	}
	joueurElimine = caseAyantLePLusDeVote;

	if (egalite_i)
	{
		for (i = 0; i < nCaseAyantLeMemeNombreDeVote; i++)
		{
			tabEgalite[i] += 1;
		}

		char text[48];
		sprintf_s(text, 48, "Le capitaine, Joueur %d, doit eliminer un Joueur", i + 1);
		joueurElimine = choisirUnJoueur(input, tabEgalite, nCaseAyantLeMemeNombreDeVote, text, .45) - 1;

		if (tabVote[joueurElimine] == tabVote[caseAyantLePLusDeVote])
		{
			vote_i = VRAI;
		}
	}

	char buffer[25];
	sprintf_s(buffer, 25, "Le Joueur %d est elimine", joueurElimine + 1);
	afficherMessage(input, buffer, .3);
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

	//Annonce du reveille
	afficherMessage(input, "Les loupgarous se reveille", .3);

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

	// Recherche du joueur le plus voté
	tabEgalite[0] = caseAyantLePLusDeVote;
	nCaseAyantLeMemeNombreDeVote = 1;
	initTabShort(tabEgalite, 18, 20);
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
	
	//Si egalite la victime est choisi aleatoirment parmis les joueurs les plus votés
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
	
	//verifie l'allocation dynamique
	assert(joueursAVoir);
	
	//permet de stocker si on est déjà trouvé la voyante dans le tableau des roles
	bool trouverLaSorciere = false;

	//Annonce du reveille
	afficherMessage(input, "La voyante se reveille", .3);
	
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

void fCupidon(GUI* input, Role* tabRoles, unsigned short tabCupidon[])
{
	unsigned short caseCupidon = 1;
	unsigned short tabJoueur[18] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };
	char text[57];
	unsigned short buf;

	afficherMessage(input, "Cupidon se reveille", .3);

	//Recherche de cupidon
	while (tabRoles[caseCupidon - 1] == ROLE_CUPIDON) caseCupidon++;

	//demande le premier joueur du couple
	sprintf_s(text, 56, "Cupidon, Joueur %d doit choisir le 1er Joueur du couple", caseCupidon);
	tabCupidon[0] = choisirUnJoueur(input, tabJoueur, input->nombreDeJoueur, text, .5);

	//enleve ce joueur du tableau
	buf = tabJoueur[tabCupidon[0] - 1];
	tabJoueur[tabCupidon[0] - 1] = tabJoueur[input->nombreDeJoueur - 1];
	tabJoueur[input->nombreDeJoueur - 1] = buf;

	//demande le 2eme joueur du couple
	sprintf_s(text, 57, "Cupidon, Joueur %d doit choisir le 2eme Joueur du couple", caseCupidon);
	tabCupidon[1] = choisirUnJoueur(input, tabJoueur, input->nombreDeJoueur - 1, text, .5);
}

void fVoleur(GUI* input, Role* tabRoles)
{
	unsigned short i;
	unsigned short j;
	unsigned short nbrDeJoueurs = input->nombreDeJoueur;
	unsigned short numeroJoueur = 0;
	unsigned short caseTabVoleur = 0;
	unsigned short nAlea;
	unsigned short flecheTabVoleur;
	unsigned short roleChoisi = 0;
	//tab
	unsigned short tabVoleur[19];
	Role tabVoleurChoix[2] = {0,1};
	//bool
	bool attribue;
	//ALea
	time_t t;
	srand((unsigned)time(&t));
	//Init Tab
	initTabShort(tabVoleur, 19, ROLE_VILLAGEOIS);
	//on cherche qui est le voleur
	while (tabRoles[numeroJoueur] != ROLE_VOLEUR)
	{
		numeroJoueur += 1;
	}
	
	//Remplissage de tab Voleur avec les roles non attribues
	tabVoleur[0] = ROLE_LOUP_GAROU;
	caseTabVoleur = 1;
	if (nbrDeJoueurs < 11)
	{
		tabVoleur[1] = ROLE_LOUP_GAROU;
		caseTabVoleur += 1;
	}

	for (j = 3; j < 7; j++)
	{
		attribue = FAUX;
		for (i = 0; i < nbrDeJoueurs; i++)
		{
			if (tabRoles[i] == j)
			{
				attribue = VRAI;
			}
		}
		if (!attribue)
		{
			tabVoleur[caseTabVoleur] = j;
			caseTabVoleur += 1;
		}
	}
	afficherTableau2(tabVoleur, 19);

	//choix aleatoire des deux roles
	flecheTabVoleur = 19 - nbrDeJoueurs;
	
	nAlea = rand() % flecheTabVoleur;
	tabVoleurChoix[0] = tabVoleur[nAlea];
	echangeCase2(tabVoleur, nAlea, 18);

	flecheTabVoleur -= 1;
	nAlea = rand() % flecheTabVoleur;
	tabVoleurChoix[1] = tabVoleur[nAlea];

	afficherTableau(tabVoleurChoix, 2);

	roleChoisi = choisirUneCarte(input, tabVoleurChoix);

	tabRoles[numeroJoueur] = roleChoisi;
}

bool fSorciere(GUI* input, Role* tabRoles, bool peutTuer, bool peutSauver, short joueurTuee, unsigned short nbrDeJoueurEnVie, unsigned short* joueursTueParLaSorciere)
{
	unsigned short i;
	unsigned short j = 0;
	Actions action;
	//tab
	unsigned short tabJoueurEnVie[18];

	action = ActionsSorciere(input, peutTuer, peutSauver, joueurTuee);

	//Action de tuer
	if (action == SORCIERE_TUER)
	{
		//creation Tableau joueur en vie
		for (i = 0; i < input->nombreDeJoueur; i++)
		{
			if (tabRoles[i] != -1 && tabRoles[i] != ROLE_VOYANTE)
			{
				tabJoueurEnVie[j] = i + 1;
				j++;
			}
		}

		unsigned char text[48] = "La sorciere doit eliminer un Joueur";
		text[17] = 233;

		*joueursTueParLaSorciere = choisirUnJoueur(input, tabJoueurEnVie, j, text, .37);
	}
	else if (action == SORCIERE_SAUVER) {
		return true;
	}
	return false;
}

int fChasseur(GUI* input, Role* tabRoles, unsigned short joueursEnVie) {
	unsigned short joueursATuer[17];
	int j = 0;

	for (size_t i = 0; i < joueursEnVie; i++)
	{
		if (tabRoles[i] != ROLE_CHASSEUR) {
			joueursATuer[j] = i + 1;
			j++;
		}
	}
	unsigned char text[59] = "le Chasseur doit choisir un Joueur a tuer avant de mourrir";
	text[35] = 224;

	return choisirUnJoueur(input, joueursATuer, j, text, .6);
}

bool LeRoleExiste() {
	return true;
}

void deroulementDeLaPartie(GUI* input, Role* roles){
	bool SorcierePotionTuer = true;
	bool SorcierePotionSauver = true;
	Role* rolesEnVie = (Role*)malloc(sizeof(Role) * input->nombreDeJoueur);
	montrerLeRoleDeChaqueJoueurs(input, roles);

	afficherMessage(input, "le village s endort !", .17f);


}
