#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "interface.h"
#include "glmath.h"

#define PROJECT_PATH "../../../../OneDrive/Documents/GitHub/LoupGarou/"

int main() {
    
    GLFWwindow* fenetre;
    creerLaFenetre(&fenetre);

    //couleur d'arriere plan
    glClearColor(0.1f, 0.5, 0.4, 1.0f);

    //active la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    
    
    unsigned int shader = compilerLeShader(PROJECT_PATH"default.vert", PROJECT_PATH"default.frag");
    unsigned int VAO = creerUnCarre();

    unsigned int loupGarouTexture = chargerUneTexture(PROJECT_PATH"loupGarou.png");
    unsigned int villageoisTexture = chargerUneTexture(PROJECT_PATH"villageois.png");
    unsigned int voyanteTexture = chargerUneTexture(PROJECT_PATH"voyante.png");

    Uniform projectionUniform = make_Uniform("projection", shader);
    Uniform modelUniform = make_Uniform("model", shader);
    Uniform vueUniform = make_Uniform("vue", shader);
    Uniform timeUniform = make_Uniform("time", shader);

    Boutton lancer = make_Boutton(100, 100, 30, 100, chargerUneTexture(PROJECT_PATH"lancerUnePartieDefault.png"), fenetre);
    lancer.textureHover = chargerUneTexture(PROJECT_PATH"lancerUnePartieHover.png");

    while (!glfwWindowShouldClose(fenetre))
    {
        mat4x4 projection;
        mat4x4 model;
        mat4x4 taille;
        mat4x4 translation;
        mat4x4 rotation;
        mat4x4 vue;

        int width, height;
        glfwGetWindowSize(fenetre, &width, &height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);
        glUniform1f(timeUniform.location, glfwGetTime());

        //3D
        glDepthFunc(GL_LEQUAL);
        projection = projectionPerspective(((float)width / (float)height), PI * 0.25f, 0.1f, 100.0f);
        vue = matriceDeVue(make_vec4(cos(glfwGetTime()), 0, sin(glfwGetTime()) * 20, 1), make_vec4(0, 0, 0, 1), make_vec4(0, 1, 0, 1));

        glUniformMatrix4fv(vueUniform.location, 1, GL_FALSE, &vue.col0.x);
        glUniformMatrix4fv(projectionUniform.location, 1, GL_FALSE, &projection.col0.x);

        glUseProgram(shader);
        
        taille = matriceDeTaille(3, 3, 1);
        translation = matriceDeTranslation(0.2, -0.5, -glfwGetTime() + 1);
        rotation = matriceDeRotation(make_vec4(0, 0, 1, 0), PI * .3f * (glfwGetTime()));

        mat4x4 modelIntermediaire = multiplicationDeMatrices(&translation, &taille);
        model = multiplicationDeMatrices(&modelIntermediaire, &rotation);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, villageoisTexture);
        glUniformMatrix4fv(modelUniform.location, 1, GL_FALSE, &model.col0.x);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        taille = matriceDeTaille(3, 3, 1);
        translation = matriceDeTranslation(1.3, 0.1, -(glfwGetTime() * .8) - 0.5);
        rotation = matriceDeRotation(make_vec4(0, 0, 1, 0), PI * .2f * glfwGetTime());

        modelIntermediaire = multiplicationDeMatrices(&translation, &taille);
        model = multiplicationDeMatrices(&modelIntermediaire, &rotation);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, loupGarouTexture);
        glUniformMatrix4fv(modelUniform.location, 1, GL_FALSE, &model.col0.x);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //2D
        glDepthFunc(GL_ALWAYS);
        projection = ProjectionOrthographique(0, width, 0, height, -10.0f, 10.0f);
        vue = matriceDidentite(1);
        
        glUniformMatrix4fv(vueUniform.location, 1, GL_FALSE, &vue.col0.x);
        glUniformMatrix4fv(projectionUniform.location, 1, GL_FALSE, &projection.col0.x);

        lancer.l = width * .5f;
        lancer.h = width * .15f;
        lancer.x = width * .5f;
        lancer.y = height * .5f;
        afficherBoutton(&lancer, shader);

        glfwSwapBuffers(fenetre);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
