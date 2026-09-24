#include "../include/vectors.hpp"
#include "../include/matrices.hpp"

// EX01
// Multipplier des vecteurs par des scalaires et les addtionner:

//     v1 = [1, 0], v2 = [0, 1];
//     coef = [3, 5];

//     résultat = 3 * [1, 0] + 5 * [0, 1];

// Décrire n'importle quel point d'un espace à partir de vecteurs de base

// Quand l'utiliser

// Transformer des coordonnées (c'est la base des matrices de transformation)
// Exprimer un vecteur comme combinaison d'autres vecteurs (base de l'algèbre linéaire)
// Shaders 3D, physique, machine learning

// Graphisme 3D: Décrire n'importe quel point d'un espace à partir de vecteurs de base,
// Mécanique:    Combiner des forces qui s'appliquent sur un objet,
// Machine Learning: Chaque couche d'un réseau de neurones est une combinaison linéaire

// résoudre des systemes d'équations
// créer des espaces géométriques

// * * * VECTORS * * *//
template<typename K>
Vector<K> linear_combination(const std::vector<Vector<K>>& u, const std::vector<K>& coefs)
{
    if (u.empty() || coefs.empty())
        throw std::invalid_argument("Error : one or both entry are empty");
    if (u.size() != coefs.size())
        throw std::length_error("Error : u element count (" + std::to_string(u.size())
            + ") must match coefs element count (" + std::to_string(coefs.size()) + ")");

    size_t len = u[0].size();
    if (len == 0)
        throw std::invalid_argument("Error : size is 0");
    for (size_t i = 1; i < u.size(); i++) {
        if (len != u[i].size()) {
             throw std::length_error("Error: all vectors in u must have the same size");
        }
    }
    // init result with size u, val = 0;
    Vector<K> result(len, K(0));

    for (size_t i = 0; i < u.size(); i++) {
        for (size_t j = 0; j < u[i].size(); j++) {
            // fma[Fused Multiply-Add](x * y) + z
            // without fma CPU do 2 separate operation instead of one.
            if constexpr (std::is_floating_point_v<K>)
                result.data[j] = std::fma(coefs[i], u[i].data[j], result.data[j]);
            else
                result.data[j] += coefs[i] * u[i].data[j];
        }
    }
    return (result);
}


// * * * MATRIX * * *//
template <typename K>
Matrix<K> linear_combination(const std::vector<Matrix<K>>& u, const std::vector<K>& coefs)
{
    if (u.empty() || coefs.empty())
        throw std::invalid_argument("Error : one or both entry are empty");
    
    if (u.size() != coefs.size())
        throw std::length_error("Error : u element count (" + std::to_string(u.size())
            + ") must match coefs element count (" + std::to_string(coefs.size()) + ")");
    
    size_t len = u[0].size();
    if (len == 0)
        throw std::invalid_argument("Error : size is 0");
    for (size_t i = 1; i < u.size(); i++) {
        if (len != u[i].size()) {
            throw std::length_error("Error : all row in u must have the same size");
        }
    }

    size_t rows = u[0].rows;
    size_t cols = u[0].cols;

    Matrix<K> result(rows, cols, K(0));

    for (size_t i = 0; i < u.size(); i++) {
        for (size_t r = 0; r < u[i].rows; r++) {
            for (size_t c = 0; c < u[i].cols; c++) {

                if constexpr (std::is_floating_point_v<K>)
                    result(r, c) = std::fma(coefs[i], u[i](r, c), result(r, c));
                else
                    result(r, c) += coefs[i] * u[i](r, c);
            }
        }
    }
    return (result);
}

void print_linear_combination_info(const std::vector<Vector<float>>& u, const std::vector<float>& c)
{
    size_t dimension = u[0].size();
    size_t vector_count = u.size();

    std::cout << std::fixed << std::setprecision(3);
    // display vectors
    std::cout << BIBLUE;
    for (size_t i = 0; i < vector_count; i++) {
        std::cout << "u[" << i << "] = ";
        for (size_t j = 0; j < dimension; j++) {
            std::cout << "|" << normalize_zero(u[i].data[j]) << "|";
            if (j == dimension - 1)
                std::cout << "\n";
            else
                std::cout << ", ";
        }
    }
    std::cout << RESET << "\n";

    // display coefs
    std::cout << BIYELLOW;
    for (size_t i = 0; i < vector_count; i++) {
        std::cout << "c[" << i << "] = " << normalize_zero(c[i]);
        if (i != vector_count - 1)
            std::cout << ", ";
    }

    std::cout << RESET << "\n\n";
    std::cout << BIGREEN;
    std::cout << "R = 2.f * u[0] + 7.f * u[1] + -1.f * u[2]\n\n" << RESET; 


    // display operations
    for (size_t j = 0; j < dimension; j++) {
        std::cout << BIWHITE << "r[" << j << "] = ";
        for (size_t i = 0; i < vector_count; i++) {
            if (i > 0) std::cout << " + ";
            std::cout << BIYELLOW << normalize_zero(c[i]) <<  RESET << " * ";
            std::cout << BIBLUE << " |" << normalize_zero(u[i].data[j]) << "|" << RESET;
        }
    std::cout << "\n";
    }
    std::cout << BIWHITE << "――――― \n" << RESET;
}