#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * @brief creer une fenetre avec glfw
 * @param un pointeur vers une fenetre
 */
void creerLaFenetre(GLFWwindow** window);
/**
 * @brief creer un const char* contenant le contenu d'un fichier 
 * @param chemin vers ce fichier
 */
char* fichierVersString(const char* filename);
/**
 * @brief creer une pipeline opengl a partir de deux fichier (.vert et .frag)
 * @param un chemin vers un fichier contenant un vertex shader
 * @param un chemin vers un fichier contenant un fragment shader
 */
unsigned int compilerLeShader(const char* vertexShaderPath, const char* fragmentShaderPath);
/**
 * @brief rempli un vertex Array avec un carre
 */
unsigned int creerUnCarre();