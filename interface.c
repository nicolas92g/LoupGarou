#include "interface.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void creerLaFenetre(GLFWwindow** window) {

    glfwInit();//initialise la librairie glfw

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//on utilise opengl 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//on utilise opengl 3.3

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 32);//active le multisampling avec 32 samples par pixels

    *window = glfwCreateWindow(800, 600, "Jeu de Loup Garou", NULL, NULL);//on creer la fenetre
    
    //mettre une icone a la fenetre
    GLFWimage icon;
    icon.pixels = stbi_load(PROJECT_PATH"loupGarou.png", &icon.width, &icon.height, NULL, 4);
    glfwSetWindowIcon(*window, 1, &icon);

    //on teste si la fentre a été créée correctement
    if (*window == NULL)
    {
        printf("la fenetre n'a pas reussie a etre creer\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    //on creer un context opengl
    glfwMakeContextCurrent(*window);

    //on initialise glad qui permet d'utilise opengl
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("glad ne s'est pas initialise correctement\n");
        exit(EXIT_FAILURE);
    }

    //on met le viewport par default a la taille actuelle de la fenetre
    glViewport(0, 0, 800, 600);

    glfwSetInputMode(*window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_FALSE);
}

char* fichierVersString(const char* filename)  {
    
    FILE* file;
    fopen_s(&file, filename, "r");              //lire le fichier
    if (!file) return NULL;                     //verifier qu'il est ouvert

    fseek(file, 0L, SEEK_END);                  //mettre le curseur a la fin
    size_t size = ftell(file);                  //noter la taille du fichier

    char* source = calloc(1, size);             //creer un tableau de char
    if (!source || !size) return NULL;          //verifie que l'allocation est correcte

    rewind(file);                               //mettre le curseur au debut   
    fread(source, size, sizeof(char), file);    //lire le fichier

    fclose(file);                               //fermer le fichier

    return source;
}

unsigned int compilerLeShader(const char* vertexPath, const char* fragmentPath)
{
    //recupere le texte dans les fichiers shaders
    const char* vertexText = fichierVersString(vertexPath);
    const char* fragmentText = fichierVersString(fragmentPath);//recupere le texte des shaders 

    //creer un vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexText, NULL);
    glCompileShader(vertexShader);//compile le vertex shader

    free(vertexText);//libere la memoire allouer pour contenir le texte du shader
 
    int succes;
    char InfoCompilation[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succes);//recupere les infos de compilation

    if (!succes)//verifie que la compilation est un succes
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, InfoCompilation);
        printf("%s\n", InfoCompilation);
    }

    //creer le fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentText, NULL);
    glCompileShader(fragmentShader);//creer et compile le fragment shader

    free(fragmentText);//libere la memoire allouer pour contenir le texte du shader

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succes);//recupere les infos de compilation 

    if (!succes)//verifie que la compilation est un succes
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, InfoCompilation);
        printf("%s\n", InfoCompilation);
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();//creer le programme

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);//ajoute les deux shaders a ce programme 

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &succes);//verifie le succes de cette etape
    if (!succes) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, InfoCompilation);
        printf("%s\n", InfoCompilation);
        exit(EXIT_FAILURE);
    }

    glUseProgram(shaderProgram);//on utilise ce nouveau programme

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);//supprime les shaders qui ont été ajouté au programme

    return shaderProgram;
}

