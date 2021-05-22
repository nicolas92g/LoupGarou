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

#include <ft2build.h>
#include FT_FREETYPE_H

#include "glmath.h"
#include <stdbool.h>

//IMPORTANT ! definit le chemin ou sont stockées les textures sur l'ordi
#define PROJECT_PATH "../../../../OneDrive/Documents/GitHub/LoupGarou/"

//evite de clicker instantanement sur le boutton de l'interface d'apres en clickant sur un boutton
#define NBR_MIN_DANS_UN_ETAT 10

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
	bool viensDetreClicker;			//permet de savoir si l'utilisateur viens de clicker sur le boutton
	bool filtreHover;				//indique a l'affichage si le survol est affiché par une texture ou par un filtre
} Boutton;
/**
 * @brief permet de creer des matrices pour la 3d ou pour la 2d
 */
typedef struct Camera {
	vec4 position;		//position de la camera 3D
	vec4 regard;		//point ou regarde la camera 3D
	GLFWwindow* win;	//fenetre utilisée
	mat4x4 vue;			//matrice de vue générée
	mat4x4 projection;	//matrice de projection générée
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
 * @brief permet de stocker l'ensemble des éléments qu'il faut pour afficher un charactere
 */
typedef struct Charactere {
	unsigned int largeur;
	unsigned int hauteur;
	unsigned int decalageX;
	unsigned int decalageY;
	unsigned int avance;
	unsigned int texture;
} Charactere;
/**
 * @brief permet d'afficher des chaines de characteres a l'ecran
 */
typedef struct AfficheurDeTexte {
	Charactere tableauDeCharacteres[256];
	unsigned int VAO;
	unsigned int VBO;

	GLFWwindow* fenetre;
	unsigned int shader;
} AfficheurDeTexte;
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
	AfficheurDeTexte texte;					//objet permettant d'afficher du texte

	unsigned int carre;						//VAO pour afficher des images
	unsigned long long nombreDimageDansUnEtat;//compteur d'images
	unsigned int shader;					//shader pour afficher l'interface

	//un boutton pour choisir un nombre entre 1 et 18
	Boutton bouttons[18];					//un boutton par joueur

	//ecran de depart
	Boutton lancerLaPartie;

	//combien de joueur ?
	unsigned int nombresTextures[18];

	unsigned short nombreDeJoueur;			//stocke le nombre de joueurs qui veulent jouer


	//assignation des roles
	unsigned short roleAMontrer;

	//sorciere
	Boutton tuer;
	Boutton rienFaire;
	Boutton sauver;

} GUI;
/**
 * @brief permet de stocker l'action que souhaite effectuer un joueur
 */
typedef enum Actions {
	SORCIERE_RIEN_FAIRE,
	SORCIERE_TUER,
	SORCIERE_SAUVER
}Actions;

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
 * @brief fonction affichant l'interface de depart pour demander le nombre de joueurs
 */
void recupererLeNombreDeJoueurs(GUI* input);
/**
 * @brief permet a chaque joueur de savoir son role
 */
void montrerLeRoleDeChaqueJoueurs(GUI* input, Role* roles);
/**
 * @brief utile pour montrer le role d'un joueur a la voyante
 */
void montrerLeRoleDuJoueur(GUI* input, Role role, unsigned short joueur);
/**
 * @brief detruit l'objet GUI
 */
void detruire_GUI(GUI* input);
/**
 * @brief interface permettant de selectionner un joueur parmis une selectionée
 */
unsigned short choisirUnJoueur(GUI* input, unsigned short* listeDeJoueurs, unsigned short nombreDeJoueurs, const unsigned char* message, float textAlignement);
/**
 * @brief creer un afficheur de texte qui peut afficher une police donner en argument
 */
AfficheurDeTexte make_afficheurDeTexte(const char* policeChemin, GLFWwindow* fenetre);
/**
 * @brief afficher avec un afficheur de texte
 * @param scale unité arbitraire 1 = 48 px
 */
void afficherDuTexte(AfficheurDeTexte* r, const unsigned char* text, int x, int y, float scale);
/**
 * @brief permet de demander a la sorciere ce quelle veut faire
 */
Actions ActionsSorciere(GUI* input, bool peutTuer, bool peutSauver, short joueurTue);
/**
 * @brief permet d'afficher un message a l'utilisateur
 */
void afficherMessage(GUI* input, const unsigned char* message, float textAligment);
/**
 * @brief permet au voleur de choisir sa carte
 */
Role choisirUneCarte(GUI* input, Role* roles);
#endif // !INTERFACE