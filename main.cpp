#include "include/vectors.hpp"
#include "include/martices.hpp"

//tpp
#include "srcs/cosine.tpp"
#include "srcs/cross_product.tpp"
#include "srcs/linear_combination.tpp"
#include "srcs/linera_interpolation.tpp"

#include <unordered_map>
#include <functional>

static void test_ex00() {
    
    std::cout << BIWHITE << "/* * * TEST EX00 (add, subtract, scale) * * */\n\n" << RESET;

    //test 1
    try {
        Vector<float> u{2.f, 3.f};
        Vector<float> v{5.f, 7.f};
        u.add(v);
        u.print();
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << RESET;
    }
    std::cout << "\n";
    //test 2
    try {
        Vector<float> u{2.f, 3.f};
        Vector<float> v{5.f, 7.f};
        u.sub(v);
        u.print();
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << RESET;
    }
    std::cout << "\n";
    //test 3
    try {
        Vector<float> u{2.f, 3.f};
        u.scl(2.f);
        u.print();
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << RESET;
    }
    std::cout << "\n";
    //test 4
    try {
        Vector<float> u{2.f, 3.f};
        Vector<float> v{5.f, 7.f, 2.3f};
        u.add(v);
        u.print();
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
}

static void test_ex01() {
    
    std::cout << BIWHITE << "/* * * TEST EX01 (linear combination) * * */\n\n" << RESET;

    //test 1
    try {
        std::vector<Vector<float>> v1 = {
            Vector<float> {2.f, 3.f, 4.f},
            Vector<float> {6.f, -7.f, 8.f},
            Vector<float> {5.f, 0.f, -3.f},
        };
        std::vector<float> c1 {2.f, 7.f, -1.f};

        print_linear_combination_info(v1, c1);
        std::cout << "\n";
        Vector<float> e1 = linear_combination(v1, c1);

        e1.print();
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
    std::cout << "\n";
    //test 2
    try {
        std::vector<Vector<float>> v2 = {
            Vector<float> {1.f, 0.f,  0.f},
            Vector<float> {0.f, 1.f,  0.f},
            Vector<float> {0.f, 0.f,  1.f},
        };
        std::vector<float> c2{1.f, 2.f, 3.f};
        std::vector<float> c3{0.f, 10.f, -100.f};

        Vector<float> e2 = linear_combination(v2, c2);
        Vector<float> e3 = linear_combination(v2, c3);

        e2.print();
        std::cout << "\n";
        e3.print();

    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
    std::cout << "\n";
    //test 3
    try {
        std::vector<Vector<float>> v3 = {
            Vector<float> {1.f, 0.f,  0.f},
            Vector<float> {0.f, 1.f,  0.f},
            Vector<float> {0.f, 0.f,  1.f},
        };
        std::vector<float> c4{1.f, 2.f, 3.f, 4.5f};

        Vector<float> e4 = linear_combination(v3, c4);

        e4.print();
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
}

static void test_ex02() {
    
    std::cout << BIWHITE << "/* * * TEST EX02 (lerp) * * */\n\n" << RESET;

    //test 1
    try {
        float r1 = lerp(0.f, 1.f, 0.f);

        std::cout << r1 << "\n";
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
    try {
        float r2 = lerp(0.f, 1.f, 1.f);

        std::cout << r2 << "\n";
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
    try {
        float r3 = lerp(0.f, 1.f, 0.f);

        std::cout << r3 << "\n";
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
    std::cout << "\n";
    //test 2
    try {
        Vector<float> v1{2.f, 1.f};
        Vector<float> v2{4.f, 2.f};

        Vector<float> r1 = lerp(v1, v2, 0.3f);

        r1.print();
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
    std::cout << "\n";
    //test 3
    try {
        Matrix<float> m1{{2.f, 1.f}, {3.f, 4.f}};
        Matrix<float> m2{{20.f, 10.f}, {30.f, 40.f}};

        Matrix<float> m3 = lerp(m1, m2, 0.5f);

        m3.print();
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
}

static void test_ex03() {

    std::cout << BIWHITE << "/* * * TEST EX03 (dot product) * * */\n\n" << RESET;

    //test 1
    try {
        Vector<float> u{0.f, 0.f};
        Vector<float> v{1.f, 1.f};

        std::cout << "u = \n";
        u.print();
        std::cout << "\n";
        std::cout << "v = \n";
        v.print();
        std::cout << "\n";
        std::cout << u.dot(v) << "\n";
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
    std::cout << "――――― \n";
    //test 2
    try {
        Vector<float> u{1.f, 1.f};
        Vector<float> v{1.f, 1.f};

        std::cout << "u = \n";
        u.print();
        std::cout << "\n";
        std::cout << "v = \n";
        v.print();
        std::cout << "\n";
        std::cout << u.dot(v) << "\n";
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
    std::cout << "――――― \n";
    //test 3
    try {
        Vector<float> u{-1.f, 6.f};
        Vector<float> v{3.f, 2.f};

        std::cout << "u = \n";
        u.print();
        std::cout << "\n";
        std::cout << "v = \n";
        v.print();
        std::cout << "\n";
        std::cout << u.dot(v) << "\n";
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
    std::cout << "――――― \n";
    //test 4
    try {
        Vector<float> u{0.f, 0.f};
        Vector<float> v{1.f, 1.f, 2.f};

        std::cout << "u = \n";
        u.print();
        std::cout << "\n";
        std::cout << "v = \n";
        v.print();
        std::cout << "\n";
        std::cout << u.dot(v) << "\n";
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
}

static void test_ex04() {
    
    std::cout << BIWHITE << "/* * * TEST EX04 (norms l1, l2, inf) * * */\n\n" << RESET;

    std::cout << "norms for vectors\n\n";
    //test 1
    Vector<float> u1{0.f, 0.f, 0.f};

    std::cout << "||u||1 = " << u1.norm_l1() << "\n";
    std::cout << "||u||  = " "√" << u1.pythagore_impl() << " ≈ " << u1.norm_l2() << "\n";
    std::cout << "||u||∞ = " << u1.norm_inf() << "\n";

    std::cout << "――――― \n";
    //test 2
    Vector<float> u2{1.f, 2.f, 3.f};

    std::cout << "||u||1 = " << u2.norm_l1() << "\n";
    std::cout << "||u||  = " "√" << u2.pythagore_impl() << " ≈ " << u2.norm_l2() << "\n";
    std::cout << "||u||∞ = " << u2.norm_inf() << "\n";

    std::cout << "――――― \n";
    //test 3
    Vector<float> u3{-1.f, -2.f};

    std::cout << "||u||1 = " << u3.norm_l1() << "\n";
    std::cout << "||u||  = " "√" << u3.pythagore_impl() << " ≈ " << u3.norm_l2() << "\n";
    std::cout << "||u||∞ = " << u3.norm_inf() << "\n";

    std::cout << "\nnorms for matrices\n\n";
    //test 4
    Matrix<float> m1{{0.f, 0.f, 0.f}, {1.f, 1.f, 1.f}};

    std::cout << "||u||1 = " << m1.norm_l1() << "\n";
    std::cout << "||u||  = " "√" << m1.pythagore_impl() << " ≈ " << m1.norm_F() << "\n";
    std::cout << "||u||∞ = " << m1.norm_inf() << "\n";

    std::cout << "――――― \n";
    //test 5
    Matrix<float> m2{{-4.f, 5.f, 6.f}, {3.f, -1.f, 1.f}};

    std::cout << "||u||1 = " << m2.norm_l1() << "\n";
    std::cout << "||u||  = " "√" << m2.pythagore_impl() << " ≈ " << m2.norm_F() << "\n";
    std::cout << "||u||∞ = " << m2.norm_inf() << "\n";

}

static void test_ex05() {
    
    std::cout << BIWHITE << "/* * * TEST EX05 (cosine) * * */\n\n" << RESET;

    //test 1
    try {
        Vector<float> u1{0.f, 0.f, 0.f};
        Vector<float> u2{1.f, 2.f, 3.f};

        float a_cos = angle_cos(u1, u2);
        std::cout << "cos(θ) = " << a_cos << "\n";
    }
    catch (std::domain_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;  
    }
    std::cout << "――――― \n";
    //test 2
    try {
        Vector<float> u1{2.f, 4.f, -2.f};
        Vector<float> u2{5.f, 1.f};

        float a_cos = angle_cos(u1, u2);
        std::cout << "cos(θ) = " << a_cos << "\n";
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
    std::cout << "――――― \n";
    //test 3
    try {
        Vector<float> u1{1.f, 0.f};
        Vector<float> u2{1.f, 0.f};

        float a_cos = angle_cos(u1, u2);
        std::cout << "cos(θ) = " << a_cos << "\n";
    }
    catch (std::domain_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;  
    }
    std::cout << "――――― \n";
    //test 4
    try {
        Vector<float> u1{1.f, 0.f};
        Vector<float> u2{0.f, 1.f};

        float a_cos = angle_cos(u1, u2);
        std::cout << "cos(θ) = " << a_cos << "\n";
    }
    catch (std::domain_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;  
    }
    std::cout << "――――― \n";
    //test 5
    try {
        Vector<float> u1{-1.f, 1.f};
        Vector<float> u2{1.f, -1.f};

        float a_cos = angle_cos(u1, u2);
        std::cout << "cos(θ) = " << a_cos << "\n";
    }
    catch (std::domain_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;  
    }
    std::cout << "――――― \n";
    //test 6
    try {
        Vector<float> u1{2.f, 1.f};
        Vector<float> u2{4.f, 2.f};

        float a_cos = angle_cos(u1, u2);
        std::cout << "cos(θ) = " << a_cos <<  "\n";
    }
    catch (std::domain_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;  
    }
    std::cout << "――――― \n";
    //test 7
    try {
        Vector<float> u1{1.f, 2.f, 3.f};
        Vector<float> u2{4.f, 5.f, 6.f};

        float a_cos = angle_cos(u1, u2);
        std::cout << "cos(θ) = " << a_cos << "\n";
    }
    catch (std::domain_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;  
    }
}

void test_ex06() {

    std::cout << BIWHITE << "/* * * TEST EX06 (cross product) * * */\n\n" << RESET;

    //test 1
    try {
        Vector<float> u{2.f, 3.f};
        Vector<float> v{-6.f, 5.f, 1.f};

        Vector<float> cp = cross_product(u, v);

        cp.print();
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET;
    }
    std::cout << "――――― \n";
    //test 2
    try {
        Vector<float> u{0.f, 0.f, 1.f};
        Vector<float> v{1.f, 0.f, 0.f};

        Vector<float> cp = cross_product(u, v);

        cp.print();
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET;
    }
    std::cout << "――――― \n";
    //test 3
    try {
        Vector<float> u{1.f, 2.f, 3.f};
        Vector<float> v{4.f, 5.f, 6.f};

        Vector<float> cp = cross_product(u, v);

        cp.print();
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET;
    }
    std::cout << "――――― \n";
    //test 4
    try {
        Vector<float> u{4.f, 2.f, -3.f};
        Vector<float> v{-2.f, -5.f, 16.f};

        Vector<float> cp = cross_product(u, v);

        cp.print();
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET;
    }
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./matrix <exercise>\n"
            << "Availeble: ex00, ex01, ..., ex05\n";
        return (1);
    }

    const std::unordered_map<std::string, std::function<void()>> exercises = {
        {"ex00", test_ex00},
        {"ex01", test_ex01},
        {"ex02", test_ex02},
        {"ex03", test_ex03},
        {"ex04", test_ex04},
        {"ex05", test_ex05},
        {"ex06", test_ex06},
    };

    const std::string key(av[1]);
    auto it = exercises.find(key);
    if (it == exercises.end()) {
        std::cerr << "Unknown exercise: " << key << "\n";
        return (1);
    }

    it->second();
    return (0);
}
