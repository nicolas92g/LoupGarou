#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "interface.h"

#define PROJECT_PATH "../../../../OneDrive/Documents/GitHub/LoupGarou/"

int main() {

    GLFWwindow* fenetre;
    creerLaFenetre(&fenetre);

    //couleur d'arriere plan
    glClearColor(0.7f, 1, 1, 1.0f);

    //active la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    unsigned int shader = compilerLeShader(PROJECT_PATH"default.vert", PROJECT_PATH"default.frag");
    unsigned int VAO = creerUnCarre();
    unsigned int texture = chargerUneTexture(PROJECT_PATH"image.png");

    Uniform projectionUniform = make_Uniform("projection", shader);
    Uniform tailleUniform = make_Uniform("taille", shader);
    Uniform positionUniform = make_Uniform("position", shader);

    while (!glfwWindowShouldClose(fenetre))
    {
        static mat4x4 projection;
        static mat4x4 model;
        static mat4x4 translation;
        static mat4x4 taille;
        
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        int width, height;
        glfwGetWindowSize(fenetre, &width, &height);
        projection = ProjectionOrthographique(0, width, 0, height, -1.0f, 10.0f);

        glUniformMatrix4fv(projectionUniform.location, 1, GL_FALSE, &projection.line0.x);
        
        taille = matriceDeTaille(100, 100, 10);
        translation = matriceDeTranslation(100, 100, 0);
        //model =  multiplicationDeMatrices(&taille, &translation);

        glUniformMatrix4fv(tailleUniform.location, 1, GL_FALSE, &taille.line0.x);
        glUniformMatrix4fv(positionUniform.location, 1, GL_FALSE, &translation.line0.x);
        
        printf("my function\n");
        printf("----\n\n");
        for (size_t i = 0; i < 16; i++)
        {
            printf("%f\t ", (&taille.line0.x)[i]);
            if (!((i + 1) % 4)) {
                printf("\n");
            }
        }
        printf("\n----");
        //exit(0);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glfwSwapBuffers(fenetre);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
