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

    float   f = 1 / std::tan(fov / 2); // facteur d'échelle basé sur l'angle


    P(0, 0) = f / ratio; // ajuste la largeur selon le ratio de l'écran

    P(1, 1) = f; // ajuste selon l'angle de vue

    P(2, 2) = far / (near - far);
    P(2, 3) = -1.0f; // force la division par w / effet de perspective
    P(3, 2) = std::fma(near, far, 0.0f) / (near - far); // near*far / (near-far)
    // convertit la profondeur (z) en valeur normalisée
    // pour le depth buffer (distance à la caméra)
    return (P);
}