unsigned int creerUnCarre()
{
    //creer un tableau de Vertices (points ?)
    static float vertices[] = {
          //coordonnées (xyz)        //droites normales          //coordonées uv (pour les textures)    
         -0.5f,  -0.5f,  0.0f,       0.0f,   0.0f, -1.0f,        0.0f,   0.0f,
          0.5f,  -0.5f,  0.0f,       0.0f,   0.0f, -1.0f,        1.0f,   0.0f,
         -0.5f,   0.5f,  0.0f,       0.0f,   0.0f, -1.0f,        0.0f,   1.0f,
                                                   
         -0.5f,   0.5f,  0.0f,       0.0f,   0.0f, -1.0f,        0.0f,   1.0f,
          0.5f,  -0.5f,  0.0f,       0.0f,   0.0f, -1.0f,        1.0f,   0.0f,
          0.5f,   0.5f,  0.0f,       0.0f,   0.0f, -1.0f,        1.0f,   1.0f,
    };
    
    //création de l'objet qui stockera les infos de notre carré
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //creation de la memoire qui stockera le tableau de vertices dans la carte graphique
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //dis ou trouver les coordonnées géométriques dans ce tableau
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //dis ou trouver les droites normales dans ce tableau
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //dis ou trouver les coordonnées uv dans ce tableau
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //sort du VAO
    glBindVertexArray(0);
    return VAO;
}

unsigned int chargerUneTexture(const char* path)
{
    //inverse les coordonées uv
    stbi_set_flip_vertically_on_load(1);

    //creer la texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //assigne des parametres a la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //charge l'image 
    int width, height, nbrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nbrChannels, 4);

    //si l'image a été correctement chargé
    if (data)
    {
        //rempli la texture avec l'image précédement chargé en utilisant 4 canals (rouge, bleu, vert, et transparence)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //creer plein de copie de la texture en divisant la resolution par 2 a chaque fois
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        //message d'erreur
        printf("probleme de chargement d'une texture : %s (verifier peut etre la macro PROJECT_PATH)\n" , path);
        exit(EXIT_FAILURE);
    }
    //libere l'allocation dynamique qui stocke l'image
    stbi_image_free(data);

    //desactive toutes les textures
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

Boutton make_Boutton(int x, int y, int h, int l, unsigned int defaultTex, GLFWwindow* win) {
    return (Boutton) {x, y, h, l, defaultTex, defaultTex, defaultTex, .0f, make_vec4(1,1,1,1), win, false, false, false, false};
}

void setBouttonTextures(Boutton* boutton, unsigned int whenHover, unsigned int whenClicked)
{
    //assigne les textures dynamiques
    boutton->textureHover = whenHover;
    boutton->textureCliquer = whenClicked;
}

void afficherBoutton(Boutton* boutton, unsigned int shader)
{
    //creer un seul carre pour chaque boutton 
    static unsigned int carre = 0;
    if (!carre) carre = creerUnCarre(); 

    //utilise le shader mis en parametre
    glUseProgram(shader);

    //genere un nouvelle matrice model
    mat4x4 taille = matriceDeTaille(boutton->l, boutton->h, 1);
    mat4x4 translation = matriceDeTranslation(boutton->x, boutton->y, 0);
    mat4x4 model = multiplicationDeMatrices(&translation, &taille);

    //recupere la hauteur de la fenetre 
    int height;
    glfwGetWindowSize(boutton->win, NULL, &height);

    //recupere la position du curseur
    double x, y;
    glfwGetCursorPos(boutton->win, &x, &y);

    //met le curseur sur le meme repere que le boutton
    y = height - y;

    //indique si le curseur survole le boutton
    boutton->hover = 
        x > (boutton->x - boutton->l * .5) && 
        x < (boutton->x + boutton->l * .5) && 
        y > (boutton->y - boutton->h * .5) && 
        y < (boutton->y + boutton->h * .5);

    //indique si le boutton est cliquer
    bool ancienneValeur = boutton->clicker;
    boutton->clicker = (boutton->hover && glfwGetMouseButton(boutton->win, GLFW_MOUSE_BUTTON_LEFT));

    boutton->viensDetreClicker = (!ancienneValeur && boutton->clicker);
    
    //choisit la bonne texture
    glActiveTexture(GL_TEXTURE0);
    if (boutton->clicker) {
        glBindTexture(GL_TEXTURE_2D, boutton->textureCliquer);
    }
    else if (boutton->hover) {
        glBindTexture(GL_TEXTURE_2D, boutton->textureHover);
    }
    else {
        glBindTexture(GL_TEXTURE_2D, boutton->textureDefault);
    }

    //assigne la matrice généré dans le shader
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model.col0.x);

    //assigne les filtres dans le shader
    glUniform1f(glGetUniformLocation(shader, "alpha"), boutton->alpha);
    

    if (boutton->filtreHover && boutton->hover) {
        glUniform3f(glGetUniformLocation(shader, "filtre"), 
            boutton->filter.x - .2, boutton->filter.y - .2, boutton->filter.z - .2);

    }
    else {
        glUniform3fv(glGetUniformLocation(shader, "filtre"), 1, &boutton->filter);
    }
    
    glBindVertexArray(carre);
    //affiche le boutton
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

