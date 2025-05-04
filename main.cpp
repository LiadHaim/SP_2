//liadi.haim@gmail.com

#include "SquareMat.hpp"
#include <iostream>

using namespace matrix;

int main() {
    std::cout << "=== SquareMat Demo ===\n\n";

    double vals1[] = { 1.0, 2.0,
                       3.0, 4.0 };
    double vals2[] = { 5.0, 6.0,
                       7.0, 8.0 };

    SquareMat m1(vals1, 2);
    SquareMat m2(vals2, 2);

    std::cout << "m1:\n" << m1 << "\n\n";
    std::cout << "m2:\n" << m2 << "\n\n";

    std::cout << "m1 + m2:\n"  << (m1 + m2) << "\n\n";
    std::cout << "m2 - m1:\n"  << (m2 - m1) << "\n\n";
    std::cout << "-m1:\n"     << (-m1)    << "\n\n";
    std::cout << "m1 * m2:\n"  << (m1 * m2) << "\n\n";
    std::cout << "m1 * 2:\n"   << (m1 * 2.0) << "\n\n";
    std::cout << "2 * m1:\n"   << (2.0 * m1) << "\n\n";

    std::cout << "m1 % m2:\n"  << (m1 % m2) << "\n\n";
    std::cout << "m1 % 3:\n"   << (m1 % 3)  << "\n\n";
    std::cout << "m1 / 2:\n"   << (m1 / 2.0) << "\n\n";
    std::cout << "m1 ^ 2:\n"   << (m1 ^ 2)   << "\n\n";

    {
        SquareMat t = m1;
        std::cout << "++t:\n" << ++t << "\n\n";
    }
    {
        SquareMat t = m1;
        std::cout << "t++:\n" << (t++) << "\nthen t is:\n" << t << "\n\n";
    }
    {
        SquareMat t = m1;
        std::cout << "--t:\n" << --t << "\n\n";
    }
    {
        SquareMat t = m1;
        std::cout << "t--:\n" << (t--) << "\nthen t is:\n" << t << "\n\n";
    }

    std::cout << "~m1:\n" << (~m1) << "\n\n";

    std::cout << "m1[0][1] = " << m1[0][1] << "\n";
    SquareMat t = m1;
    t[0][1] = 9.9;
    std::cout << "after t[0][1]=9.9:\n" << t << "\n\n";

    std::cout << std::boolalpha
              << "m1 == m2? " << (m1 == m2) << "\n"
              << "m1 != m2? " << (m1 != m2) << "\n"
              << "m1 <  m2? " << (m1 <  m2) << "\n"
              << "m1 >  m2? " << (m1 >  m2) << "\n\n";

    std::cout << "det(m1) = " << !m1 << "\n\n";

    SquareMat u = m1;
    u += m2;
    std::cout << "u = m1; u += m2:\n" << u << "\n\n";

    SquareMat v = m1;
    v *= 3.0;
    std::cout << "v = m1; v *= 3.0:\n" << v << "\n\n";

    return 0;
}