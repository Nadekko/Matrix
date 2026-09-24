#pragma once
#include <vector>

template <typename K>
K sum_of_squares(const std::vector<K>& data)
{
    K sum = K(0);
    for (const K& val : data)
        sum += val * val;
    return sum;
}

template <typename K>
K my_abs(K v) { return v < K(0) ? -v : v; }

template <typename K>
bool is_zero(const K& x) {
    return my_abs(x) < 1e-6;
}

template <typename K>
K normalize_zero(const K& x) {
    return is_zero(x) ? K(0) : x;
}



//     Héron / Newton-Raphson

//     norm = 25
//     x₀ = 25/2 = 12.5

//     It1 : x₁ = (12.5 + 25/12.5) / 2 = (12.5 + 2) / 2 = 7.25
//     It2 : x₂ = (7.25 + 25/7.25) / 2 = (7.25 + 3.45) / 2 = 5.35
//     It3 : x₃ = (5.35 + 25/5.35) / 2 = (5.35 + 4.67) / 2 = 5.01
//     It4 : x₄ = (5.01 + 25/5.01) / 2 ≈ 5.0
//     It5 : x₅ = (5.0 + 25/5.0) / 2 = (5.0 + 5.0) / 2 = 5.0

//     x₅ = x₄ = 5.0
// */
// K method_sqrt(K val)
// {
    
//     K x = val / K(2);
//     K prev = K(0);

//     while (x != prev)
//     {
//         prev = x;
//         x = (x + (val / x)) / K(2);
//     }
//     return (x);
// }