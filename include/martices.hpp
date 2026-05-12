#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include "colors.hpp"

template<typename K>
struct Matrix
{
    size_t rows;
    size_t cols;
    std::vector<K> data;
    mutable K root = K(0);

    Matrix(std::initializer_list<std::initializer_list<K>> list) : data() {
        if (list.size() == 0)
            throw std::length_error("Error: initializer list must not be empty.");
        if (list.begin()->size() == 0)
            throw std::length_error("Error: rows must not be empty.");
        rows = list.size();
        cols = list.begin()->size();
        for (auto& row : list) {
            if (row.size() != cols)
               throw std::length_error("Error: all rows must have the same size.");
        }
        for (auto& row : list)
            for (auto& val : row)
                data.push_back(val);
    };
    Matrix(size_t r, size_t c, K val) : rows(r), cols(c), data(r * c, val) {}

    std::pair<size_t, size_t> shape() const { return {rows, cols}; }
    bool is_square() const { return rows == cols; }
    size_t size() const { return data.size(); }
    
    void print() const {
        std::cout << std::fixed << std::setprecision(1);
        for (size_t i = 0; i < rows; i++) {
            std::cout << "[";
            for (size_t j = 0; j < cols; j++) {
                std::cout << data[i * cols + j];
                if (j < cols - 1)
                    std::cout << ", ";
            }
            std::cout << "]\n";
        }
    };

    // EX00 
    void    add(const Matrix<K>& m)
    {
        if (shape() != m.shape())
            throw std::length_error("Error: matrices must have the same shape.");
        for (size_t i = 0; i < data.size(); i++)
            data[i] += m.data[i];
    }

    void    sub(const Matrix<K>& m)
    {
        if (shape() != m.shape())
            throw std::length_error("Error: matrices must have the same shape.");
        for (size_t i = 0; i < data.size(); i++)
            data[i] -= m.data[i];
    }

    void scl(K a)
    {
        for (K& val : data)
            val *= a;
    }

    // EX04
    //1-norm: ∥v∥1 (also called the Taxicab norm or Manhattan norm)
    K norm_l1() const
    {
        K norm_l1 = (0);
        for (size_t i = 0; i < cols; i++) {
            K col_sum = K(0);
            for (size_t j = 0; j < rows; j++) {
                col_sum += abs(data[j * cols + i]);
            }
            norm_l1 = std::max(col_sum, norm_l1);
        }
        return (norm_l1);
    }

    //Frobenius norm: ∥A∥_F = √(Σᵢⱼ aᵢⱼ²)
    K norm_F() const
    {
        K norm_F = K(0);

        for (size_t i = 0; i < data.size(); i++) {
            norm_F += data[i] * data[i];
        }
        if (norm_F == K(0)) {
            set_root(norm_F);
            return (norm_F);
        }

        K x = norm_F / K(2);
        K prev = K(0);
        // calculer la racine carré sans la fonction sqrt
        // méthode de Heron + méthode de Newton-Raphson
        while (x != prev) {
            prev = x;
            x = (x + (norm_F / x)) / K(2);
        }
        set_root(x);
        return (x);
    }

    //∞-norm: ∥v∥∞ (also called the supremum norm)
    K norm_inf() const
    {
        K norm_inf = (0);
        for (size_t i = 0; i < rows; i++) {
            K row_sum = K(0);
            for (size_t j = 0; j < cols; j++) {
                row_sum += abs(data[i * cols + j]);
            }
            norm_inf = std::max(row_sum, norm_inf);
        }
        return (norm_inf);
    }
};

