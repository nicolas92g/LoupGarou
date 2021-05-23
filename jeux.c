#include "jeux.h"

void attribution(Role* tabRoles, unsigned short nbrDeJoueurs) {
	int caseRoleAlea = 0;
	int flecheJoueur = nbrDeJoueurs - 1;
	int flecheRole = 16;
	int joueurAlea = 0;
	int roleAlea = 0;
	int nLoupgarou = 0;
	int i;
	//Tableaux
	int tabAttributionJoueur[18];
	int tabAttributionRoles[17];
	//Mise en place de l'aleatoire
	time_t t;
	srand((unsigned)time(&t));

	////Initilisation de tableau Joueur. 
	//Les cases du tableau contienne les numeros des joueurs
	//Ce tableau contient tout les joueurs
	initTab2(tabAttributionJoueur, nbrDeJoueurs, 0);

	////Initilisation de tableau Roles. 
	//Ce tableau contient tout les roles qui vont être distribué
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

	// Distribution du role: Voyante
	int caseJoueurAlea = rand() % (flecheJoueur + 1);
	joueurAlea = tabAttributionJoueur[caseJoueurAlea];
	tabRoles[joueurAlea] = ROLE_VOYANTE;
	echangeCase(tabAttributionJoueur, caseJoueurAlea, flecheJoueur);
	flecheJoueur = flecheJoueur - 1;

	//Distribution des roles LoupGarou en fonction du nombre de joueurs
	for (i = 0; i < nLoupgarou; i++)
	{
		caseJoueurAlea = rand() % (flecheJoueur + 1);
		joueurAlea = tabAttributionJoueur[caseJoueurAlea];

		tabRoles[joueurAlea] = ROLE_LOUP_GAROU;
		echangeCase(tabAttributionJoueur, caseJoueurAlea, flecheJoueur);
		flecheJoueur = flecheJoueur - 1;
	}

	//Distribution des roles restant en fonction du nombre de joueurs
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
	//booleen
	bool egalite_i = FAUX; // _i = ?
	//Tableaux
	int tabEgalite[18] = { -1 };
	int tabVote[18] = { 0 };
	//Mise en place de l'aleatoire
	time_t t;
	srand((unsigned)time(&t));
	
	//Chaque joueurs vote pour le joueur qu'il souhaite voir capitaine
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

	//Recherche du joueur le plus vote
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
	}
	joueurElu = caseAyantLePLusDeVote;

	//si egalite le capitaine est choisi aleatoirement
	if (egalite_i)
	{
		afficherMessage(input, "il y une egalite, Le capitaine va etre choisi aleatoirement", .55);
		joueurElu = tabEgalite[rand() % (nCaseAyantLeMemeNombreDeVote + 1)];
	}

	//Affichage du joueur elu
	char buffer[31];
	sprintf_s(buffer, 31, "Le Joueur %d est elu capitaine", joueurElu + 1);
	afficherMessage(input, buffer, .3);

	//On retourne le numero du joueur elu
	return joueurElu;
}

