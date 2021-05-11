#ifndef INTERFACE
#define INTERFACE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glmath.h"
#include <stdbool.h>

#define PI 3.141592

/**
 * @brief definit une variable shader de type uniform
 */
typedef struct Uniform {
	const char* name;
	unsigned int location;
}Uniform;
/**
 * @brief definit un boutton 2D, sa position et les différentes textures qu'il peut avoir
 */
typedef struct Boutton {
	int x;		//position x   (en pixel)
	int y;		//position y   (en pixel)
	int h;		// hauteur 	   (en pixel)
	int l;		// largeur	   (en pixel)
	unsigned int textureDefault;
	unsigned int textureHover;
	unsigned int textureCliquer;
	GLFWwindow* win;
	bool clicker;
	bool hover;
} Boutton;

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
/**
 * @brief creer une texture a partir d'un fichier (.png, .jpg, etc..)
 */
unsigned int chargerUneTexture(const char* path);
/**
 * @brief permet de creer un uniform 
 * @param nom de la variable dans le shader
 * @param id du shader en question
 */
Uniform make_Uniform(const char* name, unsigned int shader);

Boutton make_Boutton(int x, int y, int h, int l, unsigned int defaultTex, GLFWwindow* win);

/**
 * @brief permet de changer rapidement les textures d'un boutton
 */
void setBouttonTextures(Boutton* boutton, unsigned int whenHover, unsigned int whenClicked);

void afficherBoutton(Boutton* boutton, unsigned int shader);

#endif // !INTERFACE