#include "../include/vectors.hpp"

// fn cross_product::<K>(u: &Vector::<K>, v: &Vector::<K>) -> Vector::<K>;
// the result is a vector, perpendicular by the other two
// its length equals the area of the parallelogram formed by u and v
// cx = aybz - azby
// cy = azbx - axbz
// cz = axby - aybx
template <typename K>
Vector<K> cross_product(const Vector<K>& u, const Vector<K>& v)
{
    constexpr size_t dim = 3;
    if ((u.size() != dim) || (v.size() != dim))
        throw std::length_error("Error : vectors are not 3-dimensional.");
    
    Vector<K> result(dim, K(0));

    result.data[0] = (u.data[1] * v.data[2]) - (u.data[2] * v.data[1]); // cx
    result.data[1] = (u.data[2] * v.data[0]) - (u.data[0] * v.data[2]); // cy
    result.data[2] = (u.data[0] * v.data[1]) - (u.data[1] * v.data[0]); // cz

    return (result);
}