int voteFinDeTour(GUI* input, Role* tabRoles, unsigned short nbrDeJoueursEnVie, int caseCapitaine) {
	int i = 0;
	int j = 0;
	int caseAyantLePLusDeVote = 0;
	int nCaseAyantLeMemeNombreDeVote = 0;
	int joueurElimine = 0;
	unsigned short nbrDeJoueurs = input->nombreDeJoueur;
	//Booleen
	bool egalite_i = FAUX; // _i = ?
	//Tableaux
	unsigned short tabEgalite[18];
	int tabVote[18] = { 0 };
	unsigned short tabJoueurEnVie[18];
	//Mise en place de l'aleatoire
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
	
	//Chaque joueurs vote pour le joueur qu'il veut voir être elimine
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
	}
	joueurElimine = caseAyantLePLusDeVote;

	//Le capitaine choisi quel joueur sera elimine en cas d'egalite
	if (egalite_i)
	{
		for (i = 0; i < nCaseAyantLeMemeNombreDeVote; i++)
		{
			tabEgalite[i] += 1;
		}

		char text[48];
		sprintf_s(text, 48, "Le capitaine, Joueur %d, doit eliminer un Joueur", i + 1);
		joueurElimine = choisirUnJoueur(input, tabEgalite, nCaseAyantLeMemeNombreDeVote, text, .45) - 1;
	}

	//Annonce du joueur elimine
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
	//Tableau
	unsigned short tabEgalite[18];
	int tabVote[18] = { 0 };
	unsigned short tabJoueurEnVie[18];
	//bool
	bool egalite_i = FAUX; // _i = ?
	bool vote_i = FAUX; // _i = ?

	//Annonce du reveille
	afficherMessage(input, "Les loup garous se reveille", .3);

	//creation Tableau joueur en vie
	for (i = 0; i < nbrDeJoueurs; i++)
	{
		if (tabRoles[i] != ROLE_MORT && tabRoles[i] != ROLE_LOUP_GAROU)
		{
			tabJoueurEnVie[j] = i + 1;
			j += 1;
		}
	}

	//Chaque loupgarou en vie vote pour le joueur qu'il souhaite elimine
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

					if (tabRoles[caseJoueur] != -1 && tabRoles[caseJoueur] != ROLE_LOUP_GAROU && caseJoueur <= nbrDeJoueurs)
					{
						tabVote[caseJoueur] = tabVote[caseJoueur] + 1;
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
	}
	joueurVote = caseAyantLePLusDeVote;
	
	//Si egalite la victime est choisi aleatoirment parmis les joueurs les plus votés
	if (egalite_i == VRAI)
	{
		joueurVote = tabEgalite[rand() % (nCaseAyantLeMemeNombreDeVote + 1)];
	}

	//Annonce du joueur elimine
	char text[35];
	sprintf_s(text, 35, "Vous avez eliminez le Joueur: %d", joueurVote + 1);
	afficherMessage(input, text, .3);

	//On retourne le numero du joueur elimine
	return joueurVote + 1;
}

void fVoyante(GUI* input, Role* tabRoles) {
	//alloue un tableau de tous les joueurs que peut voir la voyante
	unsigned short* joueursAVoir = (unsigned short*)calloc(input->nombreDeJoueur - 1, sizeof(unsigned short));
	
	//verifie l'allocation dynamique
	assert(joueursAVoir);

	//Annonce du reveille
	afficherMessage(input, "La voyante se reveille", .2);

	int j = 0;
	
	//parcours le tableau des roles
	for (unsigned short i = 0; i < input->nombreDeJoueur; i++)
	{
		if (tabRoles[i] != ROLE_VOYANTE && tabRoles[i] != ROLE_MORT) {
			joueursAVoir[j] = (unsigned short)(i + 1);
			j++;
		}	
	}

	//la yoyante choisit un joueurs
	unsigned short joueurAVoir = choisirUnJoueur(input, joueursAVoir, input->nombreDeJoueur - 1, "la voyante choisit un Joueur a demasquer", .4);

	montrerLeRoleDuJoueur(input, tabRoles[joueurAVoir - 1], joueurAVoir);

	free(joueursAVoir);
}

void fCupidon(GUI* input, Role* tabRoles, unsigned short tabCupidon[])
{
	unsigned short caseCupidon = 1;
	unsigned short tabJoueur[18] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };
	char text[57];
	unsigned short buf;

	afficherMessage(input, "Cupidon se reveille", .2);

	//Recherche de cupidon
	while (tabRoles[caseCupidon - 1] == ROLE_CUPIDON) caseCupidon++;

	//demande le premier joueur du couple
	sprintf_s(text, 56, "Cupidon, Joueur %d, doit choisir le 1er Joueur du couple", caseCupidon);
	tabCupidon[0] = choisirUnJoueur(input, tabJoueur, input->nombreDeJoueur, text, .5);

	//enleve ce joueur du tableau
	buf = tabJoueur[tabCupidon[0] - 1];
	tabJoueur[tabCupidon[0] - 1] = tabJoueur[input->nombreDeJoueur - 1];
	tabJoueur[input->nombreDeJoueur - 1] = buf;

	//demande le 2eme joueur du couple
	sprintf_s(text, 57, "Cupidon, Joueur %d, doit choisir le 2eme Joueur du couple", caseCupidon);
	tabCupidon[1] = choisirUnJoueur(input, tabJoueur, input->nombreDeJoueur - 1, text, .5);
}

