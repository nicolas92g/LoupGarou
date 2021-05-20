#include "interface.h"

int main() {
    
    GLFWwindow* fenetre;
    creerLaFenetre(&fenetre);

    GUI input = make_GUI(fenetre);

    unsigned short joueurs[18] = { 1, 12, 3, 8, 5, 6, 7, 4, 9, 10, 11, 2, 13, 14, 15, 16, 17, 18 };

    printf("%d\n", choisirUnJoueur(&input, joueurs, 18, "choisisez un Joueur a tuer", .28));

    recupererLeNombreDeJoueurs(&input);

    ActionsSorciere(&input, false, true, 12);

    Role roles[18];

    for (size_t i = 0; i < input.nombreDeJoueur; i++)
        roles[i] = rand() % 7;
    

    montrerLeRoleDeChaqueJoueurs(&input, roles);

    montrerLeRoleDuJoueur(&input, ROLE_CHASSEUR, 2);
    montrerLeRoleDuJoueur(&input, ROLE_CUPIDON, 4);
    montrerLeRoleDuJoueur(&input, ROLE_VILLAGEOIS, 18);
    montrerLeRoleDuJoueur(&input, ROLE_CHASSEUR, 10);


    //finir le programme
    detruire_GUI(&input);
    glfwDestroyWindow(fenetre);
    glfwTerminate();
    return 0;
}
