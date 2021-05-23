#include "glmath.h"

float carre(float a) {
    return a * a;
}

mat4x4 ProjectionOrthographique(float left, float right, float bottom, float top, float zNear, float zFar) {
    mat4x4 ret = matriceDidentite(1);

    ret.col0.x = 2.0f / (right - left);
    ret.col1.y = 2.0f / (top - bottom);
    ret.col2.z = -2.0f / (zFar - zNear);

    ret.col3.x = -(right + left) / (right - left);
    ret.col3.y = -(top + bottom) / (top - bottom);
    ret.col3.z = -(zFar + zNear) / (zFar - zNear);

    return ret;
}

vec4 make_vec4(float x, float y, float z, float w) {
    return (vec4) { x, y, z, w };
}

vec4 multiplie(vec4 vec, float f)
{
    return (vec4) { vec.x * f, vec.y * f, vec.z * f, vec.w * f };
}

vec4 additionne(vec4 v1, vec4 v2)
{
    return (vec4) { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w };
}

mat4x4 matriceDidentite(float f) {
    mat4x4 ret;
    //creer la matrice
    ret.col0 = make_vec4(f, 0, 0, 0);
    ret.col1 = make_vec4(0, f, 0, 0);
    ret.col2 = make_vec4(0, 0, f, 0);
    ret.col3 = make_vec4(0, 0, 0, f);
    return ret;
}

mat4x4 matriceDeTaille(float x, float y, float z) {
    mat4x4 ret;
    //creer la matrice
    ret.col0 = make_vec4(x, 0, 0, 0);
    ret.col1 = make_vec4(0, y, 0, 0);
    ret.col2 = make_vec4(0, 0, z, 0);
    ret.col3 = make_vec4(0, 0, 0, 1);
    return ret;
}

mat4x4 matriceDeTranslation(float x, float y, float z) {
    mat4x4 ret;
    //forme la matrice
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

    //u prends une norme égale a 1
    u = normalise(u);

    //ameliore la complexité temporelle
    const float cosA = cos(A);
    const float sinA = sin(A);
    const float IcosA = 1.0f - cosA;

    //composer la matrice
    mat4x4 ret;
    ret.col0 = make_vec4(cosA + carre(u.x) * IcosA     , u.y * u.x * IcosA + u.z * sinA, u.z * u.x * IcosA - u.y * sinA, 0);
    ret.col1 = make_vec4(u.x * u.y * IcosA - u.z * sinA, cosA + carre(u.y) * IcosA     , u.z * u.y * IcosA - u.x * sinA, 0);
    ret.col2 = make_vec4(u.x * u.z * IcosA - u.y * sinA, u.y * u.z * IcosA - u.x * sinA, cosA + carre(u.z) * IcosA     , 0);
    ret.col3 = make_vec4(                             0,                              0,                              0, 1);
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

mat4x4 projectionPerspective(float aspect, float fov, float zNear, float zFar) {
    const float tanDemiFov = tan(fov * .5);
    const float zPortee = zNear - zFar;

    mat4x4 ret;
    ret.col0 = make_vec4(1.0f / (aspect * tanDemiFov), 0, 0, 0);
    ret.col1 = make_vec4(0, 1.0f / tanDemiFov, 0, 0);
    ret.col2 = make_vec4(0, 0, -(-zNear - zFar) / zPortee, -1);
    ret.col3 = make_vec4(0, 0, 2.0f * zFar * zNear / zPortee, 0);
    return ret;
}

mat4x4 matriceDeVue(const vec4 eyePos, const vec4 lookAt, const vec4 up) {
    mat4x4 ret = matriceDidentite(1);

    const vec4 f = normalise(additionne(lookAt, multiplie(eyePos, -1.0f)));
    const vec4 s = normalise(produitVectoriel(f, up));
    const vec4 u = produitVectoriel(s, f);


    ret.col0.x = s.x;
    ret.col1.x = s.y;
    ret.col2.x = s.z;
    ret.col0.y = u.x;
    ret.col1.y = u.y;
    ret.col2.y = u.z;
    ret.col0.z = -f.x;
    ret.col1.z = -f.y;
    ret.col2.z = -f.z;
    ret.col3.x = -produitScalaire(s, eyePos);
    ret.col3.y = -produitScalaire(u, eyePos);
    ret.col3.z = produitScalaire(f, eyePos);

    return ret;
}

vec4 produitVectoriel(vec4 A, vec4 B)
{
    vec4 ret = make_vec4(0, 0, 0, 1);
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
    return multiplie(a, 1.0f / sqrt((double)carre(a.x) + (double)carre(a.y) + (double)carre(a.z)));
}