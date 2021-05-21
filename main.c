#include "interface.h"

int main() {
 
    int caseCapitaine;
    int caseJoueurELimine;
    int nDeJoueurEnVie;
    
   GLFWwindow* fenetre;
   creerLaFenetre(&fenetre);

    GUI input = make_GUI(fenetre);
    recupererLeNombreDeJoueurs(&input);
    nDeJoueurEnVie = &input;

    Role roles[18];

    attribution(roles, input.nombreDeJoueur);

    montrerLeRoleDeChaqueJoueurs(&input, roles);

   caseCapitaine = voteCapitaine(&input, input.nombreDeJoueur);

   caseJoueurELimine = voteFinDeTour(&input, roles, input.nombreDeJoueur, nDeJoueurEnVie, caseCapitaine);

    //finir le programme
    detruire_GUI(&input);
    glfwDestroyWindow(fenetre);
    glfwTerminate();
    return 0;
}