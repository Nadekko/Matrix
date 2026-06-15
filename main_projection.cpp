#include "include/matrices.hpp"

#include "srcs/projection.tpp"

#include <unordered_map>
#include <functional>

// gcc -std=c++17 -o projection main.cpp -lm
// ./projection > proj
// ./display

int main()
{

    // std::cout << BIWHITE << "/* * * TEST EX14 (projection) * * */\n\n" << RESET;

    float fov   = 60.0f * (3.14159265f / 180.0f); // 60° en radians
    float ratio = 16.0f / 9.0f;                    // fenêtre 16:9
    float near  = 0.1f;
    float far   = 100.0f;

    Matrix<float> P = projection<float>(fov, ratio, near, far);

    P.print_proj();
}