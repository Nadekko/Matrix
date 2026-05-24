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
        std::cout << std::fixed << std::setprecision(2);
        for (size_t i = 0; i < rows; i++) {
            std::cout << "[";
            for (size_t j = 0; j < cols; j++) {
                // A = 1, 2, 3
                //     4, 5, 6
                // stocker tel que A = 1., 2., 3., 4., 5., 6. (pas de colonnes pas de lignes)
                // i=1, j=1 : data[1*3+1] = 4 -> valeur 5
                std::cout << data[i * cols + j];
                if (j < cols - 1)
                    std::cout << ", ";
            }
            std::cout << "]\n";
        }
    }

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
        K norm = (0);
        for (size_t i = 0; i < cols; i++) {
            K col_sum = K(0);
            for (size_t j = 0; j < rows; j++) {
                col_sum += abs(data[j * cols + i]);
            }
            norm = std::max(col_sum, norm);
        }
        return (norm);
    }

    K pythagore_impl() const
    {        
        K sum = K(0);
        
        for (const K& val : data)
            sum += val * val;
        return (sum);
    }

    //Frobenius norm: ∥A∥_F = √(Σᵢⱼ aᵢⱼ²)
    K norm_F() const
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

    //∞-norm: ∥v∥∞ (also called the supremum norm)
    K norm_inf() const
    {
        K norm = (0);
        for (size_t i = 0; i < rows; i++) {
            K row_sum = K(0);
            for (size_t j = 0; j < cols; j++) {
                row_sum += abs(data[i * cols + j]);
            }
            norm = std::max(row_sum, norm);
        }
        return (norm);
    }

    //EX07
    // A est m*n -> m lignes, n colonnes
    // u est dans Rn -> n élémentes
    // result dans Rm -> m éléments
    // multiplacation de chaque elements par ligne de la matrice par chaque elements du vector
    Vector<K> mul_vec(const Vector<K>& vec) const
    {
        if (vec.size() != cols)
            throw std::length_error("Error: vector size (" + std::to_string(vec.size()) +
                ") must match matrix column count (" + std::to_string(cols) + ")");

        Vector<K> result(rows, K(0));

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if constexpr (std::is_floating_point_v<K>)
                    result.data[i] = fma(data[i * cols + j], vec.data[j], result.data[i]);
                else
                    result.data[i] += data[i * cols + j] * vec.data[j];
            }
        }
        return (result);
    }

    // A est m*n
    // B est n*p; le nombre colonnes dans A doivent être égale au nombre de lignes dans B
    // result est m*p
    // multication de chaque elements par ligne de la matrice A par chaque elements par colonne de la matrice B 
    Matrix<K> mul_mat(const Matrix<K>& mat) const
    {
        if (cols != mat.rows)
            throw std::length_error("Error: A column count (" + std::to_string(cols) + 
                ") must match B row count (" + std::to_string(mat.rows) + ")");

        Matrix<K> result (rows, mat.cols, K(0));

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                for (size_t k = 0; k < mat.cols; k++) {
                    if constexpr (std::is_floating_point_v<K>)
                        result.data[i * mat.cols + k] = fma(data[i * cols + j], mat.data[j * mat.cols + k], result.data[i * mat.cols + k]);
                    else
                        result.data[i * mat.cols + k] += data[i * cols + j] * mat.data[j * mat.cols + k];
                }
            }
        }
        return (result);
    }

    //EX08
    // la trace d'une matrice carré est la somme de ses coefficients diagonaux. noté Tr(M)
    K   trace() const
    {
        if (!is_square())
            throw std::length_error("Error: matrice must be square.");
        
        K result = K(0);

        for (size_t i = 0; i < rows; i++) {
                    result = data[i * cols + i];
        }
        return (result);
    }

    //EX09
    Matrix<K> transpose()
    {
        Matrix<K> result(cols, rows, K(0));

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                // i=0, j=1 : data[0*3+1] = 2   -> result[1][0] = result[1*2+0] = 2
                // i=1, j=0 : data[1*3+0] = 4   -> result[0][1] = result[0*2+1] = 4
                result.data[j * rows + i] = data[i * cols + j];
            }
        }
        return (result);
    }
};

