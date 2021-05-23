/*****************************************************************//**
 * \file   main.c
 * \brief  Jeux de Loups Garou
 * 
 * \author Thibault GARCIA-MEGEVAND, Nicolas GUILLOT, david DEL CAMPO 
 * \date   May 2021
 *********************************************************************/
 
 //inclue tous les fichiers
#include "jeux.h"

//fonction principale
int main() {

    //creer la fenetre
    GLFWwindow* fenetre;
    creerLaFenetre(&fenetre);

    //creer l'interface graphique
    GUI input = make_GUI(fenetre);
   
    //recupere le nbr de joueurs et alloue un tableau de cette taille
    recupererLeNombreDeJoueurs(&input);
    Role* roles = (Role*)calloc(input.nombreDeJoueur, sizeof(Role));

    //attribue un role a chaque joueurs
    attribution(roles, input.nombreDeJoueur);

    //commence la partie
    deroulementDeLaPartie(&input, roles);
    
    //finir le programme
    free(roles);
    detruire_GUI(&input);
    glfwDestroyWindow(fenetre);
    glfwTerminate();
    return EXIT_SUCCESS;
}