Carte make_Carte(unsigned int texture){
    //charger une texture de verso pour toutes les cartes
    static unsigned int verso = 0;
    if (!verso) verso = chargerUneTexture(PROJECT_PATH"textures/verso.png");
    //creer la carte
    return (Carte){make_vec4(0,0,0,1), make_vec4(0, 0, 1, 1), .0f, texture, verso};
}

void afficherCarte(Carte* carte, unsigned int shader)
{
    glEnable(GL_CULL_FACE);
    glUseProgram(shader);

    static mat4x4 taille, translation, rotation, modelIntermediaire, model;
    static unsigned int carre = 0;
    if (!carre) carre = creerUnCarre();

    taille = matriceDeTaille(3, 3, 1);
    translation = matriceDeTranslation(carte->position.x, carte->position.y, carte->position.z);
    rotation = matriceDeRotation(carte->axeRotation, carte->angle);

    modelIntermediaire = multiplicationDeMatrices(&translation, &taille);
    model = multiplicationDeMatrices(&modelIntermediaire, &rotation);

    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model.col0.x);

    glBindVertexArray(carre);

    //affiche le recto de la carte
    glCullFace(GL_BACK);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, carte->textureRecto);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //affiche le verso de la carte
    modelIntermediaire = matriceDeRotation(make_vec4(0, 1, 0, 1), PI);
    model = multiplicationDeMatrices(&model, &modelIntermediaire);

    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model.col0.x);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, carte->textureVerso);

    glDrawArrays(GL_TRIANGLES, 0, 6);

}

Decoration make_Decoration(GLFWwindow* fenetre)
{
    Decoration deco;

    deco.shader = compilerLeShader(PROJECT_PATH"phong.vert", PROJECT_PATH"phong.frag");
    deco.cam = make_Camera(fenetre);
    deco.cam.regard = make_vec4(0, 0, 0, 1);

    deco.loupGarouTexture = chargerUneTexture(PROJECT_PATH"textures/loupGarou.png");
    deco.villageoisTexture = chargerUneTexture(PROJECT_PATH"textures/villageois.png");
    deco.voyanteTexture = chargerUneTexture(PROJECT_PATH"textures/voyante.png");
    deco.voleurTexture = chargerUneTexture(PROJECT_PATH"textures/voleur.png");
    deco.versoTexture = chargerUneTexture(PROJECT_PATH"textures/verso.png");
    deco.petiteFilleTexture = chargerUneTexture(PROJECT_PATH"textures/petiteFille.png");
    deco.cupidonTexture = chargerUneTexture(PROJECT_PATH"textures/cupidon.png");
    deco.chasseurTexture = chargerUneTexture(PROJECT_PATH"textures/chasseur.png");
    deco.sorciereTexture = chargerUneTexture(PROJECT_PATH"textures/sorciere.png");
    deco.capitaineTexture = chargerUneTexture(PROJECT_PATH"textures/capitaine.png");

    deco.carteLoupGarou = make_Carte(deco.loupGarouTexture);
    deco.carteVillageois = make_Carte(deco.villageoisTexture);
    deco.cartevoyante = make_Carte(deco.voyanteTexture);
    deco.cartePetiteFille = make_Carte(deco.petiteFilleTexture);
    deco.carteCupidon = make_Carte(deco.cupidonTexture);
    deco.carteChasseur = make_Carte(deco.chasseurTexture);
    deco.carteSorciere = make_Carte(deco.sorciereTexture);
    deco.carteVoleur = make_Carte(deco.voleurTexture);

    return deco;
}

