/*****************************************************************//**
 * \file   interface.h
 * \brief  quelques fonctions pour creer un affichage avec opengl
 * \author nicolas GUILLOT
 * \date   May 2021
 *********************************************************************/

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

//IMPORTANT ! definit le chemin ou sont stockées les textures sur l'ordi
#define PROJECT_PATH "../../../../OneDrive/Documents/GitHub/LoupGarou/"

/**
 * @brief definit un boutton 2D, sa position et les différentes textures qu'il peut avoir
 */
typedef struct Boutton {
	int x;							//position x   (en pixel)
	int y;							//position y   (en pixel)
	int h;							// hauteur 	   (en pixel)
	int l;							// largeur	   (en pixel)
	unsigned int textureDefault;	//texture affichée par default
	unsigned int textureHover;		//texture affichée quand le curseur survole le boutton
	unsigned int textureCliquer;	//texture affichée que=and ce boutton est cliquer
	float alpha;					//permet d'ajouter de la transparence
	vec4 filter;					//permet d'ajouter une couleur 
	GLFWwindow* win;				//une fenetre 
	bool clicker;					//permet de savoir si le boutton est clicker
	bool hover;						//permet de savoir si le boutton est survolé
} Boutton;
/**
 * @brief definit une carte de loup-garou en 3D
 */
typedef struct Carte {
	vec4 position;					//position 3d de la carte
	vec4 axeRotation;				//axe de rotation de la carte
	float angle;					//angle de rotation de la carte
	unsigned int textureRecto;		//texture du recto de la carte
	unsigned int textureVerso;		//texture du verso de la carte

} Carte;

/**
 * @brief creer une fenetre avec glfw
 * @param un double pointeur vers une fenetre
 */
void creerLaFenetre(GLFWwindow** window);
/**
 * @brief creer un const char* contenant le contenu d'un fichier 
 * @param chemin vers ce fichier
 * @return une chaine de charactere avec le contenu du fichier 
 */
char* fichierVersString(const char* filename);
/**
 * @brief creer une pipeline opengl a partir de deux fichier (.vert et .frag)
 * @param un chemin vers un fichier contenant un vertex shader
 * @param un chemin vers un fichier contenant un fragment shader
 */
unsigned int compilerLeShader(const char* vertexShaderPath, const char* fragmentShaderPath);
/**
 * @brief creer un carre 
 * @return un Vertex Array
 */
unsigned int creerUnCarre();
/**
 * @brief creer une texture a partir d'un fichier (.png, .jpg, etc..)
 * @param un chemin vers une image
 */
unsigned int chargerUneTexture(const char* path);
/**
 * @brief sert de constructeur a la struct Boutton
 * @param position x	 (en pixel)
 * @param position y	 (en pixel)
 * @param h : hauteur	 (en pixel)
 * @param l : largeur 	 (en pixel)
 * @param defaultTex : une texture qui sera assigné a toutes les textures
 * @param win : une fenetre pour recuperer la position du curseur
 */
Boutton make_Boutton(int x, int y, int h, int l, unsigned int defaultTex, GLFWwindow* win);

/**
 * @brief permet de changer rapidement les textures d'un boutton
 */
void setBouttonTextures(Boutton* boutton, unsigned int whenHover, unsigned int whenClicked);
/**
 * @brief affiche et test si le boutton est cliquer ou survolé
 * @param un pointeur vers un boutton
 * @param un shader avec lequel afficher ce boutton
 */
void afficherBoutton(Boutton* boutton, unsigned int shader);
/**
 * @brief creer une carte de loup garou 3D
 */
Carte make_Carte(unsigned int texture);
/**
 * @brief afficher une carte
 */
void afficherCarte(Carte* carte, unsigned int shader);

#endif // !INTERFACE