void fPetiteFille(GUI* input, Role* tabRoles, unsigned short nbrDeJoueursEnVie) {
	unsigned char text[28] = "la petite fille se reveille";
	text[20] = 233;
	afficherMessage(input, text, .3);

	unsigned short nbrLoupGarou = 0;
	unsigned short loups[4];
	for (unsigned short i = 0; i < nbrDeJoueursEnVie; i++)
	{
		if (tabRoles[i] == ROLE_LOUP_GAROU) {
			loups[nbrLoupGarou] = i + 1;
			nbrLoupGarou++;
		}
		assert(nbrLoupGarou < 5);
	}

	if (!nbrLoupGarou) return;

	char buffer[200] = { 0 };

	sprintf_s(buffer, 200, "les loups garous sont les Joueurs : %d", loups[0]);

	for (size_t i = 1; i < nbrLoupGarou; i++)
	{
		size_t offset = 37 + ((i - 1) * 3);
		sprintf_s(buffer + offset, 200 - offset, ", %d", loups[i]);
	}

	afficherMessage(input, buffer, .5);
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
	//Tableau
	unsigned short tabVoleur[19];
	Role tabVoleurChoix[2] = {0,1};
	//booleen
	bool attribue;
	//Mise en place de l'aleatoire
	time_t t;
	srand((unsigned)time(&t));

	//on cherche qui est le voleur
	while (tabRoles[numeroJoueur] != ROLE_VOLEUR)
	{
		numeroJoueur += 1;
	}

	//Annonce du reveille
	afficherMessage(input, "Le voleur se reveille", .2);
	
	////Remplissage de tab Voleur avec les roles non attribues
	//Remplissage avec des roles villageaois
	initTabShort(tabVoleur, 19, ROLE_VILLAGEOIS);

	//AJout des roles loupgarou non-attribue
	tabVoleur[0] = ROLE_LOUP_GAROU;
	caseTabVoleur = 1;
	if (nbrDeJoueurs < 11)
	{
		tabVoleur[1] = ROLE_LOUP_GAROU;
		caseTabVoleur += 1;
	}

	//Ajout des autres roles (different de villageois et loupgarou)
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

	//choix aleatoire des deux roles parmis lequel le voleur fera son choix
	flecheTabVoleur = 19 - nbrDeJoueurs;
	
	nAlea = rand() % flecheTabVoleur;
	tabVoleurChoix[0] = tabVoleur[nAlea];
	echangeCase2(tabVoleur, nAlea, 18);

	flecheTabVoleur -= 1;
	nAlea = rand() % flecheTabVoleur;
	tabVoleurChoix[1] = tabVoleur[nAlea];

	//Le voleur choisi quel roles il souhaite voler et attribution de ce dernier
	roleChoisi = choisirUneCarte(input, tabVoleurChoix);
	tabRoles[numeroJoueur] = roleChoisi;
}

bool fSorciere(GUI* input, Role* tabRoles, bool* peutTuer, bool* peutSauver, short joueurTuee, unsigned short nbrDeJoueurEnVie, unsigned short* joueursTueParLaSorciere)
{
	unsigned short i;
	unsigned short j = 0;
	Actions action;
	//tab
	unsigned short tabJoueurEnVie[18];

	afficherMessage(input, "la sorciere se reveille", .3);

	action = ActionsSorciere(input, *peutTuer, *peutSauver, joueurTuee);

	//Action de tuer
	if (action == SORCIERE_TUER)
	{
		*peutTuer = false;
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
		*peutSauver = false;
		return true;
	}
	return false;
}