void rotationsEnCercle(Decoration* deco) {

    deco->cam.position = make_vec4( 1,cos(glfwGetTime() * .2) * 12, 16, 1);
    updateCamera3D(&deco->cam, deco->shader);

    Carte* crt = &deco->carteLoupGarou;
    for (short i = 0; i < 8; i++)
    {
        (crt + i)->axeRotation = make_vec4(0, 1, 0, 1);
        (crt + i)->angle = glfwGetTime() + PI * 0.25 * i;
        (crt + i)->position = make_vec4(
            cos(glfwGetTime() * 0.2 + PI * 0.25 * i) * 6, 
            0, 
            sin(glfwGetTime() * 0.2 + PI * 0.25 * i) * 6,
            1);

        afficherCarte(crt + i, deco->shader);
    }
}

void carteQuiSeDevoile(Decoration* deco, Role role) {
    static double startTime = .0;
    static Role ancienRole = -1;

    if (ancienRole != role) {
        startTime = glfwGetTime();
        ancienRole = role;
    }
    if (role < 1) {
        startTime = glfwGetTime();
        role = ROLE_LOUP_GAROU;
    }

    const double time = (glfwGetTime() - startTime) * 2.0;

    deco->cam.position = make_vec4(0, 2, 16, 1);
    updateCamera3D(&deco->cam, deco->shader);

    (&deco->carteLoupGarou + role)->axeRotation = make_vec4(0, 1, 0, 1);
    (&deco->carteLoupGarou + role)->angle = cos(min(time * .5, PI)) * PI * .5 + PI * .5;
    (&deco->carteLoupGarou + role)->position = make_vec4(0, 0, min(-5 + time, 5), 1);

    afficherCarte(&deco->carteLoupGarou + role, deco->shader);
}

Camera make_Camera(GLFWwindow* fenetre)
{
    return (Camera) {make_vec4(0,0,-2,1), make_vec4(0,0,0,1), fenetre, matriceDidentite(1), matriceDidentite(1)};
}

void updateCamera3D(Camera* cam, unsigned int shader)
{
    int width, height;
    glfwGetWindowSize(cam->win, &width, &height);

    glDepthFunc(GL_LEQUAL);

    cam->projection = projectionPerspective(((float)width / (float)height), PI * 0.25f, 0.1f, 100.0f);
    cam->vue = matriceDeVue(cam->position, cam->regard, make_vec4(0, 1, 0, 1));

    glUseProgram(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader, "vue"), 1, GL_FALSE, &cam->vue.col0.x);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &cam->projection.col0.x);
}

void updateCamera2D(Camera* cam, unsigned int shader)
{
    int width, height;
    glfwGetWindowSize(cam->win, &width, &height);

    glDepthFunc(GL_ALWAYS);

    cam->projection = ProjectionOrthographique(0, width, 0, height, -10.0f, 10.0f);

    glUseProgram(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &cam->projection.col0.x);
}

