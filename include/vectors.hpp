#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>
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
    // mutable K arccos = K(0); //angle
    
    Vector(std::initializer_list<K> list) : data(list) {
        if (list.size() == 0)
        throw std::length_error("Error: initializer list must not be empty");
    }
    Vector(size_t n, K val) : data(n, val) {}
    
    size_t size() const { return data.size(); }
    // void set_arccos(K arcc) const { arccos = arcc; }
    // K get_arccos() const { return (arccos); }
    
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
             result = std::fma(data[i], v.data[i], result);
            else
              result = data[i] * v.data[i] + result;
        }
        return (result);
    }

    //l1-norm: ∥v∥1 (also called the Taxicab norm or Manhattan norm)
    K norm_l1() const
    {
        K norm = K(0);
        
        for (const K& val : data)
            norm += std::abs(val);
        return (norm);
    }

    //∞-norm: ∥v∥∞ (also called the supremum norm)
    K norm_inf() const
    {
        K norm = K(0);
        
        for (const K& val : data)
            norm = std::max(std::abs(val), norm);
        return (norm);
    }

    //l2-norm: ∥v∥ or ∥v∥2 (also called the Euclidean norm)
    // u = [3, 4]
    // ||u|| = √(3² + 4²) = √25 = 5
    K pythagore_impl() const
    {        
        K sum = K(0);

        for (const K& val : data)
            sum += val * val;
        return (sum);
    }
    
    K norm_l2() const
    {
        K norm= pythagore_impl();

        // if the vector is zero, root is zero
        if (norm == K(0)) { return (norm); }
        
        // méthode de Heron + méthode de Newton-Raphson
        K x = norm / K(2);
        K prev = K(0);

        while (x != prev) {
            prev = x;
            x = (x + (norm / x)) / K(2);
        }
        return (x);
    }
};