int fChasseur(GUI* input, Role* tabRoles) {
	unsigned short joueursATuer[17];
	int j = 0;

	for (size_t i = 0; i < input->nombreDeJoueur; i++)
	{
		if (tabRoles[i] != ROLE_CHASSEUR && tabRoles[i] != ROLE_MORT) {
			joueursATuer[j] = i + 1;
			j++;
		}
	}
	unsigned char text[59] = "le Chasseur doit choisir un Joueur a tuer avant de mourrir";
	text[35] = 224;

	return choisirUnJoueur(input, joueursATuer, j, text, .6);
}

unsigned short LeRoleExiste(Role* roles, unsigned short size,  Role role) {
	for (unsigned short i = 0; i < size; i++)
	{
		if (roles[i] == role) return i;
	}
	return 20;
}

bool partieEstFinie(Role* rolesEnVies, unsigned short nbrDeJoueursEnVie) {
	bool IlnyAQueDesLoups = true;
	for (unsigned short i = 0; i < nbrDeJoueursEnVie; i++)
	{
		if (rolesEnVies[i] != ROLE_LOUP_GAROU && rolesEnVies[i] != ROLE_MORT) {
			IlnyAQueDesLoups = false;
			break;
		}
	}
	return (LeRoleExiste(rolesEnVies, nbrDeJoueursEnVie, ROLE_LOUP_GAROU) == 20 || IlnyAQueDesLoups);
}

void tuerJoueur(unsigned short joueurATuer, Role* roles, unsigned short* couple, 
	unsigned short joueursTue[], unsigned short* nbrJoueursTue) {
	
	roles[joueurATuer - 1] = ROLE_MORT;

	joueursTue[*nbrJoueursTue] = joueurATuer;
	(*nbrJoueursTue)++;
	

	if (joueurATuer == couple[0]) {
		roles[couple[1] - 1] = ROLE_MORT;

		joueursTue[*nbrJoueursTue] = couple[1];
		(*nbrJoueursTue)++;
	}
	else if (joueurATuer == couple[1]) {
		roles[couple[0] - 1] = ROLE_MORT;

		joueursTue[*nbrJoueursTue] = couple[0];
		(*nbrJoueursTue)++;
	}
}

void afficherLesMorts(GUI* input, unsigned short *nbrDeJoueursTue, unsigned short* joueursTue, unsigned short* couple, Role* roles, Role* rolesEnVie, unsigned short* capitaine) {
	for (size_t i = 0; i < *nbrDeJoueursTue; i++)
	{
		if (roles[joueursTue[i] - 1] == ROLE_CHASSEUR) {
			tuerJoueur(fChasseur(input, rolesEnVie), rolesEnVie, couple, joueursTue, nbrDeJoueursTue);
		}
		if (joueursTue[i] == *capitaine) {

			unsigned short joueursEnVie[17] = { 0 };
			int j = 0;
			for (size_t i = 0; i < input->nombreDeJoueur; i++)
			{
				if (rolesEnVie[i] != ROLE_MORT) {
					joueursEnVie[j] = i + 1;
					j++;
				}
			}

			*capitaine = choisirUnJoueur(input, joueursEnVie, j, "le capitaine est mort, il doit en choisir un nouveau", .55);
		}
	}
}

