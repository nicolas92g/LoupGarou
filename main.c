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

    while (!glfwWindowShouldClose(fenetre))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        
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
