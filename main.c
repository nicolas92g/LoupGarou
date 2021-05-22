#include "interface.h"
#include "jeux.h"

int main() {
    int caseCapitaine;
    int caseJoueurELimine;
    
    GLFWwindow* fenetre;
    creerLaFenetre(&fenetre);

    GUI input = make_GUI(fenetre);
    recupererLeNombreDeJoueurs(&input);

    Role *roles = (Role*)calloc(input.nombreDeJoueur, sizeof(Role));

    attribution(roles, input.nombreDeJoueur);

    montrerLeRoleDeChaqueJoueurs(&input, roles);

    caseCapitaine = voteCapitaine(&input);
    
    caseJoueurELimine = voteFinDeTour(&input, roles, input.nombreDeJoueur, caseCapitaine);

    //finir le programme
    free(roles);
    detruire_GUI(&input);
    glfwDestroyWindow(fenetre);
    glfwTerminate();
    return 0;
}
