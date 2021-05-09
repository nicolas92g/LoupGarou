#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "interface.h"

GLFWwindow* fenetre;

#define PROJECT_PATH "../../../../OneDrive/Documents/GitHub/LoupGarou/"

int main() {
    creerLaFenetre(&fenetre);

    glClearColor(0.7f, 1, 1, 1.0f);

    unsigned int shader = compilerLeShader(PROJECT_PATH"default.vert", PROJECT_PATH"default.frag");
    unsigned int VAO = creerUnCarre();

    while (!glfwWindowShouldClose(fenetre))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glfwSwapBuffers(fenetre);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