GUI make_GUI(GLFWwindow* fenetre) {
    //couleur d'arriere plan
    glClearColor(.7f, .7f, .7f, 1.0f);

    //active la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //active le test de profondeur
    glEnable(GL_DEPTH_TEST);

    GUI ret;
    ret.lancerLaPartie = make_Boutton(100, 100, 30, 100, chargerUneTexture(PROJECT_PATH"textures/lancerUnePartieDefault.png"), fenetre);
    ret.lancerLaPartie.textureHover = chargerUneTexture(PROJECT_PATH"textures/lancerUnePartieHover.png");
    ret.lancerLaPartie.alpha = 0.1;

    ret.fenetre = fenetre;
    ret.etat = ETAT_ECRAN_DE_DEPART;

    ret.carre = creerUnCarre();
    ret.shader = compilerLeShader(PROJECT_PATH"interface.vert", PROJECT_PATH"interface.frag");
    ret.cam = make_Camera(fenetre);
    ret.deco = make_Decoration(fenetre);

    ret.combienDeJoueurQuestion = chargerUneTexture(PROJECT_PATH"textures/combienDeJoueurQuestion.png");
    ret.afficherCarteTexture = chargerUneTexture(PROJECT_PATH"textures/carteDuJoueur.png");
    ret.cacherCarteTexture = chargerUneTexture(PROJECT_PATH"textures/cacherCarte.png");

    ret.nombresTextures[0] = chargerUneTexture(PROJECT_PATH"textures/un.png");
    ret.nombresTextures[1] = chargerUneTexture(PROJECT_PATH"textures/deux.png");
    ret.nombresTextures[2] = chargerUneTexture(PROJECT_PATH"textures/trois.png");
    ret.nombresTextures[3] = chargerUneTexture(PROJECT_PATH"textures/quatre.png");
    ret.nombresTextures[4] = chargerUneTexture(PROJECT_PATH"textures/cinq.png");
    ret.nombresTextures[5] = chargerUneTexture(PROJECT_PATH"textures/six.png");
    ret.nombresTextures[6] = chargerUneTexture(PROJECT_PATH"textures/sept.png");
    ret.nombresTextures[7] = chargerUneTexture(PROJECT_PATH"textures/huit.png");
    ret.nombresTextures[8] = chargerUneTexture(PROJECT_PATH"textures/neuf.png");
    ret.nombresTextures[9] = chargerUneTexture(PROJECT_PATH"textures/dix.png");
    ret.nombresTextures[10] = chargerUneTexture(PROJECT_PATH"textures/onze.png");
    ret.nombresTextures[11] = chargerUneTexture(PROJECT_PATH"textures/douze.png");
    ret.nombresTextures[12] = chargerUneTexture(PROJECT_PATH"textures/treize.png");
    ret.nombresTextures[13] = chargerUneTexture(PROJECT_PATH"textures/quatorze.png");
    ret.nombresTextures[14] = chargerUneTexture(PROJECT_PATH"textures/quinze.png");
    ret.nombresTextures[15] = chargerUneTexture(PROJECT_PATH"textures/seize.png");
    ret.nombresTextures[16] = chargerUneTexture(PROJECT_PATH"textures/dixSept.png");
    ret.nombresTextures[17] = chargerUneTexture(PROJECT_PATH"textures/dixHuit.png");

    unsigned int blancTexture = chargerUneTexture(PROJECT_PATH"textures/blanc.png");

    for (size_t i = 0; i < 11; i++)
    {
        ret.bouttons[i] = make_Boutton(0, 0, 10, 10, blancTexture, fenetre);
        (ret.bouttons + i)->alpha = .2f;
        (ret.bouttons + i)->filtreHover = true;
    }

    ret.roleAMontrer = 0;
    ret.nombreDeJoueur = 0;

    return ret;
}

