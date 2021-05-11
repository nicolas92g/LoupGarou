/*****************************************************************//**
 * \file   glmath.h
 * \brief  quelques outils mathématiques pour la 3D et la 2D (les algo viennent d'internet et de glm)
 * \author nicolas
 * \date   May 2021
 *********************************************************************/

#ifndef GLMATH
#define GLMATH

#include <math.h>

/**
 * @brief definit un vecteur ou tableau de 4 float
 */
typedef struct vec4 {
	float x;
	float y;
	float z;
	float w;
} vec4;

/**
 * @brief definit une matrice 4 x 4
 */
typedef struct mat4x4 {
	vec4 col0;
	vec4 col1;
	vec4 col2;
	vec4 col3;
}mat4x4;
/**
 * @brief renvoit le carre d'un nombre
 */
float carre(float a);
/**
 * @brief creer un vecteur
 */
vec4 make_vec4(float x, float y, float z, float w);
/**
 * @brief multiplie un vecteur par un nombre reel
 */
vec4 multiplie(vec4 vec, float f);
/**
 * @brief additionne deux vecteur entre eux
 */
vec4 additionne(vec4 v1, vec4 v2);
/**
 * @brief creer une matrice de projection orthographique (sans perspective) adapté au 2D
 */
mat4x4 ProjectionOrthographique(float left, float right, float bottom, float top, float zNear, float zFar);
/**
 * @brief creer une matrice 4x4 permettant de simuler un monde 3D
 */
mat4x4 projectionPerspective(float aspect, float fov, float zNear, float zFar);
/**
 * @brief creer un matrice qui ne fait rien (si facteur = 1)
 */
mat4x4 matriceDidentite(float facteur);
/**
 * @brief creer un matrice qui permet de redimensioner un objet 3D selon les 3 axes
 */
mat4x4 matriceDeTaille(float x, float y, float z);
/**
 * @brief creer un matrice qui permet d'effectuer des translations selon les 3 axes
 */
mat4x4 matriceDeTranslation(float x, float y, float z);
/**
 * @brief creer un matrice qui permet d'effectuer des rotations
 */
mat4x4 matriceDeRotation(vec4 axe, float angle);
/**
 * @brief multiplie 2 matrices entre elles
 */
mat4x4 multiplicationDeMatrices(mat4x4* m1, mat4x4* m2);
/**
 * @brief creer une matrice qui modifie la position et la direction de la prise de vue
 */
mat4x4 matriceDeVue(const vec4 eyePos, const vec4 lookAt, const vec4 up);
/**
 * @brief donne le produit vectoriel de 2 vecteurs
 */
vec4 produitVectoriel(vec4 A, vec4 B);
/**
 * @brief donne le produit scalaire de 2 vecteurs
 */
float produitScalaire(vec4 A, vec4 B);
/**
 * @brief modifie un vecteur pour que sa norme soit egale a 1
 */
vec4 normalise(vec4 a);

#endif //GLMATH