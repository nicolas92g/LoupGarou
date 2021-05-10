#include "interface.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void creerLaFenetre(GLFWwindow** window) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    *window = glfwCreateWindow(800, 600, "Jeu de Loup Garou", NULL, NULL);

    if (*window == NULL)
    {
        printf("la fenetre n'a pas reussie a etre creer\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(*window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("glad ne s'est pas initialise correctement\n");
        exit(EXIT_FAILURE);
    }

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
    const char* vertexText = fichierVersString(vertexPath);
    const char* fragmentText = fichierVersString(fragmentPath);//recupere le texte des shaders 

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexText, NULL);
    glCompileShader(vertexShader);//creer et compile le vertex shade

    free(vertexText);//libere la memoire allouer pour contenir le texte du shader
 
    int succes;
    char InfoCompilation[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succes);//recupere les infos de compilation 

    if (!succes)//verifie que la compilation est un succes
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, InfoCompilation);
        printf("la compilation du vertex shader a rate :\n%s\n", InfoCompilation);
    }

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
    static float vertices[] = {
         0.0f,  0.0f,
         1.0f,  0.0f,
         0.0f,  1.0f,

         0.0f,  1.0f,
         1.0f,  0.0f,
         1.0f,  1.0f
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glBindVertexArray(0);
    return VAO;
}

unsigned int chargerUneTexture(const char* path)
{
    stbi_set_flip_vertically_on_load(1);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nbrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nbrChannels, 4);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("probleme de chargement d'une texture : %s\n" , path);
        exit(EXIT_FAILURE);
    }
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

mat4x4 ProjectionOrthographique(float left, float right, float bottom, float top, float zNear, float zFar) {
    mat4x4 ret = matriceDidentite(1);

    ret.line0.x =  2.0f / (right - left);
    ret.line1.y =  2.0f / (top - bottom);
    ret.line2.z = -2.0f / (zFar - zNear);

    ret.line3.x = -(right + left) / (right - left);
    ret.line3.y = -(top + bottom) / (top - bottom);
    ret.line3.z = -(zFar + zNear) / (zFar - zNear);

    return ret;
}

vec4 make_vec4(float x, float y, float z, float w) {
    return (vec4) {x, y, z, w};
}

Uniform make_Uniform(const char* name, unsigned int shader){
    return (Uniform) {name, glGetUniformLocation(shader, name)};
}

mat4x4 matriceDidentite(float f) {
    mat4x4 ret;
    ret.line0 = make_vec4(f, 0, 0, 0);
    ret.line1 = make_vec4(0, f, 0, 0);
    ret.line2 = make_vec4(0, 0, f, 0);
    ret.line3 = make_vec4(0, 0, 0, f);
    return ret;
}

mat4x4 matriceDeTaille(float x, float y, float z) {
    mat4x4 ret;
    ret.line0 = make_vec4(x, 0, 0, 0);
    ret.line1 = make_vec4(0, y, 0, 0);
    ret.line2 = make_vec4(0, 0, z, 0);
    ret.line3 = make_vec4(0, 0, 0, 1);
    return ret;
}

mat4x4 matriceDeTranslation(float x, float y, float z) {
    mat4x4 ret;
    ret.line0 = make_vec4(1, 0, 0, x);
    ret.line1 = make_vec4(0, 1, 0, y);
    ret.line2 = make_vec4(0, 0, 1, z);
    ret.line3 = make_vec4(0, 0, 0, 1);
    return ret;
}

mat4x4 multiplicationDeMatrices(mat4x4* m1, mat4x4* m2)
{
    mat4x4 ret;
    ret.line0 = make_vec4(m1->line0.x * m2->line0.x, m1->line0.y * m2->line0.y, m1->line0.z * m2->line0.z, m1->line0.w * m2->line0.w);
    ret.line1 = make_vec4(m1->line1.x * m2->line1.x, m1->line1.y * m2->line1.y, m1->line1.z * m2->line1.z, m1->line1.w * m2->line1.w);
    ret.line2 = make_vec4(m1->line2.x * m2->line2.x, m1->line2.y * m2->line2.y, m1->line2.z * m2->line2.z, m1->line2.w * m2->line2.w);
    ret.line3 = make_vec4(m1->line3.x * m2->line3.x, m1->line3.y * m2->line3.y, m1->line3.z * m2->line3.z, m1->line3.w * m2->line3.w);
    return ret;
}

