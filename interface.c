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

    //on met le viewport a la taille actuelle de la fenetre
    glViewport(0, 0, 800, 600);
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
        printf("la compilation du vertex shader a rate :\n%s\n", InfoCompilation);
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
        printf("la compilation du fragment shader a rate :\n%s\n", InfoCompilation);
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();//creer le programme

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);//ajoute les deux shaders a ce programme 

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &succes);//verifie le succes de cette etape
    if (!succes) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, InfoCompilation);
        printf("la creation du shader a rate : \n%s\n", InfoCompilation);
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
          //coordonnées (xyz)       //coordonées uv (pour les textures)    
         -0.5f,  -0.5f,  0.0f,      0.0f,   0.0f,
          0.5f,  -0.5f,  0.0f,      1.0f,   0.0f,
         -0.5f,   0.5f,  0.0f,      0.0f,   1.0f,

         -0.5f,   0.5f,  0.0f,      0.0f,   1.0f,
          0.5f,  -0.5f,  0.0f,      1.0f,   0.0f,
          0.5f,   0.5f,  0.0f,      1.0f,   1.0f,
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //dis ou trouver les coordonnées uv dans ce tableau
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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
        printf("probleme de chargement d'une texture : %s\n" , path);
        exit(EXIT_FAILURE);
    }
    //libere l'allocation dynamique qui stocke l'image
    stbi_image_free(data);

    //desactive toutes les textures
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

Uniform make_Uniform(const char* name, unsigned int shader){
    return (Uniform) {name, glGetUniformLocation(shader, name)};//recupere la position de la variable dans le shader
}

Boutton make_Boutton(int x, int y, int h, int l, unsigned int defaultTex, GLFWwindow* win) {
    return (Boutton) {x, y, h, l, defaultTex, defaultTex, defaultTex, .0f, make_vec4(1,1,1,1), win, false, false};
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
    if (!carre) { carre = creerUnCarre(); printf("creer un carre\n"); }

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
    boutton->clicker = (boutton->hover && glfwGetMouseButton(boutton->win, GLFW_MOUSE_BUTTON_LEFT));
    
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
    glUniform3fv(glGetUniformLocation(shader, "filtre"), 1, &boutton->filter);

    glBindVertexArray(carre);
    //affiche le boutton
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //remetre les filtres par defaults
    glUniform1f(glGetUniformLocation(shader, "alpha"), 0.0f);
    glUniform3f(glGetUniformLocation(shader, "filtre"), 1, 1, 1);
}

Carte make_Carte(unsigned int texture){
    //charger une texture de verso pour toutes les cartes
    static unsigned int verso = 0;
    if (!verso) verso = chargerUneTexture(PROJECT_PATH"verso.png");
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

    glCullFace(GL_BACK);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, carte->textureRecto);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glCullFace(GL_FRONT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, carte->textureVerso);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glCullFace(GL_BACK);
}
