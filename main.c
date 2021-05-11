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
    Uniform modelUniform = make_Uniform("model", shader);

    while (!glfwWindowShouldClose(fenetre))
    {
        static mat4x4 projection;
        static mat4x4 model;
        static mat4x4 taille;
        static mat4x4 translation;
        static mat4x4 rotation;
        
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        int width, height;
        glfwGetWindowSize(fenetre, &width, &height);

        glViewport(0, 0, width, height);
        //projection = projectionPerspective(((float)width / (float)height), PI * .5f, 0.1f, 100.0f);
        projection = ProjectionOrthographique(0, width, 0, height, -1.0f, 10.0f);

        glUniformMatrix4fv(projectionUniform.location, 1, GL_FALSE, &projection.col0.x);

        taille = matriceDeTaille(100, 100, 1);
        translation = matriceDeTranslation(200, 100, 0);
        rotation = matriceDeRotation(make_vec4(0, 1, 0, 0), PI * .3f * glfwGetTime());

        mat4x4 modelIntermediaire = multiplicationDeMatrices(&translation, &taille);
        model = multiplicationDeMatrices(&modelIntermediaire, &rotation);

        glUniformMatrix4fv(modelUniform.location, 1, GL_FALSE, &model.col0.x);
        
        
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
