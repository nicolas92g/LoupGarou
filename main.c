#include "interface.h"

int main() {
    
    GLFWwindow* fenetre;
    creerLaFenetre(&fenetre);

    GUI input = make_GUI(fenetre);
    recupererLeNombreDeJoueurs(&input);

    Role roles[18];

    
    
    montrerLeRoleDeChaqueJoueurs(&input, roles);


    //finir le programme
    detruire_GUI(&input);
    glfwDestroyWindow(fenetre);
    glfwTerminate();
    return 0;
}