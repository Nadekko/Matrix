#include "../include/vectors.hpp"
#include "../include/matrices.hpp"

// EX02

//fn lerp::<V>(u: V, v: V, t: f32) -> V;
// u + t * (v - u)
// lerp : use to travel progressivly between two data.

/* * * VECTORS * * */
template<typename K>
Vector<K> lerp(const Vector<K>& u, const Vector<K>& v, float t)
{
    if (t < 0 || t > 1)
        throw std::invalid_argument("Error: t must be between 0 and 1 (t ∈ [0; 1])");
    if (u.size() != v.size())
        throw std::length_error("Error : u element count (" + std::to_string(u.size())
            + ") must match v element count (" + std::to_string(v.size()) + ")");;

    size_t len = u.size();
    // init result with size of v ∈ u,  ∀ val ∈ result, val = 0;
    Vector<K> result(len, K(0));

    for (size_t i = 0; i < len; i++) {
        // fma[Fused Multiply-Add](x * y) + z
        // without fma CPU do 2 separite operation instead of one.
        if constexpr (std::is_floating_point_v<K>)
            result.data[i] = std::fma(t, v.data[i] - u.data[i], u.data[i]);
        else
            result.data[i] = t * (v.data[i] - u.data[i]) + u.data[i];
    }
    return (result);
};

/* * * MATRICES * * */
template<typename K>
Matrix<K> lerp(const Matrix<K>& u, const Matrix<K>& v, float t)
{
    if (t < 0 || t > 1)
        throw std::invalid_argument("Error: t must be between 0 and 1 (t ∈ [0; 1])");
    if (u.shape() != v.shape())
        throw std::length_error("Error: matrices must have the same shape");
    
    Matrix<K> result(u.rows, u.cols, K(0));

    for (size_t i = 0; i < u.size(); i++) {
        if constexpr (std::is_floating_point_v<K>)
            // fma[Fused Multiply-Add](x * y) + z
            // without fma CPU do 2 separate operation instead of one.
            result.data[i] = std::fma(t, v.data[i] - u.data[i], u.data[i]);
        else
            result.data[i] = t * (v.data[i] - u.data[i]) + u.data[i];
    }
    return (result);
}

template <typename K>
K lerp(K u, K v, float t)
{
    if (t < 0 || t > 1)
        throw std::invalid_argument("Error: t must be between 0 and 1 (t ∈ [0; 1])");
   
    K result (0);
    if constexpr (std::is_floating_point_v<K>)
            // fma[Fused Multiply-Add](x * y) + z
            // without fma CPU do 2 separate operation instead of one.
            result = std::fma(t, v - u, u);
        else
            result = t * (v - u) + u;
    return (result);
}

// Trouver un point entre deux valeurs selon un pourcentage t :

//     u = [0, 0],  v = [10, 10]

//     t = 0.0  →  [0, 0]    (on est à u)
//     t = 0.5  →  [5, 5]    (on est au milieu)
//     t = 1.0  →  [10, 10]  (on est à v)

// Quand l'utiliser

// Animations: Déplacer un objet progressivement d'un point A à un point B,
// Couleurs:   Faire un dégradé entre rouge et bleu
// Caméra:     Transition fluide entre deux positions de caméra
// Audio:      Fondu enchaîné entre deux sons