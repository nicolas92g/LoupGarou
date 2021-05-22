#include "interface.h"
#include "jeux.h"

int main() {
    int caseCapitaine;      //indique le joueur qui est capitaine
    int caseJoueurELimine;  
    
    //creer la fenetre
    GLFWwindow* fenetre;
    creerLaFenetre(&fenetre);

    //creer l'interface graphique
    GUI input = make_GUI(fenetre);


    //recupere le nbr de joueurs et alloue un tableau de cette taille
    recupererLeNombreDeJoueurs(&input);
    Role* roles = (Role*)calloc(input.nombreDeJoueur, sizeof(Role));

    attribution(roles, input.nombreDeJoueur);

    deroulementDeLaPartie(&input, roles);

    //finir le programme
    free(roles);
    detruire_GUI(&input);
    glfwDestroyWindow(fenetre);
    glfwTerminate();
    return 0;
}
