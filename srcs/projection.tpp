#include "../include/matrices.hpp"

//EX14 (bonus)
// ratio : ratio de la fenêtre (la largeur de la fenêtre divisé par sa hauteur)
// angle : angle de vue de la caméra (70° pour un oeil humain)
// near : distance la plus proche de la caméra qu'il faut afficher
// far : distance la plus éloignée de la caméra qu'il faut afficher
// f = 1.0 / tan(fov / 2.0)
// P = [
//   f/ratio,  0,   0,              0,
//   0,        f,   0,              0,
//   0,        0,   far/(near-far), -1,
//   0,        0,   (near*far)/(near-far), 0
// ]

template<typename K>
Matrix<K> projection(float fov, float ratio, float near, float far)
{
    Matrix<K> P(4, 4, 0.0f);

    float   f = 1 / std::tan(fov / 2);


    P(0, 0) = f / ratio;

    P(1, 1) = f;

    P(2, 2) = far / (near - far);
    P(3, 2) = std::fma(near, far, 0.f) / (near - far); // near*far / (near-far)

    P(2, 3) = -1.0f;

    return (P);
}