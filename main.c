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

    unsigned short ptr[2];
    fSorciere(&input, roles, true, true, 1, input.nombreDeJoueur, ptr);
    printf("a tuer : %d", *ptr);

    //verifie l'allocation dynamique
    assert(roles);

    
    fPetiteFille(&input, roles, input.nombreDeJoueur);

    unsigned short amoureux[2];
    fCupidon(&input, roles, amoureux);

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
