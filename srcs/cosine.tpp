#include "../include/vectors.hpp"

// cos(θ) proche de 1  -> vecteurs alignés -> très similaires
// cos(θ) proche de 0  -> vecteurs orthogonaux -> pas de lien
// cos(θ) proche de -1 -> vecteurs opposés -> très différents
// mesure de ressamblance entre deux objets

// fn angle_cos::<K>(u: &Vector::<K>, v: &Vector::<K>) -> f32;
// cos(θ) = u⋅v / ​∣∣u∣∣*∣∣v∣∣ 
// function return the value of cos(θ) (-1 =< x <= 1)
template <typename K>
K angle_cos_vec(const Vector<K>& u, const Vector<K>& v)
{
    if (u.size() != v.size())
        throw std::length_error("Error : u element count (" + std::to_string(u.size())
            + ") must match v element count (" + std::to_string(v.size()) + ")");

    K norm_product = u.norm_l2() * v.norm_l2();
    if (norm_product == K(0))
        throw std::domain_error("Error: angle is undefined for zero-length vectors");
    K angle_cos = u.dot(v) / norm_product;

    return (angle_cos);
}

template <typename K>
K angle_cos_mat(const Matrix<K>& u, const Matrix<K>& v)
{
    if (u.shape() != v.shape())
        throw std::invalid_argument("Error : Matrices must have the same shape");
    
    K frob_product = u.norm_F() * v.norm_F();
    if (frob_product == K(0))
        throw std::domain_error("Error : angle is undefined for zero-size matrices");
    K angle_cos = u.frobenius_dot_product(v) / frob_product;

    return (angle_cos);
}


// optionel function to get the value of the angle
// θ = cos-1 [(a · b) / (|a| |b|)]
// Approximates arcsin(x) using its Taylor series expansion.
// arcsin(x) = x + (1/6)x³ + (3/40)x⁵ + (15/336)x⁷ + ...
// Each iteration adds one more term, improving precision.
// (cos-1(θ)) 
// Computes arccos(x) using the identity:
// arccos(x) = π/2 - arcsin(x)
// template <typename K>
// K arcsin_taylor(K x)
// {
//     K result = x;
//     K numerator = x;
//     K denominator = K(1);
//     size_t terms = 10;

//     for (size_t i = 1; i < terms; ++i)
//     {
//         numerator *= x * x * (2 * i - 1) / (2 * i);
//         denominator *= (2 * i + 1);
//         result += numerator / denominator;
//     }
//     return result;
// }
// template <typename K>
// K arccos_impl(K x)
// {
//     K pi = K(3.14159265358979323846);
//     return pi / K(2) - arcsin_taylor(x);
// }