void recupererLeNombreDeJoueurs(GUI* input) {
    input->etat = ETAT_ECRAN_DE_DEPART;
    do
    {
        int width, height;
        glfwGetWindowSize(input->fenetre, &width, &height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);

        mat4x4 model;
        mat4x4 translation;
        mat4x4 taille;

        switch (input->etat)
        {
        case ETAT_ECRAN_DE_DEPART:
            //affiche l'arriere plan
            rotationsEnCercle(&input->deco);

            //met a jour la camera pour la 2D
            updateCamera2D(&input->cam, input->shader);

            //affiche un bouton lancer la partie en modifiant sa position et sa taille par rapport a la fenetre
            input->lancerLaPartie.l = width * .35f;
            input->lancerLaPartie.h = width * .1f;
            input->lancerLaPartie.x = width * .5f;
            input->lancerLaPartie.y = height * .15f;
            afficherBoutton(&input->lancerLaPartie, input->shader);

            //test si le boutton est clicker
            if (input->lancerLaPartie.viensDetreClicker && input->nombreDimageDansUnEtat > NBR_MIN_DANS_UN_ETAT) {
                input->etat = ETAT_COMBIEN_DE_JOUEUR;
                input->nombreDimageDansUnEtat = 0;
            }
            break;

        case ETAT_COMBIEN_DE_JOUEUR:
            //fonctions pour afficher l'arriere plan
            rotationsEnCercle(&input->deco);

            //met a jour la camera pour la 2D
            updateCamera2D(&input->cam, input->shader);

            //prepare la matrice
            translation = matriceDeTranslation(width * .5f, height * 0.95f, 0);
            taille = matriceDeTaille(height * 1.0f, height * .09f, 1);
            model = multiplicationDeMatrices(&translation, &taille);

            //envoie la matrice au shader et le filtre alpha
            glUniformMatrix4fv(glGetUniformLocation(input->shader, "model"), 1, GL_FALSE, &model.col0.x);
            glUniform1f(glGetUniformLocation(input->shader, "alpha"), .1f);
            glUniform3f(glGetUniformLocation(input->shader, "filtre"), 1, 1, 1);

            //affiche la question
            glUseProgram(input->shader);
            glBindVertexArray(input->carre);
            glBindTexture(GL_TEXTURE_2D, input->combienDeJoueurQuestion);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            //sert de compteur de lignes pour l'entree du nombre de joueur
            static int lignes;
            lignes = 0;

            //affichage des bouttons pour choisir le nbr de joueurs
            for (size_t i = 0; i < 11; i++)
            {
                //si i est un multiple de 3 non nul alors sauter une ligne
                if (!(i % 3) && i) lignes++;

                //position et taille de chaque bouttons;
                (input->bouttons + i)->x = i % 3 * height * .21f + (width * .5f - height * .21f);
                (input->bouttons + i)->y = height * .78f - lignes * height * .21f;
                (input->bouttons + i)->l = height * .2f;
                (input->bouttons + i)->h = height * .2f;

                //affichage du boutton
                afficherBoutton(&input->bouttons[i], input->shader);

                //affichage du nombre sur le boutton
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, input->nombresTextures[i + 7]);

                glDrawArrays(GL_TRIANGLES, 0, 6);

                //si un boutton est clicker et que la page s'est afficher suffisament longtemps
                if ((input->bouttons + i)->viensDetreClicker && input->nombreDimageDansUnEtat > NBR_MIN_DANS_UN_ETAT) {
                    input->nombreDeJoueur = 8 + i;
                    input->nombreDimageDansUnEtat = 0;

                    //verifie que le nombre de joueur est correct
                    assert(input->nombreDeJoueur >= 8 && input->nombreDeJoueur <= 18);

                    return;
                }
            }
            break;
        default:
            break;
        }
        input->nombreDimageDansUnEtat++;
        //finir l'image
        glfwSwapBuffers(input->fenetre);
        glfwPollEvents();

    } while (!glfwWindowShouldClose(input->fenetre));
    exit(0);
}

