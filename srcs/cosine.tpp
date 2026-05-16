#include "../include/vectors.hpp"

// fn angle_cos::<K>(u: &Vector::<K>, v: &Vector::<K>) -> f32;
// cos(θ) = u⋅v / ​∣∣u∣∣*∣∣v∣∣ 
// function return the value of cos(θ) (-1 =< x <= 1)
template <typename K>
K angle_cos(const Vector<K>& u, const Vector<K>& v)
{
    if (u.size() != v.size())
        throw std::length_error("Error : u and v must have the same number of elements");
    
    K norm_product = u.norm_l2() * v.norm_l2();
    if (norm_product == K(0))
        throw std::domain_error("Error: angle is undefined for zero-length vectors");
    K angle_cos = u.dot(v) / norm_product;

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