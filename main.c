#include "interface.h"

int main() {
 
    int caseCapitaine;
    int caseJoueurELimine;
    int nDeJoueurEnVie;
    
   GLFWwindow* fenetre;
   creerLaFenetre(&fenetre);

    GUI input = make_GUI(fenetre);
    recupererLeNombreDeJoueurs(&input);
    nDeJoueurEnVie = input.nombreDeJoueur;

    Role roles[18];

    attribution(roles, input.nombreDeJoueur);

    montrerLeRoleDeChaqueJoueurs(&input, roles);

   caseCapitaine = voteCapitaine(&input);

   caseJoueurELimine = voteFinDeTour(&input, roles, input.nombreDeJoueur, nDeJoueurEnVie, caseCapitaine);

    //finir le programme
    detruire_GUI(&input);
    glfwDestroyWindow(fenetre);
    glfwTerminate();
    return 0;
}


/*int caseJoueur = 0;
unsigned short tabJoueur[18] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 };
for (i = 0; i < nbrDeJoueurs; i++)
{
	vote_i = FAUX;

	while (!vote_i)
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
	}
}*/