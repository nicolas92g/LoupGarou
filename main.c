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

   // Role ro[2] = { 0, 3 };
    //printf("role : %d\n",choisirUneCarte(&input, ro));

    //recupere le nbr de joueurs et alloue un tableau de cette taille
    recupererLeNombreDeJoueurs(&input);
    Role* roles = (Role*)calloc(input.nombreDeJoueur, sizeof(Role));

    //verifie l'allocation dynamique
    assert(roles);

    attribution(roles, input.nombreDeJoueur);
    //fPetiteFille(&input, roles, input.nombreDeJoueur);

   // unsigned short amoureux[2];
   //fCupidon(&input, roles, amoureux);

    roles[0] = ROLE_VOLEUR;

    montrerLeRoleDeChaqueJoueurs(&input, roles);

    fVoleur(&input, roles);

    //caseCapitaine = voteCapitaine(&input);
    
    //caseJoueurELimine = voteFinDeTour(&input, roles, input.nombreDeJoueur, caseCapitaine);

    //finir le programme
    free(roles);
    detruire_GUI(&input);
    glfwDestroyWindow(fenetre);
    glfwTerminate();
    return 0;
}
