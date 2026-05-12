#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include "colors.hpp"

// ***** VECTORS *****//
template<typename K>
struct Vector
{
    std::vector<K> data;
    mutable K root = K(0);
    // mutable K inverse_cos = K(0); //angle
    
    Vector(std::initializer_list<K> list) : data(list) {
        if (list.size() == 0)
        throw std::length_error("Error: initializer list must not be empty");
    }
    Vector(size_t n, K val) : data(n, val) {}
    
    size_t size() const { return data.size(); }
    void set_root(K r) const { root = r; }
    K get_root() const { return (root); }
    
    void    print() const {
        std::cout << std::fixed << std::setprecision(1);
        for (const K& val : data)
        std::cout << "[" << val << "]\n";
    };

    void add(const Vector<K>& v)
    {
        if (data.size() != v.size())
            throw std::length_error("Error: vectors must have the same size");

        for (size_t i = 0; i < data.size(); ++i)
            data[i] += v.data[i];
    }

    void    sub(const Vector<K>& v)
    {
        if (data.size() != v.size())
            throw std::length_error("Error: vectors must have the same size");

        for (size_t i = 0; i < data.size(); i++)
            data[i] -= v.data[i];
    }

    void    scl(K a)
    {
        // range-based 
        for (K& val : data)
            val *= a;
    }

    // Soit u = (2, 3, 7) et v = (8, 1, 6)
    // u·v = (2*8) + (3*1) + (7*6)

    // u·v = ||u|| × ||v|| × cos(θ)  (interprétation géométrique générale)
    // où θ designe l'angle entre u et v.

    // u·v > 0 --> θ est aigu.
    // u·v < 0 --> θ est obtus.
    // u·v = 0 --> signifie qu'il sont orthogonaux, donc les vecteurs sont perpendiculaires.
    K dot(const Vector<K>& v) const
    {
        if (data.size() != v.data.size())
            throw std::length_error("Error: vectors must have the same size");
            
        size_t len = data.size();
        
        K result = K(0);
            
        for (size_t i = 0; i < len; i++) {
            if constexpr (std::is_floating_point_v<K>)
             result = fma(data[i], v.data[i], result);
            else
              result = data[i] * v.data[i] + result;
        }
        return (result);
    }

    //l1-norm: ∥v∥1 (also called the Taxicab norm or Manhattan norm)
    K norm_l1() const
    {
        size_t len = data.size();

        K norm1 = K(0);
        
        for (size_t i = 0; i < len; i++) {
            norm1 += std::abs(data[i]);
        }
        return (norm1);
    }

    //∞-norm: ∥v∥∞ (also called the supremum norm)
    K norm_inf() const
    {
        size_t len = data.size();

        K norm_inf = K(0);
        
        for (size_t i = 0; i < len; i++) {
            norm_inf = std::max(std::abs(data[i]), norm_inf);
        }
        return (norm_inf);
    }

    //l2-norm: ∥v∥ or ∥v∥2 (also called the Euclidean norm)
    // u = [3, 4]
    // ||u|| = √(3² + 4²) = √25 = 5
    K norm_l2() const
    {
        size_t len = data.size();

        K norm_l2 = K(0);
        
        for (size_t i = 0; i < len; i++) {
            norm_l2 += data[i] * data[i];
        }
        // if the vector is zero, root is zero
        if (norm_l2 == K(0)) {
            set_root(norm_l2);
            return (norm_l2);
        }
        // calculer la racine carré sans la fonction sqrt
        // méthode de Heron + méthode de Newton-Raphson
        K x = norm_l2 / K(2);
        K prev = K(0);

        while (x != prev) {
            prev = x;
            x = (x + (norm_l2 / x)) / K(2);
        }
        set_root(x);
        return (x);
    }
};