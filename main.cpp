#include "include/vectors.hpp"
#include "include/matrices.hpp"

//tpp
#include "srcs/cosine.tpp"
#include "srcs/cross_product.tpp"
#include "srcs/linear_combination.tpp"
#include "srcs/linear_interpolation.tpp"

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
    std::cout << BIWHITE << "――――― \n" << RESET;
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
    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 3
    try {
        Vector<float> u{2.f, 3.f};
        u.scl(2.f);
        u.print();
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << RESET;
    }
    std::cout << BIWHITE << "――――― \n" << RESET;
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
    std::cout << BIWHITE << "――――― \n" << RESET;
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
        std::cout << BIWHITE << "――――― \n" << RESET;
        e3.print();

    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
    std::cout << BIWHITE << "――――― \n" << RESET;
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
    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 2
    try {
        float r2 = lerp(0.f, 1.f, 1.f);

        std::cout << r2 << "\n";
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 3
    try {
        float r3 = lerp(0.f, 1.f, 0.f);

        std::cout << r3 << "\n";
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 4
    try {
        Vector<float> v1{2.f, 1.f};
        Vector<float> v2{4.f, 2.f};

        Vector<float> r1 = lerp(v1, v2, 0.3f);

        r1.print();
    }
    catch (std::length_error &e) {
        std::cerr << RED << e.what() << "\n" << RESET;
    }
    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 5
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
    std::cout << BIWHITE << "――――― \n" << RESET;
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
    std::cout << BIWHITE << "――――― \n" << RESET;
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
    std::cout << BIWHITE << "――――― \n" << RESET;
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

    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 2
    Vector<float> u2{1.f, 2.f, 3.f};

    std::cout << "||u||1 = " << u2.norm_l1() << "\n";
    std::cout << "||u||  = " "√" << u2.pythagore_impl() << " ≈ " << u2.norm_l2() << "\n";
    std::cout << "||u||∞ = " << u2.norm_inf() << "\n";

    std::cout << BIWHITE << "――――― \n" << RESET;
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

    std::cout << BIWHITE << "――――― \n" << RESET;
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
    std::cout << BIWHITE << "――――― \n" << RESET;
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
    std::cout << BIWHITE << "――――― \n" << RESET;
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
    std::cout << BIWHITE << "――――― \n" << RESET;
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
    std::cout << BIWHITE << "――――― \n" << RESET;
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
    std::cout << BIWHITE << "――――― \n" << RESET;
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
    std::cout << BIWHITE << "――――― \n" << RESET;
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

static void test_ex06() {

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
    std::cout << BIWHITE << "――――― \n" << RESET;
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
    std::cout << BIWHITE << "――――― \n" << RESET;
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
    std::cout << BIWHITE << "――――― \n" << RESET;
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

static void test_ex07() {

    std::cout << BIWHITE << "/* * * TEST EX07 (linear map, matrix multiplication) * * */\n\n" << RESET;

    //test 1
    try {
        Matrix<float> u {{4.0f, 2.2f, 6.0f}, {1.0f, 3.2f, -4.0f}};
        Vector<float> v {0.0f, 5.1f};

        Vector<float> result = u.mul_vec(v);
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET; 
    }
    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 2
    try {
        Matrix<float> u {{4.0f, 2.2f, 6.0f}, {1.0f, 3.2f, -4.0f}};
        Vector<float> v {0.0f, -5.1f, 2.0f};

        Vector<float> result = u.mul_vec(v);

        result.print();
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET; 
    }
    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 3
    try {
        Matrix<float> u {{4.0f, 2.2f, 6.0f}, {1.0f, 3.2f, -4.0f}};
        Matrix<float> v {{0.0f, -5.1f, 2.0f}, {4.0f, -9.0f, 1.1f}, {4.5f, 2.0f, -6.0f}};

        Matrix<float> result = u.mul_mat(v);

        result.print();
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET; 
    }
    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 4
    try {
        Matrix<float> u {{4.0f, 2.2f, 6.0f}, {1.0f, 3.2f, -4.0f}};
        Matrix<float> v {{0.0f, -5.1f}, {4.0f, -9.0f}, {4.5f, 2.0f}};

        Matrix<float> result = u.mul_mat(v);

        result.print();
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET; 
    }
    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 5
    try {
        Matrix<float> u {{4.0f, 2.0f, 6.0f}, {1.0f, 3.0f, -4.0f}, {0.0f, -7.0f, 3.0f}};
        Matrix<float> v {{0.0f, -5.0f, 2.0f}, {4.0f, 8.0f, 1.0f}, {2.0f, 5.0f, 6.0f}, {0.0f, 2.0, -1.0f}};

        Matrix<float> result = u.mul_mat(v);

        result.print();
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET; 
    }
    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 6
    try {
        Matrix<float> u {{4.0f, 2.0f, 6.0f}, {1.0f, 3.0f, -4.0f}, {0.0f, -7.0f, 3.0f}};
        Matrix<float> v {{0.0f, -5.0f}, {4.0f, 8.0f}, {2.0f, 5.0f}};

        Matrix<float> result = u.mul_mat(v);

        result.print();
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET; 
    }
}

static void test_ex08() {

    std::cout << BIWHITE << "/* * * TEST EX08 (trace) * * */\n\n" << RESET;

    //test 1
    try {
        Matrix<double> u {{1., 2., 3.}, {4., 5., 6.}};

        double tr = u.trace();
        std::cout << "Tr(" << tr << ")\n";

    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET;
    }
    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 2
    try {
        Matrix<float> u {{1.0f, 0.0f}, {0.0f, 1.0f}};

        float tr = u.trace();
        std::cout << "Tr(" << tr << ")\n";
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET;
    }
    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 3
    try {
        Matrix<double> u {{2., -5., 0.}, {4., 3., 7.}, {-2, 3, 4}};

        double tr = u.trace();
        std::cout << "Tr(" << tr << ")\n";
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET;
    }
    //test 4
    std::cout << BIWHITE << "――――― \n" << RESET;
    try {
        Matrix<double> u {{-2., -8., 4.}, {1., -23., 7.}, {0., 6., 4.}};

        double tr = u.trace();
        std::cout << "Tr(" << tr << ")\n";
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET;
    }
}

static void test_ex09() {

    std::cout << BIWHITE << "/* * * TEST EX09 (transposition) * * */\n\n" << RESET;

    Matrix<double> A {{4., -7.}, {5., 3.}};
    Matrix<double> B {{5., -1.}, {2., 7.}, {-3., 4.}};
    Matrix<float> C  {{1.f, -7.f, 3.f, -2.f}};

    std::cout << BICYAN << "print matrices before transpose\n\n" << RESET;

    std::cout << "A\n";
    A.print();
    std::cout << BIWHITE << "――――― \n" << RESET;
    std::cout << "B\n";
    B.print();
    std::cout << BIWHITE << "――――― \n" << RESET;
    std::cout << "C\n";
    C.print();

    std::cout << BICYAN << "\nprint matrices after transpose\n" << RESET;
    
    Matrix<double> At = A.transpose();
    Matrix<double> Bt = B.transpose();
    Matrix<float> Ct = C.transpose();

    std::cout << "At\n";
    At.print();
    std::cout << BIWHITE << "――――― \n" << RESET;
    std::cout << "Bt\n";
    Bt.print();
    std::cout << BIWHITE << "――――― \n" << RESET;
    std::cout << "Ct\n";
    Ct.print();
    std::cout << BIWHITE << "――――― \n" << RESET;

}

static void test_ex10() {

    std::cout << BICYAN << "testing negative zero\n";
    std::cout << "print zero -> " << 0.0 << "\n";
    std::cout << "print neg zero -> " << -0.0 << "\n";
    std::cout << "print 1.0/0.0 -> " << (1.0/0.0) << "\n";
    std::cout << "print 1.0/-0.0 -> " << (1.0/-0.0) << "\n";
    std::cout << "print 0.0/-1.0 -> " << (0.0/-1.0) << "\n";
    std::cout << "does -0.0 == 0.0 (reutrn 1 if true) -> " << (0.0 == -0.0) << "\n";
    std::cout << "other test == " << "\n";
    std::cout << (-0 - (2 * -0)) << "\n";
    std::cout << (0.0 - (3.0 * 0.0)) << "\n";
    std::cout << (0.0 - (-0.0 * 0.0)) << "\n";
    std::cout << (0.0 - 0.0) << "\n";
    std::cout << (-0.0 - -0.0) << "\n";
    std::cout << BIWHITE << "/* * * TEST EX10 (row echelon form REF/RREF) * * */\n\n" << RESET;
    //test 1
    Matrix<double> A {{0.001, 1., 4.}, {0., 4., 8.}, {0., 5., 4.}};
    std::cout << BIWHITE << "Print Matrix\n" << RESET;
    A.print();

    Matrix<double> identityA = A.reduce_row_echelon();

    std::cout << BIWHITE << "Print Reduce Row Echelon Form\n" << RESET;
    identityA.print();

    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 2
    Matrix<float> B {{8.f, 5.f, -2.f, 4.f, 28.f}, {4.f, 2.5f, 20.f, 4.f, -4.f}, {8.f, 5.f, 1.f, 4.f, 17.f}};
    std::cout << BIWHITE << "Print Matrix\n" << RESET;
    B.print();

    Matrix<float> identityB = B.reduce_row_echelon();

    std::cout << BIWHITE << "Print Reduce Row Echelon Form\n" << RESET;
    identityB.print();

    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 3
    Matrix<double> C {{1., 0., 0.}, {0., 1., 0.}, {0., 0., 1.}};
    std::cout << BIWHITE << "Print Matrix\n" << RESET;
    C.print();

    Matrix<double> identityC = C.reduce_row_echelon();

    std::cout << BIWHITE << "Print Reduce Row Echelon Form\n" << RESET;
    identityC.print();

    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 4
    Matrix<double> D {{1., 2.}, {3., 4.}};
    std::cout << BIWHITE << "Print Matrix\n" << RESET;
    D.print();

    Matrix<double> identityD = D.reduce_row_echelon();

    std::cout << BIWHITE << "Print Reduce Row Echelon Form\n" << RESET;
    identityD.print();

    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 5
    Matrix<double> E {{1., 2.}, {2., 4.}};
    std::cout << BIWHITE << "Print Matrix\n" << RESET;
    E.print();

    Matrix<double> identityE = E.reduce_row_echelon();

    std::cout << BIWHITE << "Print Reduce Row Echelon Form\n" << RESET;
    identityE.print();

    std::cout << BIWHITE << "――――― \n" << RESET;
    //test 6
    Matrix<double> F {{0., 2., 3.}, {0., 7., 0.}, {0., 5., 4.}};
    std::cout << BIWHITE << "Print Matrix\n" << RESET;
    F.print();

    Matrix<double> identityF = F.reduce_row_echelon();

    std::cout << BIWHITE << "Print Reduce Row Echelon Form\n" << RESET;
    identityF.print();

}

static void test_ex11 () {

    std::cout << BIWHITE << "/* * * TEST EX11 (determinant) * * */\n\n" << RESET;

    //test 1
    try {
        Matrix<float> A {{4.3}, {1.0}};

        float det = A.determinant();
        std::cout << "det(" << det << ")\n";
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET; 
    }
    //test 2
    try {
        Matrix<float> B {{4.3}};

        float det = B.determinant();
        std::cout << "det(" << det << ")\n";
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET; 
    }
    //test 3
    try {
        Matrix<double> A {{1.0, -1.}, {-1., 1.}};

        double det = A.determinant();
        std::cout << "det(" << det << ")\n";
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET; 
    }
    //test 4
    try {
        Matrix<double> A {{2., 0., 0.}, {0., 2., 0.}, {0., 0., 2.}};

        double det = A.determinant();
        std::cout << "det(" << det << ")\n";
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET; 
    }
    //test 5
    try {
        Matrix<double> A {{8., 5., -2.}, {4., 7., 20.}, {7., 6., 1.}};

        double det = A.determinant();
        std::cout << "det(" << det << ")\n";
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET; 
    }
    //test 6
    try {
        Matrix<double> A {{8., 5., -2., 4}, {4., 2.5, 20., 4.}, {8., 5., 1., 4.}, {28., -4., 17., 1.}};

        double det = A.determinant();
        std::cout << "det(" << det << ")\n";
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET; 
    }
    //test 7
    try {
        Matrix<double> A {{8., 5., -2., 4, 7}, {4., 2.5, 20., 4., 0}, {8., 5., 1., 4., 4}, {28., -4., 17., 1., 18}, {4., 2., 1.3, 7., 78.}};

        double det = A.determinant();
        std::cout << "det(" << det << ")\n";
    }
    catch (std::length_error &e) {
        std::cout << RED << e.what() << "\n" << RESET; 
    }
}

static void test_ex12() {
    std::cout << BIWHITE << "/* * * TEST EX12 (inverse matrix) * * */\n\n" << RESET;

    //test 1
    try {
        Matrix<double> A{{1., 2.}, {4., 2.}, {3., 8.}};

        A.inverse();
        A.print();
    }
    catch (std::invalid_argument &e) {
        std::cout << RED << e.what() << RESET << "\n";
    }
    //test 2
    try {
        Matrix<double> A{{0., 2.}, {0., 0.}};

        A.inverse();
        A.print();
    }
    catch (std::domain_error &e) {
        std::cout << RED << e.what() << RESET << "\n";
    }
    //test 3
    try {
        Matrix<double> A{{1., 0., 0.}, {0., 1., 0.}, {0., 0., 1.}};

        A.inverse();
        A.print();
    }
    catch (std::invalid_argument &e) {
        std::cout << RED << e.what() << RESET << "\n";
    }
    //test 4
    try {
        Matrix<double> A{{2., 0., 0.}, {0., 2., 0.}, {0., 0., 2.}};

        A.inverse();
        A.print();
    }
    catch (std::invalid_argument &e) {
        std::cout << RED << e.what() << RESET << "\n";
    }
    //test 5
    try {
        Matrix<double> A {{8., 5., -2}, {4., 7., 20.}, {7., 6., 1.}};

        Matrix<double> B = A.inverse();
        B.print();
    }
    catch (std::invalid_argument &e) {
        std::cout << RED << e.what() << RESET << "\n";
    }
}

static void test_ex13() {
    std::cout << BIWHITE << "/* * * TEST EX13 (rank) * * */\n\n" << RESET;

    Matrix<double> A{{1., 0., 0.}, {0., 1., 0.}, {0., 0., 1.}};

    size_t rank1 = A.rank();

    std::cout << rank1 << "\n";

    Matrix<double> B{{8., 5., -2}, {4., 7., 20.}, {21., 18., 7}};

    size_t rank2 = B.rank();

    std::cout << rank2 << "\n";

    Matrix<double> C{{1., 2., 0., 0.}, {2., 4., 0., 0.}, {-1., 2., 1., 1.}};

    size_t rank3 = C.rank();

    std::cout << rank3 << "\n";

}

static void all_test()
{
    test_ex00();
    test_ex01();
    test_ex02();
    test_ex03();
    test_ex04();
    test_ex05();
    test_ex06();
    test_ex07();
    test_ex08();
    test_ex09();
    test_ex10();
    test_ex11();
    test_ex12();
    test_ex13();
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./matrix <exercise>\n"
            << "Available: ex00, ex01, ..., ex05\n";
        return (1);
    }

    const std::unordered_map<std::string, std::function<void()>> exercises = {
        {"all_test", all_test},
        {"ex00", test_ex00},
        {"ex01", test_ex01},
        {"ex02", test_ex02},
        {"ex03", test_ex03},
        {"ex04", test_ex04},
        {"ex05", test_ex05},
        {"ex06", test_ex06},
        {"ex07", test_ex07},
        {"ex08", test_ex08},
        {"ex09", test_ex09},
        {"ex10", test_ex10},
        {"ex11", test_ex11},
        {"ex12", test_ex12},
        {"ex13", test_ex13},
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
