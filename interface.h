#ifndef INTERFACE
#define INTERFACE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define PI 3.141592

typedef struct vec4 {
	float x;
	float y;
	float z;
	float w;
} vec4;

typedef struct mat4x4 {
	vec4 col0;
	vec4 col1;
	vec4 col2;
	vec4 col3;
}mat4x4;

typedef struct Uniform {
	const char* name;
	unsigned int location;
}Uniform;

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

Uniform make_Uniform(const char* name, unsigned int shader);

float carre(float a);

vec4 make_vec4(float x, float y, float z, float w);
vec4 multiplie(vec4 vec, float f);
vec4 additionne(vec4 v1, vec4 v2);

/**
 * @brief creer une matrice de projection orthographique (sans perspective) adapté au 2D
 */
mat4x4 ProjectionOrthographique(float left, float right, float bottom, float top, float zNear, float zFar);
mat4x4 projectionPerspective(float aspect, float fov, float zNear, float zFar);
mat4x4 matriceDidentite(float facteur);
mat4x4 matriceDeTaille(float x, float y, float z);
mat4x4 matriceDeTranslation(float x, float y, float z);
mat4x4 matriceDeRotation(vec4 axe, float angle);
mat4x4 multiplicationDeMatrices(mat4x4* m1, mat4x4* m2);
mat4x4 matriceDeVue(const vec4 eyePos, const vec4 lookAt, const vec4 up);
vec4 produitVectoriel(vec4 A, vec4 B);
vec4 normalise(vec4 a);

#endif // !INTERFACE