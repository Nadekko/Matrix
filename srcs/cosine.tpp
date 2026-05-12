#include "../include/vectors.hpp"

// fn angle_cos::<K>(u: &Vector::<K>, v: &Vector::<K>) -> f32;
// cos(θ) = adjacente side / hypotenuse
// cos(θ) =∣∣u∣∣*∣∣v∣∣ / u⋅v​
template <typename K>
K angle_cos(const Vector<K>& u, const Vector<K>& v)
{
    if (u.size() != v.size())
        throw std::length_error("Error : u and v must have the same number of elements");
    
    K angle_cos = K(0);
    // carefull with division by 0
    angle_cos = u.dot(v) / (u.norm_l2() * v.norm_l2());

    //check arcsin taylor serie
    // K inverse_cos = K(0);

    return (angle_cos);
}

// arccos(x) = 2 / π  - arcsin(x) = θ
// template <typename K>
// K arcsin_taylor(K x, size_t terms = 10)
// {
//     K result = x;
//     K numerator = x;
//     K denominator = K(1);
    
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