void deroulementDeLaPartie(GUI* input, Role* roles){
	//permet de savoir si la sorciere a encore ses potions
	bool SorcierePotionTuer = true;
	bool SorcierePotionSauver = true;
	//permet de savoir si la sorciere viens d'utiliser ses potions
	bool SorciereAguerit = false;
	bool SorciereAtuer = false;

	//creer une copie du tableau des roles
	Role* rolesEnVie = (Role*)malloc(sizeof(Role) * input->nombreDeJoueur);
	//verifie que l'allocation a fonctioner
	assert(rolesEnVie);
	//rempli ce tableau
	for (size_t i = 0; i < input->nombreDeJoueur; i++) rolesEnVie[i] = roles[i];

	//stocke le nbr de joueurs en vie
	unsigned short nbrDeJoueursEnVie = input->nombreDeJoueur;
	//stocke les deux joueurs qui sont en couple
	unsigned short couple[2] = {0};
	//stocke le joueur qui est capitaine
	unsigned short capitaine = 20;

	//joue une animation pour montrer le role de chaque joueurs un a un
	montrerLeRoleDeChaqueJoueurs(input, roles);

	//election capitaine
	capitaine = voteCapitaine(input) + 1;

	//debute la nuit
	afficherMessage(input, "le village s'endort !", .17f);

	//appelle le voleur en debut de partie si il existe
	unsigned short posVoleur = LeRoleExiste(rolesEnVie, nbrDeJoueursEnVie, ROLE_VOLEUR);
	if (posVoleur != 20) {
		fVoleur(input, rolesEnVie);
		//change le role du voleur aussi dans l'ancien tableau des roles
		roles[posVoleur] = rolesEnVie[posVoleur];
	}
		
	//appelle cupidon en début de partie
	if (LeRoleExiste(rolesEnVie, nbrDeJoueursEnVie, ROLE_CUPIDON) != 20) {
		fCupidon(input, rolesEnVie, couple);
		
		//creer une chaine de charactere sans charactere speciaux
		char text[100];
		sprintf_s(text, 100, "les amoureux sont les Joueurs %d et %d", couple[0], couple[1]);
		afficherMessage(input, text, .4);
	}

	//boucle de jeu
	do{
		//permet de stocker les joueurs morts
		unsigned short nbrJoueursTue = 0;
		unsigned short joueursTue[4] = { 0 };

		//appelle la voyante si elle existe
		if (LeRoleExiste(rolesEnVie, input->nombreDeJoueur, ROLE_VOYANTE) != 20) {
			fVoyante(input, rolesEnVie);
		}

		//appelle les  loups 
		unsigned short joueursTueParLaSorciere = 20;
		unsigned short joueursTueParLesLoups = fLoupgarou(input, rolesEnVie, nbrDeJoueursEnVie);
		tuerJoueur(joueursTueParLesLoups, rolesEnVie, couple, joueursTue, &nbrJoueursTue);

		//appelle la petite-fille si ele existe
		if (LeRoleExiste(rolesEnVie, input->nombreDeJoueur, ROLE_PETITE_FILLE) != 20)
			fPetiteFille(input, rolesEnVie, input->nombreDeJoueur);
		
		//appelle la sorciere si elle existe
		if (LeRoleExiste(rolesEnVie, input->nombreDeJoueur, ROLE_SORCIERE) != 20 && (SorcierePotionTuer || SorcierePotionSauver)) {
			//si la sorciere a choisi de sauver
			if (fSorciere(input, rolesEnVie, &SorcierePotionSauver, &SorcierePotionTuer, joueursTueParLesLoups, nbrDeJoueursEnVie, &joueursTueParLaSorciere)) {
				for (size_t i = 0; i < nbrJoueursTue; i++)
				{
					rolesEnVie[joueursTue[i] - 1] = roles[joueursTue[i] - 1];
				}
				nbrJoueursTue = 0;
				SorciereAguerit = true;
			}
			//si la sorciere a choisi de tuer
			else if (joueursTueParLaSorciere != 20) {
				tuerJoueur(joueursTueParLaSorciere, rolesEnVie, couple, joueursTue, &nbrJoueursTue);
				SorciereAtuer = true;
			}
		}
		//test si la partie c'est pas finie
		if (partieEstFinie(rolesEnVie, input->nombreDeJoueur)) break;

		//affiche le village se reveille
		{
			unsigned char text[100] = "le village se reveille";
			text[15] = 233;
			afficherMessage(input, text, .2);
		}

		//annonce de l'action de la sorciere
		if (SorciereAguerit)
		{
			unsigned char text[42] = "La sorciere a sauver quelqu un cette nuit";
			text[8] = 232;
			afficherMessage(input, text, .4);
			SorciereAguerit = false;
		}
		if (SorciereAtuer)
		{
			unsigned char text[42] = "La sorciere a tuer quelqu un cette nuit";
			text[8] = 232;
			afficherMessage(input, text, .4);
			SorciereAtuer = false;
		}

		//affichage des joueurs morts
		if (nbrJoueursTue > 0) {
			afficherLesMorts(input, &nbrJoueursTue, joueursTue, couple, roles, rolesEnVie, &capitaine);

			//creer une chaine de characteres
			char text[100];
			sprintf_s(text, 100, "les Joueurs morts sont : %d", joueursTue[0]);

			//ajoute le numero de tous des joueurs tué a la chaine des charactere
			for (size_t i = 1; i < nbrJoueursTue; i++)
			{
				//calcule la position du texte a ajouter
				size_t offset = 26 + (i - 1) * 4;
				//ajoute le texte sur la chaine deja existante avec un decalage
				sprintf_s(text + offset , 100 - offset, ", %d ", joueursTue[i]);
			}
			//affiche la chaine finale
			afficherMessage(input, text, .35);

			//montre le role de chacun des joueurs tue
			for (unsigned short i = 0; i < nbrJoueursTue; ++i) {
				montrerLeRoleDuJoueur(input, roles[joueursTue[i] - 1], joueursTue[i]);
			}
		}
		//affiche si il y a eu aucun morts
		else afficherMessage(input, "il n'y a eu aucun mort cette nuit", .4);

		//reduit le nombre de joueurs en vie
		nbrDeJoueursEnVie -= nbrJoueursTue;
		//remet le compteur de mort a zero pour le vote des villageois qui va suivre
		nbrJoueursTue = 0;

		afficherMessage(input, "Les villageois doivent voter pour un Joueur a tuer", .4);
		//vote des villageois
		unsigned short joueurVote = voteFinDeTour(input, rolesEnVie, nbrDeJoueursEnVie, capitaine);
		tuerJoueur(joueurVote + 1, rolesEnVie, couple, joueursTue, &nbrJoueursTue);

		//affiche le role du joueur tue par les villageois
		montrerLeRoleDuJoueur(input, roles[joueurVote], joueurVote + 1);
		if (nbrJoueursTue == 2) {
			//creer une chaine de chjaractere non spéciaux
			char buffer[37];
			sprintf_s(buffer, 37, "le Joueur %d etais en couple avec %d", joueursTue[0], joueursTue[1]);
			//ajoute des caracteres spéciaux au text
			unsigned char text[37];
			for (int i = 0; i < 37; i++) text[i] = buffer[i];
			//si le nombre fait 2 chiffre alors ajouté un a la pos du charactere special
			text[12 + (joueursTue[0] > 10)] = 233;
			afficherMessage(input, text, .4);
		}
		//verifie que le joueur tue n'etais pas en couple ou chasseur
		afficherLesMorts(input, &nbrJoueursTue, joueursTue, couple, roles, rolesEnVie, &capitaine);
		
		//reduit le nbr de joueurs en vie
		nbrDeJoueursEnVie -= nbrJoueursTue;

		//finit la boucle si il n'y a plus de loups ou si il n'y a plus que des loups
	} while (!partieEstFinie(rolesEnVie, input->nombreDeJoueur));


	//affichage du vainqueur : 
	//si il n'y as pas de loups
	if (LeRoleExiste(rolesEnVie, input->nombreDeJoueur, ROLE_LOUP_GAROU) != 20)
	{
		//creer une chaine de charactere speciaux
		unsigned char text[19] = "Les loups on gagne";
		//met un 'é' a la position 17 de la chaine
		text[17] = 233;
		afficherMessage(input, text, .2);
	}
	//si il y a des loups
	else
	{
		//creer une chaine de charactere speciaux
		unsigned char text[19] = "Le village a gagne";
		//met un 'é' a la position 17 de la chaine
		text[17] = 233;
		afficherMessage(input, text, .2);
	}

	//libere le tableau alloué dynamiquement pour stocker les roles des joueurs
	free(rolesEnVie);
}
