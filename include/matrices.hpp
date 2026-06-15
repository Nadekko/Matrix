#pragma once

#include "vectors.hpp"
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <limits>
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
    Matrix(size_t r, size_t c, const K& val) : rows(r), cols(c), data(r * c, val) {}
    // Matrix(const Matrix<K>& other)
    //     : rows(other.rows), cols(other.cols), data(other.data) {}

    K& operator()(size_t i, size_t j) {
        if (i >= rows || j >= cols)
            throw std::out_of_range("matrix index");
        return data[i * cols + j];
    }

    const K& operator()(size_t i, size_t j) const {
        if (i >= rows || j >= cols)
            throw std::out_of_range("matrix index");
        return data[i * cols + j];
    }

    std::pair<size_t, size_t> shape() const { return {rows, cols}; }
    bool is_square() const { return rows == cols; }
    size_t size() const { return data.size(); }
    
    void print() const {
        for (size_t i = 0; i < rows; i++) {
            std::cout << "[";
            for (size_t j = 0; j < cols; j++) {
                // A = 1, 2, 3
                //     4, 5, 6
                // stocker tel que A = 1., 2., 3., 4., 5., 6. (pas de colonnes pas de lignes)
                // i=1, j=1 : data[1*3+1] = 4 -> indice 4 : valeur 5
                std::cout << std::setw(6) << std::fixed << std::setprecision(3) << data[i * cols + j] << std::setw(2) << " ";
            }
            std::cout << "]\n";
        }
    }

    void print_proj() const {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                std::cout << std::fixed << std::setprecision(1) << data[i * cols + j] << " ";
            }
            std::cout << "\n";
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
        K norm = K(0);
        for (size_t j = 0; j < cols; j++) {
            K col_sum = K(0);
            for (size_t i = 0; i < rows; i++) {
                col_sum += std::abs((data[i * cols + j]));
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
        K norm = K(0);
        for (size_t i = 0; i < rows; i++) {
            K row_sum = K(0);
            for (size_t j = 0; j < cols; j++) {
                row_sum += std::abs(data[i * cols + j]);
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
            throw std::length_error("Error: matrix must be square.");
        
        K result = K(0);

        for (size_t i = 0; i < rows; i++) {
                result += data[i * cols + i];
        }
        return (result);
    }

    //EX09
    // chaque row d'une matrice devient une colonne
    // utile pour la compatibilté entre C/C++ et les API de rendu comme OpenGL
    // C/C++ les matrices sont stocker lignes par lignes en mémoires
    // OpenGL interprète par défaut les matrices fournis colonnes par colonnes
    // Matrice réelle       ->  A* = Aᵀ (identique car le conjugate d'un nombre réelle est lui même)
    // Matrice complexe     ->  A* ≠ Aᵀ (il faut en plus conjuguer)
    // Matrice Hermitienne  ->  A = A* (idantique à sa propre conjugate transpose)
    // un nombre complexe z peut se présenté tel que z = a + ib,
    // a et b sont des nombres réel et i (l'unité imaginaire) est un nombre particulier tel que i² = -1
    // le conjugué de z, noté z̄, c'est juste inverser le signe de la partie imaginaire z̄ = a - ib
    // std::conj/conjf/conjl <ccomplex> 
    Matrix<K> transpose() const
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

    //EX10
    // REF (row echelon form) ou RREF (reduce row echelon form)
    // algorithm élimination de Gauss
    // Elementary Row Operation
    // - Multiply (or divide) by a non-zero constant
    // - Inter change two row
    // - Add a multiplie of one row to another
    Matrix<K> row_echelon() const
    {
        size_t lead = 0; // column
        Matrix<K> result = *this;

        // Iteration on each row
        for (size_t i = 0; i < rows; i++) {
            
            // if we exceed number of cols
            // matrix reduction is finished
            if (lead >= cols)
                break ;
            
            // current row candidate for pivot
            size_t pivot_row = 0;

            // find pivot
            // searching for a non-zero value on the col
            // if not find increment to the next col
            while (lead < cols) {
                pivot_row = i;
                while (pivot_row < rows && result(pivot_row, lead) == K(0)) {
                    pivot_row++;
                }
                if (pivot_row == rows) {
                    lead++;
                }
                else
                    break ;
            }
            if (lead >= cols)
                break ;
            
            //swap rows if pivot is not in current row
            if (pivot_row != i) {
                for (size_t j = 0; j < cols; j++) {
                    std::swap(result(pivot_row, j), result(i, j));
                }
            }

            //normalize pivot row (make pivot row == 1)
            K div = result(i, lead);
            if (div != K(0) && div != K(1)) {
                for (size_t j = 0; j < cols; j++) {
                    if (result(i, j) == K(0))
                        continue ;
                    result(i, j) /= div;
                }
            }

            // eliminate other rows (below pivot)
            for (size_t k = i + 1; k < rows; k++) {
                K mult = result(k, lead);
                for (size_t j = 0; j < cols; j++) {
                    result(k, j) -= mult * result(i, j);
                }
            }
            lead++;
        }
        return (result);
    }

    Matrix<K> reduce_row_echelon() const
    {
        size_t lead = 0; // column
        Matrix<K> result = *this;

        // Iteration on each row
        for (size_t i = 0; i < rows; i++) {
            
            // if we exceed number of cols
            // matrix reduction is finished
            if (lead >= cols)
                break ;
            
            // current row candidate for pivot
            size_t pivot_row = i;

            // find pivot
            // searching for a non-zero value on the col
            // if not find increment to the next col
            while (lead < cols) {
                pivot_row = i;
                while (pivot_row < rows && result(pivot_row, lead) == K(0)) {
                    pivot_row++;
                }
                if (pivot_row == rows) {
                    lead++;
                }
                else
                    break ;
            }
            if (lead >= cols)
                break ;
            
            //swap rows if pivot is not in current row
            if (pivot_row != i) {
                for (size_t j = 0; j < cols; j++) {
                    std::swap(result(pivot_row, j), result(i, j));
                }
            }

            //normalize pivot row (make pivot row == 1)
            K div = result(i, lead);
            if (div != K(0) && div != K(1)) {
                for (size_t j = 0; j < cols; j++) {
                    if (result(i, j) == K(0))
                        continue ;
                    result(i, j) /= div;
                }
            }

            // eliminate other rows (above and below pivot)
            for (size_t k = 0; k < rows; k++) {
                // skip pivot row itself 
                if (k == i) 
                    continue ;
                K mult = result(k, lead);
                for (size_t j = 0; j < cols; j++) {
                    result(k, j) -= mult * result(i, j);
                }
            }
            lead++;
        }
        return (result);
    }

    //EX11
    // Si A de taille 1x1 le det est égale a son élément
    //                2x2 det(a b) = ad - bc 
    //                       c d
    //                             = (a + b)(c + d) - ac - bd - 2bc = ad - bc 
    // le difference du produit de la premiere diagonal et du produit de la seconde digonal
    // si n > 1, j'ai choisi de suivre la methode d'eliminatation de Gaussian comme pour le row echelon,
    // pour transformer la matrice square en upper_triangle et multiplier sa diagonale
    // Si det(A) = 0, la matrice est non reversible,
    // une matrice dont le determinant est 0
    // écrase les vecteurs qu'elle transforme dans un espace de dimension inferieur.
    // fn determinant::<K>(&mut self) -> K;
    K determinant() const
    {
        if (!is_square())
            throw std::length_error("Error : matrix must be square.");

        size_t  n = rows;
        size_t  pivot = 0;
        K       det = 1;
        K       factor = 0;
        Matrix<K> result = *this;

        // case 1x1
        if (size() == 1)
            return (data[0]);

        // other case
        else {

            for (size_t i = 0; i < n ; i++) {

                pivot = i;
                while (pivot < n && result(pivot, i) == K(0)) {
                    pivot++;
                }
                if (pivot == n) {
                    return (K(0));
                }
                if (pivot != i) {
                    for (size_t j = 0; j < n; j++) {
                        std::swap(result(i, j), result(pivot, j));
                    }
                    det *= K(-1);
                }

                det *= result(i, i);

                for (size_t j = i + 1; j < n; j++) {
                    factor = result(j, i) / result(i, i);
                    for (size_t k = i; k < n; k++) {
                        result(j, k) -= factor * result(i, k);
                    }
                }
            }
        }
        return (det);
    }

    //EX12
    // une matrice se dit inversible tel que  A−1A = AA-1 = I (son identité)
    // A devient I (A-1A = I)
    // I divent A-1 (A-1I = A-1)
    Matrix<K> inverse() const
    {
        size_t c_aug = 2 * cols; 
        Matrix<K> m_aug(rows, c_aug, K(0));
        Matrix<K> temp = *this;
        Matrix<K> result(rows, cols, K(0));
        if (!is_square())
            throw std::invalid_argument("Error: matrix must be square");
        else if (determinant() == 0)
            throw std::domain_error("Error: a matrix with a det(A) == 0, is not inversible");
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                m_aug(i, j) = temp(i, j);
            }
            m_aug.data[i * c_aug + cols + i] = K(1);
        }
        Matrix<K> rref = m_aug.reduce_row_echelon();
        for (size_t k = 0; k < rows; k++) {
            for (size_t l = 0; l < cols; l++) {
                // k = 2 * 6 + 1 + l = 3 = 16
                // 0  1  2  | 3  4  5
                // 6  7  8  | 9  10 11
                // 12 13 14 | 15 (16) 17
                result(k, l) = rref.data[k * c_aug + cols + l]; 
            }
        }
        return (result);
    }

    //EX13
    //fn rank::<K>(&mut self) -> usize;
    //Le rang d'une matrice est le nombre maximal de lignes ou de colonnes linéairement indépendantes dans cette matrice.
    // on peut dire aussi que le rang donne la dimension de la matrice.
    //le rank ne peut être plus grand que ça largeur (cols)
    //si la matrice est carré et que le determinant est non-null alors la rank est égale au nombre de rows
    size_t rank() const
    {

        Matrix<K> temp = row_echelon();
        size_t rank = 0;
        
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if (temp(i, j) != K(0)) {
                    rank++;
                    break ;
                }
            }
        }
        return (rank);
    }
};
