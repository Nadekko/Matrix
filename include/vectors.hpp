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
        std::cout << std::fixed << std::setprecision(2);
        for (const K& val : data)
        std::cout << "[" << val << "]\n";
    };

    // combiner ou comparer des "quantitées" qui parte du même repère
    // déplacement total / déplacer un objet
    // soustaire deux position permet de trouver la direction qui va d'un point à un autre
    void add(const Vector<K>& v)
    {
        if (data.size() != v.size())
            throw std::length_error("Error : u element count (" + std::to_string(data.size())
                + ") must match v element count (" + std::to_string(v.size()) + ")");;

        for (size_t i = 0; i < data.size(); ++i)
            data[i] += v.data[i];
    }
    void    sub(const Vector<K>& v)
    {
        if (data.size() != v.size())
            throw std::length_error("Error : u element count (" + std::to_string(data.size())
                + ") must match v element count (" + std::to_string(v.size()) + ")");;

        for (size_t i = 0; i < data.size(); i++)
            data[i] -= v.data[i];
    }
    // redimensionner une taille ou une intensité sans changer la direction
    void    scl(K a)
    {
        // range-based 
        for (K& val : data)
            val *= a;
    }

    // EX03
    /*
        Soit u = (2, 3, 7) et v = (8, 1, 6)
        u·v = (2*8) + (3*1) + (7*6)

        u·v = ||u|| × ||v|| × cos(θ)  (interprétation géométrique générale)
        où θ designe l'angle entre u et v.

        u·v > 0 --> θ est aigu.
        u·v < 0 --> θ est obtus.
        u·v = 0 --> signifie qu'il sont orthogonaux, donc les vecteurs sont perpendiculaires.

        combine deux vectors pour obtenir un sclaire, indiquant si les deux vecteurs vont dans le même directions
    */
    K dot(const Vector<K>& v) const
    {
        if (data.size() != v.data.size())
            throw std::length_error("Error : u element count (" + std::to_string(data.size())
                + ") must match v element count (" + std::to_string(v.size()) + ")");
            
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
    // distance de marche sur une grille
    K norm_l1() const
    {
        K norm = K(0);
        
        for (const K& val : data)
            norm += std::abs(val);
        return (norm);
    }

    //∞-norm: ∥v∥∞ (also called the supremum norm)
    // le plus grand éléments en valeur abs
    K norm_inf() const
    {
        K norm = K(0);
        
        for (const K& val : data)
            norm = std::max(std::abs(val), norm);
        return (norm);
    }

    K pythagore_impl() const
    {        
        K sum = K(0);
        
        for (const K& val : data)
        sum += val * val;
        return (sum);
    }

    /*
        méthode de Heron + méthode de Newton-Raphson

        norm = 25
        x₀ = 25/2 = 12.5

        It1 : x₁ = (12.5 + 25/12.5) / 2 = (12.5 + 2) / 2 = 7.25
        It2 : x₂ = (7.25 + 25/7.25) / 2 = (7.25 + 3.45) / 2 = 5.35
        It3 : x₃ = (5.35 + 25/5.35) / 2 = (5.35 + 4.67) / 2 = 5.01
        It4 : x₄ = (5.01 + 25/5.01) / 2 ≈ 5.0
        It5 : x₅ = (5.0 + 25/5.0) / 2 = (5.0 + 5.0) / 2 = 5.0

        x₅ = x₄ = 5.0
    */
    K method_sqrt(K val) const
    {
        K x = val / K(2);
        K prev = K(0);

        while (x != prev)
        {
            prev = x;
            x = (x + (val / x)) / K(2);
        }
        return (x);
    }
    
    //l2-norm: ∥v∥ or ∥v∥2 (also called the Euclidean norm)
    // distance à vol d'oiseau
    // u = [3, 4]
    // ||u|| = √(3² + 4²) = √25 = 5
    K norm_l2() const
    {
        K norm= pythagore_impl();

        // if the vector is zero, root is zero
        if (norm == K(0)) { return (norm); }
        
        // méthode de Heron + méthode de Newton-Raphson
        return (method_sqrt(norm));
    }
};