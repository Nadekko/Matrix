#include "matrices.hpp"

//EX14 (bonus)
// ratio : ratio de la fenêtre (la largeur de la fenêtre divisé par sa hauteur)
// angle : angle de vue de la caméra (70° pour un œil humain)
// near : distance la plus proche de la caméra qu'il faut afficher
// far : distance la plus éloignée de la caméra qu'il faut afficher
template<typename K>
Matrix<K> projection(float fov, float ratio, float near, float far)
{
    Matrix<K> P(4, 4, 0.0f);

    float   f = 1 / tan(fov / 2); //
    
}