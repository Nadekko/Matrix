#include "../include/vectors.hpp"
#include "../include/martices.hpp"

// EX01
template<typename K>
Vector<K> linear_combination(const std::vector<Vector<K>>& u, const std::vector<K>& coefs)
{
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

void print_linear_combination_info(const std::vector<Vector<float>>& u, const std::vector<float>& c)
{
    size_t rows = u[0].size();
    size_t cols = u.size();

    std::cout << BIWHITE << "――――― \n";
    std::cout << std::fixed << std::setprecision(1);
    // display vectors
    std::cout << BIBLUE;
    for (size_t j = 0; j < rows; j++) {
        std::cout << "u[" << j << "] = ";  
        for (size_t i = 0; i < cols; i++) {
            std::cout << "|" << u[j].data[i] << "|";
            if (i == cols - 1)
                std::cout << "\n";
            else
                std::cout << ", ";
        }
    }
    std::cout << RESET << "\n";

    // display coefs
    std::cout << BIYELLOW;
    for (size_t i = 0; i < cols; i++) {
        std::cout << "c[" << i << "] = " << c[i];
        if (i != cols - 1)
            std::cout << ", ";
    }

    std::cout << RESET << "\n\n";

    // display operations
    for (size_t j = 0; j < rows; j++) {
        std::cout << BIWHITE << "r[" << j << "] = ";
        for (size_t i = 0; i < cols; i++) {
            if (i > 0) std::cout << " + ";
            std::cout << BIYELLOW << c[i] <<  RESET << " * ";
            std::cout << BIBLUE << " |" << u[i].data[j] << "|" << RESET;
        }
    std::cout << "\n";
    }
    std::cout << BIWHITE << "――――― \n" << RESET;
}

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