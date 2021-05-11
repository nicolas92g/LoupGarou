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
         -0.5f,  -0.5f,  0.0f,  0.0f,   0.0f,
          0.5f,  -0.5f,  0.0f,  1.0f,   0.0f,
         -0.5f,   0.5f,  0.0f,  0.0f,   1.0f,

         -0.5f,   0.5f,  0.0f,  0.0f,   1.0f,
          0.5f,  -0.5f,  0.0f,  1.0f,   0.0f,
          0.5f,   0.5f,  0.0f,  1.0f,   1.0f,
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
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

float carre(float a) {
    return a * a;
}

mat4x4 ProjectionOrthographique(float left, float right, float bottom, float top, float zNear, float zFar) {
    mat4x4 ret = matriceDidentite(1);

    ret.col0.x =  2.0f / (right - left);
    ret.col1.y =  2.0f / (top - bottom);
    ret.col2.z = -2.0f / (zFar - zNear);

    ret.col3.x = -(right + left) / (right - left);
    ret.col3.y = -(top + bottom) / (top - bottom);
    ret.col3.z = -(zFar + zNear) / (zFar - zNear);

    return ret;
}

vec4 make_vec4(float x, float y, float z, float w) {
    return (vec4) {x, y, z, w};
}

Uniform make_Uniform(const char* name, unsigned int shader){
    return (Uniform) {name, glGetUniformLocation(shader, name)};
}

vec4 multiplie(vec4 vec, float f)
{
    return (vec4) {vec.x * f, vec.y * f, vec.z * f, vec.w * f};
}

vec4 additionne(vec4 v1, vec4 v2)
{
    return (vec4) {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w};
}

mat4x4 matriceDidentite(float f) {
    mat4x4 ret;
    ret.col0 = make_vec4(f, 0, 0, 0);
    ret.col1 = make_vec4(0, f, 0, 0);
    ret.col2 = make_vec4(0, 0, f, 0);
    ret.col3 = make_vec4(0, 0, 0, f);
    return ret;
}

mat4x4 matriceDeTaille(float x, float y, float z) {
    mat4x4 ret;
    ret.col0 = make_vec4(x, 0, 0, 0);
    ret.col1 = make_vec4(0, y, 0, 0);
    ret.col2 = make_vec4(0, 0, z, 0);
    ret.col3 = make_vec4(0, 0, 0, 1);
    return ret;
}

mat4x4 matriceDeTranslation(float x, float y, float z) {
    mat4x4 ret;
    ret.col0 = make_vec4(1, 0, 0, 0);
    ret.col1 = make_vec4(0, 1, 0, 0);
    ret.col2 = make_vec4(0, 0, 1, 0);
    ret.col3 = make_vec4(x, y, z, 1);
    return ret;
}

mat4x4 matriceDeRotation(vec4 u, float A)
{
    //si l'axe est un vecteur nulle ou si l'angle de rotation est nulle
    if (u.x == .0f && u.y == .0f && u.z == .0f || A == .0f) return matriceDidentite(1);

    //calcule la norme du vecteur axe
    size_t norme = sqrt((double)u.x * (double)u.x 
        + (double)u.y * (double)u.y 
        + (double)u.z * (double)u.z);

    //normalise (norme de l'axe = 1.0f)
    u = multiplie(u, 1.0f / norme);

    //composer la matrice
    mat4x4 ret;
    ret.col0 = make_vec4(cos(A) + carre(u.x) * (1 - cos(A))      , u.y * u.x * (1 - cos(A)) + u.z * sin(A) , u.z * u.x * (1 - cos(A)) - u.y * sin(A) , 0     );
    ret.col1 = make_vec4(u.x * u.y * (1 - cos(A)) - u.z * sin(A) , cos(A) + carre(u.y) * (1 - cos(A))      , u.z * u.y * (1 - cos(A)) - u.x * sin(A) , 0     );
    ret.col2 = make_vec4(u.x * u.z * (1 - cos(A)) - u.y * sin(A) , u.y * u.z * (1 - cos(A)) - u.x * sin(A) , cos(A) + carre(u.z) * (1 - cos(A))      , 0     );
    ret.col3 = make_vec4(0                                       , 0                                       , 0                                       , 1     );
    return ret;
}

