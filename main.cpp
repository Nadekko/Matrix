#include "include/vectors.hpp"
#include "include/martices.hpp"

//tpp
#include "srcs/cosine.tpp"
#include "srcs/cross_product.tpp"
#include "srcs/linear_combination.tpp"
#include "srcs/linear_interpolation.tpp"

int main()
{
    std::cout << BIWHITE << "test 1: /* * * EMPTY VECTORS AND MATRICES * * */\n\n" << RESET;
    try {
        Vector<float> u{};
    }
    catch (std::length_error& e) {
        std::cerr << RED << e.what() << RESET << "\n";
    }
    try {
        Matrix<float> u{{}, {}};
    }
    catch (std::length_error& e) {
        std::cerr << RED << e.what() << RESET << "\n";
    }
    std::cout << BIWHITE << "\ntest 2: /* * * MATRICES NOT RECTANGULAR * * */\n\n" << RESET;
    try {
        Matrix<float> u{{1., 5., 3.}, {0., 5.}};
    }
    catch (std::length_error& e ) {
        std::cerr << RED << e.what() << RESET << "\n";
    }
    std::cout << BIWHITE << "\ntest 3: / * * * TEST EX00 * * */\n\n" << RESET;
    std::cout << BIRED << "/* * * testing error on number of elements and shape* * */\n\n" << RESET;
    try {
        Vector<float> u{0., 0., 0.};
        Vector<float> v{0., 0.};

        u.add(v);
        u.print();
    }
    catch (std::length_error& e) {
        std::cerr << RED << e.what() << RESET << "\n";
    }
    try {
        Matrix<float> u{{0., 0., 0.}, {0., 0., 0.}};
        Matrix<float> v{{0., 0.}, {0., 0.}, {0., 0.}};

        u.add(v);
    }
    catch (std::length_error& e) {
        std::cerr << RED << e.what() << RESET << "\n";
    }
    {
        //for Vectors//
        std::cout << BIWHITE << "\n/* * * VECTOR * * */" << RESET << "\n";
        Vector<float> u{2., 3.};
        Vector<float> v{5., 7.};

        Vector<float> i{4., -8.};
        Vector<float> j{-3., 1.};

        Vector<float> k{7., 4., 3.};
        {
            std::cout << "calling add method\n";
            u.add(v);
            i.add(j);
            u.print();
            i.print();
        }
        {
            std::cout << "calling sub method\n";
            u.sub(v);
            u.print();
            i.sub(j);
            i.print();
        }
        {
            std::cout << "calling scl method\n";
            u.scl(-4.);
            u.print();
            k.scl(2.);
            k.print();
        }
    }
    {
        //for Matrices
        std::cout << BIWHITE << "\n/* * * MATRICES * * */" << RESET << "\n";
        Matrix<float> u{{2., 3.}, {0., -5.}};
        Matrix<float> v{{5., 7.}, {9., 3.}};

        Matrix<float> i{{4., -8.}};
        Matrix<float> j{{-3., 1.}};

        Matrix<float> k{{7., 4., 3.}};

        {
            std::cout << "calling add method\n";
            u.add(v);
            i.add(j);
            u.print();
            i.print();
        }
        {
            std::cout << "calling sub method\n";
            u.sub(v);
            u.print();
            i.sub(j);
            i.print();
        }
        {
            std::cout << "calling scl method\n";
            u.scl(-4.);
            u.print();
            k.scl(2.);
            k.print();
        }
    }
    std::cout << BIWHITE << "\ntest 3: / * * * TEST EX01 (linear combination) * * */\n\n" << RESET;
    std::cout << BIRED << "/* * * testing error on number of elements* * */\n\n" << RESET;
    { 
        // u got wrong size
        std::vector<Vector<float>> u = {
            Vector<float>({1.2, 3., 6.}),
            Vector<float>({0.3, 4., 2.}),
            Vector<float>({1., 5.2, 0., 4}),
        };     
        std::vector<float> c = {12., -6., 0.5};
        std::cout << BIWHITE << "test 1: u got wrong size\n" << RESET;
        try {
            Vector<float> result = linear_combination(u, c);
            std::cout << NGREEN << "/* * * Print result * * */\n";
            std::cout << GREEN;
            result.print();
            std::cout << RESET;
        }
        catch(std::length_error& e) {
            std::cerr << RED << e.what() << RESET << std::endl;
        }
    }
    std::cout << "\n";
    { // coefs and u not the same size
        std::vector<Vector<float>> u = {
            Vector<float>({1.2, 3., 6.}),
            Vector<float>({0.3, 4., 2.}),
            Vector<float>({1., 5.2, 0.}),
        };
        std::vector<float> c = {12., -6., 0.5, 10.};
        std::cout << BIWHITE << "test 2: coefs.size() > u[0].size()\n" << RESET;
        try {
            Vector<float> result = linear_combination(u, c);
            std::cout << NGREEN << "/* * * Print result * * */\n";
            std::cout << GREEN;
            result.print();
            std::cout << RESET;
        }
        catch(std::length_error& e) {
            std::cerr << RED << e.what() << RESET << std::endl;
        }
    }
    std::cout << "\n";
    {
        std::vector<Vector<float>> u = {
            Vector<float>({1.0002, 34444., 777776.}),
            Vector<float>({0.3, 4., 2.}),
            Vector<float>({1., 5.2, 0.}),
        };
        std::vector<float> c = {12., -6., 0.5};
        std::cout << BIWHITE << "test 3:\n" << RESET;
        try {
            print_linear_combination_info(u, c);
            Vector<float> result = linear_combination(u, c);
            std::cout << NGREEN << "\n/* * * Print result * * */\n\n";
            std::cout << GREEN;
            result.print();
            std::cout << RESET;
        }
        catch(std::length_error& e) {
            std::cerr << RED << e.what() << RESET << std::endl;
        }
    }
    std::cout << "\n";
    { // subject
        std::vector<Vector<float>> u = {
            Vector<float>({1., 0., 0.}),
            Vector<float>({0., 1., 0.}),
            Vector<float>({0., 0., 1.}),
        };
        std::cout << BIWHITE << "test 4:\n" << RESET;


        std::vector<float> c1 = {1., 2., 3.};
        std::vector<float> c2 = {0., 10., -100.};

        print_linear_combination_info(u, c2);
        try {
            Vector<float> r1 = linear_combination(u, c1);
            print_linear_combination_info(u, c1);
            std::cout << NGREEN << "\n/* * * Print result * * */\n\n";
            std::cout << GREEN;
            r1.print();
            std::cout << RESET << "\n\n";
            std::cout << BIWHITE << "test 5:\n" << RESET;
    
            Vector<float> r2 = linear_combination(u, c2);
            print_linear_combination_info(u, c2);
            std::cout << NGREEN << "\n/* * * Print result * * */\n\n";
            std::cout << GREEN;
            r2.print();
            std::cout << RESET;
        }
        catch(std::length_error& e) {
            std::cerr << RED << e.what() << RESET << std::endl;
        }
    }
    {
        Vector<float> u{1., 2., 3.};
        Vector<float> v{4., 5., 6.};

        float cosine = angle_cos(u, v);
        std::cout << "cosine = " << cosine << "\n";
    }
    return (0);
}
