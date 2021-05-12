#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "interface.h"
#include "glmath.h"

int main() {
    
    GLFWwindow* fenetre;
    creerLaFenetre(&fenetre);

    //couleur d'arriere plan
    glClearColor(.7f, .7f, .7f, 1.0f);

    //active la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //active le test de profondeur
    glEnable(GL_DEPTH_TEST);
    
    
    unsigned int shader = compilerLeShader(PROJECT_PATH"default.vert", PROJECT_PATH"default.frag");
    unsigned int VAO = creerUnCarre();

    unsigned int loupGarouTexture = chargerUneTexture(PROJECT_PATH"loupGarou.png");
    unsigned int villageoisTexture = chargerUneTexture(PROJECT_PATH"villageois.png");
    unsigned int voyanteTexture = chargerUneTexture(PROJECT_PATH"voyante.png");
    unsigned int voleurTexture = chargerUneTexture(PROJECT_PATH"voleur.png");
    unsigned int versoTexture = chargerUneTexture(PROJECT_PATH"verso.png");
    unsigned int petiteFilleTexture = chargerUneTexture(PROJECT_PATH"petiteFille.png");
    unsigned int cupidonTexture = chargerUneTexture(PROJECT_PATH"cupidon.png");
    unsigned int chasseurTexture = chargerUneTexture(PROJECT_PATH"chasseur.png");
    unsigned int sorciereTexture = chargerUneTexture(PROJECT_PATH"sorciere.png");
    unsigned int capitaineTexture = chargerUneTexture(PROJECT_PATH"capitaine.png");

    Carte carteLoupGarou = make_Carte(loupGarouTexture);
    Carte carteVillageois = make_Carte(villageoisTexture);
    Carte cartevoyante = make_Carte(voyanteTexture);
    Carte cartePetiteFille = make_Carte(petiteFilleTexture);
    Carte carteCupidon = make_Carte(cupidonTexture);
    Carte carteChasseur = make_Carte(chasseurTexture);
    Carte carteSorciere = make_Carte(sorciereTexture);
    Carte carteVoleur = make_Carte(voleurTexture);

    Uniform projectionUniform = make_Uniform("projection", shader);
    Uniform modelUniform = make_Uniform("model", shader);
    Uniform vueUniform = make_Uniform("vue", shader);
    Uniform timeUniform = make_Uniform("time", shader);

    Boutton lancer = make_Boutton(100, 100, 30, 100, chargerUneTexture(PROJECT_PATH"lancerUnePartieDefault.png"), fenetre);
    lancer.textureHover = chargerUneTexture(PROJECT_PATH"lancerUnePartieHover.png");
    lancer.alpha = 0.1;

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
        vue = matriceDeVue(make_vec4(0, cos(glfwGetTime() * 0.2) * 15, -15, 1), make_vec4(0, 0, 0, 1), make_vec4(0, 1, 0, 1));

        glUniformMatrix4fv(vueUniform.location, 1, GL_FALSE, &vue.col0.x);
        glUniformMatrix4fv(projectionUniform.location, 1, GL_FALSE, &projection.col0.x);

        carteLoupGarou.axeRotation = make_vec4(0, 1, 0, 1);
        carteLoupGarou.angle = glfwGetTime();
        carteLoupGarou.position = make_vec4(cos(glfwGetTime()* 0.2) * 6, 0, sin(glfwGetTime() * 0.2) * 6, 1);
        
        afficherCarte(&carteLoupGarou, shader);

        carteVillageois.axeRotation = make_vec4(0, 1, 0, 1);
        carteVillageois.angle = glfwGetTime() - PI * .25;
        carteVillageois.position = make_vec4(cos(glfwGetTime() * 0.2 + PI * .25) * 6, 0, sin(glfwGetTime() * 0.2 + PI * .25) * 6, 1);

        afficherCarte(&carteVillageois, shader);

        cartevoyante.axeRotation = make_vec4(0, 1, 0, 1);
        cartevoyante.angle = glfwGetTime() - PI * .5;
        cartevoyante.position = make_vec4(cos(glfwGetTime() * 0.2 + PI * .5) * 6, 0, sin(glfwGetTime() * 0.2 + PI * .5) * 6, 1);

        afficherCarte(&cartevoyante, shader);

        cartePetiteFille.axeRotation = make_vec4(0, 1, 0, 1);
        cartePetiteFille.angle = glfwGetTime() - PI * .75;
        cartePetiteFille.position = make_vec4(cos(glfwGetTime() * 0.2 + PI * .75) * 6, 0, sin(glfwGetTime() * 0.2 + PI * .75) * 6, 1);

        afficherCarte(&cartePetiteFille, shader);

        carteCupidon.axeRotation = make_vec4(0, 1, 0, 1);
        carteCupidon.angle = glfwGetTime() - PI;
        carteCupidon.position = make_vec4(cos(glfwGetTime() * 0.2 + PI ) * 6, 0, sin(glfwGetTime() * 0.2 + PI) * 6, 1);

        afficherCarte(&carteCupidon, shader);

        carteChasseur.axeRotation = make_vec4(0, 1, 0, 1);
        carteChasseur.angle = glfwGetTime() - PI * 1.25;
        carteChasseur.position = make_vec4(cos(glfwGetTime() * 0.2 + PI * 1.25) * 6, 0, sin(glfwGetTime() * 0.2 + PI * 1.25) * 6, 1);

        afficherCarte(&carteChasseur, shader);

        carteSorciere.axeRotation = make_vec4(0, 1, 0, 1);
        carteSorciere.angle = glfwGetTime() - PI * 1.5;
        carteSorciere.position = make_vec4(cos(glfwGetTime() * 0.2 + PI * 1.5) * 6, 0, sin(glfwGetTime() * 0.2 + PI * 1.5) * 6, 1);

        afficherCarte(&carteSorciere, shader);

        carteVoleur.axeRotation = make_vec4(0, 1, 0, 1);
        carteVoleur.angle = glfwGetTime() - PI * 1.75;
        carteVoleur.position = make_vec4(cos(glfwGetTime() * 0.2 + PI * 1.75) * 6, 0, sin(glfwGetTime() * 0.2 + PI * 1.75) * 6, 1);

        afficherCarte(&carteVoleur, shader);


        //2D
        glDepthFunc(GL_ALWAYS);
        projection = ProjectionOrthographique(0, width, 0, height, -10.0f, 10.0f);
        vue = matriceDidentite(1);
        
        glUniformMatrix4fv(vueUniform.location, 1, GL_FALSE, &vue.col0.x);
        glUniformMatrix4fv(projectionUniform.location, 1, GL_FALSE, &projection.col0.x);

        
        lancer.l = width * .35f;
        lancer.h = width * .1f;
        lancer.x = width * .5f;
        lancer.y = height * .15f;
        afficherBoutton(&lancer, shader);

        glfwSwapBuffers(fenetre);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