mat4x4 multiplicationDeMatrices(mat4x4* m1, mat4x4* m2)
{
    const vec4 SrcA0 = m1->col0;
    const vec4 SrcA1 = m1->col1;
    const vec4 SrcA2 = m1->col2;
    const vec4 SrcA3 = m1->col3;
           
    const vec4 SrcB0 = m2->col0;
    const vec4 SrcB1 = m2->col1;
    const vec4 SrcB2 = m2->col2;
    const vec4 SrcB3 = m2->col3;


    mat4x4 ret;
    ret.col0 = additionne(additionne(multiplie(SrcA0, SrcB0.x), multiplie(SrcA1, SrcB0.y)), additionne(multiplie(SrcA2, SrcB0.z), multiplie(SrcA3, SrcB0.w)));
    ret.col1 = additionne(additionne(multiplie(SrcA0, SrcB1.x), multiplie(SrcA1, SrcB1.y)), additionne(multiplie(SrcA2, SrcB1.z), multiplie(SrcA3, SrcB1.w)));
    ret.col2 = additionne(additionne(multiplie(SrcA0, SrcB2.x), multiplie(SrcA1, SrcB2.y)), additionne(multiplie(SrcA2, SrcB2.z), multiplie(SrcA3, SrcB2.w)));
    ret.col3 = additionne(additionne(multiplie(SrcA0, SrcB3.x), multiplie(SrcA1, SrcB3.y)), additionne(multiplie(SrcA2, SrcB3.z), multiplie(SrcA3, SrcB3.w)));
    return ret;
}

mat4x4 projectionPerspective(float aspect, float fov, float zNear, float zFar){
    const float tanDemiFov = tan(fov * .5f);
    const float zPortee = zNear - zFar;

    mat4x4 ret;
    ret.col0 = make_vec4(1.0f / (aspect * tanDemiFov), 0                , 0                            , 0);
    ret.col1 = make_vec4(0                           , 1.0f / tanDemiFov, 0                            , 0);
    ret.col2 = make_vec4(0                           , 0                , (-zNear - zFar) / zPortee    , 1);
    ret.col3 = make_vec4(0                           , 0                , 2.0f * zFar * zNear / zPortee, 0);
    return ret;
}

mat4x4 matriceDeVue(const vec4 eyePos, const vec4 lookAt, const vec4 up) {
    mat4x4 ret;

    const vec4 zaxis = normalise(additionne(lookAt, multiplie(eyePos, -1.0f)));
    const vec4 xaxis = normalise(produitVectoriel(up, zaxis));
    const vec4 yaxis = produitVectoriel(zaxis, xaxis);

    ret.col0 = make_vec4(xaxis.x, xaxis.y, xaxis.z, -produitScalaire(xaxis, eyePos));
    ret.col1 = make_vec4(yaxis.x, yaxis.y, yaxis.z, -produitScalaire(yaxis, eyePos));
    ret.col2 = make_vec4(zaxis.x, zaxis.y, zaxis.z, -produitScalaire(zaxis, eyePos));
    ret.col3 = make_vec4(0      ,0       , 0      , 1                              );
    return ret;
}

vec4 produitVectoriel(vec4 A, vec4 B)
{
    vec4 ret = make_vec4(0,0,0,1);
    ret.x = A.y * B.z - A.z * B.y;
    ret.y = A.z * B.x - A.x * B.z;
    ret.z = A.x * B.y - A.y * B.x;
    ret.w = 1;
    return ret;
}

float produitScalaire(vec4 A, vec4 B) 
{
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

vec4 normalise(vec4 a) {
    return multiplie(a, 1.0f / sqrt(carre(a.x) + carre(a.y) + carre(a.z)));
}
