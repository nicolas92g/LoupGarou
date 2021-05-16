#include "interface.h"

int main() {
    
    GLFWwindow* fenetre;
    creerLaFenetre(&fenetre);
    
    GUI affichage = make_GUI(fenetre);

    do
    {
        afficherGUI(&affichage);
    }
    while (!glfwWindowShouldClose(fenetre));

    detruire_GUI(&affichage);

    glfwTerminate();
    return 0;
}
