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

//IMPORTANT ! definit le chemin ou sont stock�es les textures sur l'ordi
#define PROJECT_PATH "../../../../OneDrive/Documents/GitHub/LoupGarou/"

//evite de clicker instantanement sur le boutton de l'interface d'apres en clickant sur un boutton
#define NBR_MIN_DANS_UN_ETAT 60

/**
 * @permet de stocker un role dans le jeu
 */
typedef enum Role {
	ROLE_LOUP_GAROU,
	ROLE_VILLAGEOIS,
	ROLE_VOYANTE,
	ROLE_PETITE_FILLE,
	ROLE_CUPIDON,
	ROLE_CHASSEUR,
	ROLE_SORCIERE,
	ROLE_VOLEUR
} Role;
/**
 * @brief definit un boutton 2D, sa position et les diff�rentes textures qu'il peut avoir
 */
typedef struct Boutton {
	int x;							//position x   (en pixel)
	int y;							//position y   (en pixel)
	int h;							// hauteur 	   (en pixel)
	int l;							// largeur	   (en pixel)
	unsigned int textureDefault;	//texture affich�e par default
	unsigned int textureHover;		//texture affich�e quand le curseur survole le boutton
	unsigned int textureCliquer;	//texture affich�e que=and ce boutton est cliquer
	float alpha;					//permet d'ajouter de la transparence
	vec4 filter;					//permet d'ajouter une couleur 
	GLFWwindow* win;				//une fenetre 
	bool clicker;					//permet de savoir si le boutton est clicker
	bool hover;						//permet de savoir si le boutton est survol�
	bool viensDetreClicker;			//permet de savoir si l'utilisateur viens de clicker sur le boutton
	bool filtreHover;				//indique a l'affichage si le survol est affich� par une texture ou par un filtre
} Boutton;
/**
 * @brief permet de creer des matrices pour la 3d ou pour la 2d
 */
typedef struct Camera {
	vec4 position;		//position de la camera 3D
	vec4 regard;		//point ou regarde la camera 3D
	GLFWwindow* win;	//fenetre utilis�e
	mat4x4 vue;			//matrice de vue g�n�r�e
	mat4x4 projection;	//matrice de projection g�n�r�e
} Camera;
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
 *@brief structure qui stockent toutes les decorations en rapport avec le loup Garou
 */
typedef struct Decoration {
	//camera pour generer les matrices de vue et de projection
	Camera cam;
	unsigned int shader;// shader pour afficher

	//textures de la carte de chaque roles
	unsigned int loupGarouTexture;
	unsigned int villageoisTexture;
	unsigned int voyanteTexture;
	unsigned int voleurTexture;
	unsigned int petiteFilleTexture;
	unsigned int cupidonTexture;
	unsigned int chasseurTexture;
	unsigned int sorciereTexture;
	unsigned int capitaineTexture;
	//texture du verso d'une carte
	unsigned int versoTexture;

	//chaque Carte est un objet 3D
	Carte carteLoupGarou;
	Carte carteVillageois;
	Carte cartevoyante;
	Carte cartePetiteFille;
	Carte carteCupidon;
	Carte carteChasseur;
	Carte carteSorciere;
	Carte carteVoleur;

} Decoration;
/**
 * @brief decrit l'emsembles des affichages 2D
 */
typedef struct GUI {
	GLFWwindow* fenetre;					//fenetre pour le responsive
	Decoration deco;						//arriere plan en 3D
	Camera cam;								//objet pour generer des matrices 3D ou 2D
	Decoration cartes;						//cartes en 3D

	unsigned int carre;						//VAO pour afficher des images
	unsigned long long nombreDimageDansUnEtat;//compteur d'images
	unsigned int shader;					//shader pour afficher l'interface

	//ecran de depart
	Boutton lancerLaPartie;

	//combien de joueur ?
	Boutton bouttons[11];							//un boutton par nombre de joueurs de 8 a 18
	unsigned int nombresTextures[18];

	unsigned int combienDeJoueurQuestion;	//stocke la texture de la question
	unsigned short nombreDeJoueur;			//stocke la reponse

	unsigned int afficherCarteTexture;		//stocke une texture
	unsigned int cacherCarteTexture;		//stocke une texture

	//assignation des roles
	Role roles[18];
	unsigned short roleAMontrer;

	enum Etat {
		ETAT_ECRAN_DE_DEPART,
		ETAT_COMBIEN_DE_JOUEUR,
		ETAT_ASSIGNATION_DES_ROLES
	} etat;									//permet de stocker quelle page est a afficher
} GUI;

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
 * @param defaultTex : une texture qui sera assign� a toutes les textures
 * @param win : une fenetre pour recuperer la position du curseur
 */
Boutton make_Boutton(int x, int y, int h, int l, unsigned int defaultTex, GLFWwindow* win);

/**
 * @brief permet de changer rapidement les textures d'un boutton
 */
void setBouttonTextures(Boutton* boutton, unsigned int whenHover, unsigned int whenClicked);
/**
 * @brief affiche et test si le boutton est cliquer ou survol�
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
/**
 * @brief creer une objet de type decoration
 */
Decoration make_Decoration(GLFWwindow* fenetre);
/**
 * @brief animation pour l'ensemble des decorations
 */
void rotationsEnCercle(Decoration* deco);
/**
 * animation d'une carte qui se devoile
 */
void carteQuiSeDevoile(Decoration* deco, Role role);
/**
 * @brief creer une camera
 */
Camera make_Camera(GLFWwindow* fenetre);
/**
 * @brief creer une prise de vue en 3D 
 * @param un pointeur vers une camera
 * @param un shader ou envoyer les matrices
 */
void updateCamera3D(Camera* cam, unsigned int shader);
/**
 * @brief creer une prise de vue en 2D
 * @param un pointeur vers une camera
 * @param un shader ou envoyer les matrices
 */
void updateCamera2D(Camera* cam, unsigned int shader);
/**
 * @brief creer une interface permettant l'interaction utilisateur 
 */
GUI make_GUI(GLFWwindow* fenetre);
/**
 * @brief affiche l'interface utilisateur
 */
void afficherGUI(GUI* inte);
/**
 * @brief detruit l'objet GUI
 */
void detruire_GUI(GUI* input);

#endif // !INTERFACE