void montrerLeRoleDeChaqueJoueurs(GUI* input, Role* roles) {
    do {

        int width, height;
        glfwGetWindowSize(input->fenetre, &width, &height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);

        //matrices
        static mat4x4 model;
        static mat4x4 translation;
        static mat4x4 taille;

        //met a jour la camera pour la 2D
        updateCamera2D(&input->cam, input->shader);

        //permet de stocker l'ancienne valeur de GLFW_MOUSE_BUTTON_LEFT
        static bool cliquer = false, montrer = false;

        //actions en cas de clique
        if (cliquer && !glfwGetMouseButton(input->fenetre, GLFW_MOUSE_BUTTON_LEFT) && input->nombreDimageDansUnEtat > NBR_MIN_DANS_UN_ETAT * 2.0 * (montrer + .1)) {
            if (montrer) {
                input->roleAMontrer++;
            }
            input->nombreDimageDansUnEtat = 0;
            montrer = !montrer;
        }
        cliquer = glfwGetMouseButton(input->fenetre, GLFW_MOUSE_BUTTON_LEFT);

        //si tous les roles on été affiché
        if (input->roleAMontrer >= input->nombreDeJoueur ||
            (glfwGetKey(input->fenetre, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(input->fenetre, GLFW_KEY_Z)))
        {
            montrer = false;
            input->roleAMontrer = 0;
            return;
        }


        //si on dois montrer la carte
        if (montrer) {
            if (input->nombreDimageDansUnEtat > NBR_MIN_DANS_UN_ETAT * 2.2) {
                //prepare la matrice
                translation = matriceDeTranslation(width * .5f, height * 0.95f, 0);
                taille = matriceDeTaille(height * .9f, height * .09f, 1);
                model = multiplicationDeMatrices(&translation, &taille);

                //envoie la matrice au shader et le filtre alpha
                glUniformMatrix4fv(glGetUniformLocation(input->shader, "model"), 1, GL_FALSE, &model.col0.x);
                glUniform1f(glGetUniformLocation(input->shader, "alpha"), (sin(input->nombreDimageDansUnEtat * .04) + 1) * .45 + .1);
                glUniform3f(glGetUniformLocation(input->shader, "filtre"), 1, 1, 1);

                //affiche la question
                glUseProgram(input->shader);
                glBindVertexArray(input->carre);
                glBindTexture(GL_TEXTURE_2D, input->cacherCarteTexture);

                glDrawArrays(GL_TRIANGLES, 0, 6);
            }

            //animation d'une carte qui se devoile pour donner le role a chaque joueur
            carteQuiSeDevoile(&input->deco, roles[input->roleAMontrer]);
        }
        //si la carte est encore cachée
        else {
            //affiche l'instruction : clicquer pour afficher la carte du joueur 
            //prepare la matrice
            translation = matriceDeTranslation(width * .45f, height * 0.95f, 0);
            taille = matriceDeTaille(height, height * .09f, 1);
            model = multiplicationDeMatrices(&translation, &taille);

            //affichage
            glUniformMatrix4fv(glGetUniformLocation(input->shader, "model"), 1, GL_FALSE, &model.col0.x);
            glUniform1f(glGetUniformLocation(input->shader, "alpha"), (sin(input->nombreDimageDansUnEtat * .04) + 1) * .45 + .1);
            glUniform3f(glGetUniformLocation(input->shader, "filtre"), 1, 1, 1);
            glUseProgram(input->shader);
            glBindVertexArray(input->carre);
            glBindTexture(GL_TEXTURE_2D, input->afficherCarteTexture);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            //affiche le numero du joueur
            translation = matriceDeTranslation(width * .47f + height * .5, height * 0.95f, 0);
            taille = matriceDeTaille(height * .08f, height * .08f, 1);
            model = multiplicationDeMatrices(&translation, &taille);

            //affichqge
            glUniformMatrix4fv(glGetUniformLocation(input->shader, "model"), 1, GL_FALSE, &model.col0.x);
            glUseProgram(input->shader);
            glBindVertexArray(input->carre);
            glBindTexture(GL_TEXTURE_2D, input->nombresTextures[input->roleAMontrer]);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            //montre juste une carte cachée
            carteQuiSeDevoile(&input->deco, -1);
        }
        input->nombreDimageDansUnEtat++;
        //finir l'image
        glfwSwapBuffers(input->fenetre);
        glfwPollEvents();
    } while (!glfwWindowShouldClose(input->fenetre));
    exit(0);
}

unsigned short choisirUnJoueur(unsigned short* listeDeJoueursEnVie, unsigned short nombreDeJoueursEnVie)
{
    return 0;
}

void detruire_GUI(GUI* input)
{
    glDeleteVertexArrays(1, &input->carre);
}
