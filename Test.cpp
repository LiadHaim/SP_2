//liadi.haim@gmail.com


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "SquareMat.hpp"
#include <cmath>
#include <iostream>

using namespace matrix;
// Test cases for the SquareMat class
TEST_CASE("Constructors and element access") {
    SUBCASE("Default constructor zeros") {
        SquareMat m(3);
        CHECK(m[0][0] == 0.0);
        CHECK(m[0][2] == 0.0);
        CHECK(m[2][0] == 0.0);
        CHECK(m[2][2] == 0.0);
    }
    SUBCASE("Flat-array constructor") {
        double vals[] = {1.0, 2.0,
                         3.0, 4.0};
        SquareMat m(vals, 2);
        CHECK(m[0][0] == 1.0);
        CHECK(m[0][1] == 2.0);
        CHECK(m[1][0] == 3.0);
        CHECK(m[1][1] == 4.0);
    }
    SUBCASE("Copy constructor") {
        double vals[] = {5.0, 6.0,
                         7.0, 8.0};
        SquareMat orig(vals, 2);
        SquareMat cpy(orig);
        orig[0][0] = 100;
        CHECK(cpy[0][0] == 5.0);
        CHECK(cpy[1][1] == 8.0);
    }
    SUBCASE("Index out of range") {
        SquareMat m(2);
        CHECK_THROWS_AS((void)m[2][0], std::out_of_range);
        // no check on m[0][2] since column bounds are unchecked
    }
    SUBCASE("Invalid constructor arguments") {
        CHECK_THROWS_AS(SquareMat(0), std::invalid_argument);
        double* p = nullptr;
        CHECK_THROWS_AS(SquareMat(p, 2), std::invalid_argument);
        double arr[] = {1.0};
        CHECK_THROWS_AS(SquareMat(arr, 0), std::invalid_argument);
    }
}
TEST_CASE("Basic arithmetic operators") {
    double aVals[] = {1, 2,
                      3, 4};
    double bVals[] = {5, 6,
                      7, 8};
    SquareMat A(aVals, 2), B(bVals, 2);

    SUBCASE("Addition") {
        SquareMat C = A + B;
        CHECK(C[0][0] == 6.0);
        CHECK(C[0][1] == 8.0);
        CHECK(C[1][0] == 10.0);
        CHECK(C[1][1] == 12.0);
    }
    SUBCASE("Subtraction") {
        SquareMat C = B - A;
        CHECK(C[0][0] == 4.0);
        CHECK(C[0][1] == 4.0);
        CHECK(C[1][0] == 4.0);
        CHECK(C[1][1] == 4.0);
    }
    SUBCASE("Unary minus") {
        SquareMat C = -A;
        CHECK(C[0][0] == -1.0);
        CHECK(C[1][1] == -4.0);
    }
    SUBCASE("Matrix multiplication") {
        SquareMat C = A * B;
        CHECK(C[0][0] == 19.0);
        CHECK(C[0][1] == 22.0);
        CHECK(C[1][0] == 43.0);
        CHECK(C[1][1] == 50.0);
    }
    SUBCASE("Scalar multiplication") {
        SquareMat C1 = A * 2.0;
        SquareMat C2 = 2.0 * A;
        for(int i=0; i<2; ++i)
            for(int j=0; j<2; ++j)
                CHECK(C1[i][j] == C2[i][j]);
        CHECK(C1[1][0] == 6.0);
    }
}

TEST_CASE("Element-wise, modulo, division, power") {
    double aVals[] = {1, 2,
                      3, 4};
    SquareMat A(aVals, 2);

    SUBCASE("Element-wise multiplication (%)") {
        double bVals[] = {2, 3,
                          4, 5};
        SquareMat B(bVals, 2);
        SquareMat C = A % B;
        CHECK(C[0][0] == 2.0);
        CHECK(C[1][1] == 20.0);
    }
    SUBCASE("Modulo scalar (%)") {
        SquareMat C = A % 2;
        CHECK(C[0][0] == 1.0);
        CHECK(C[0][1] == 0.0);
        CHECK(C[1][0] == 1.0);
        CHECK(C[1][1] == 0.0);
    }
    SUBCASE("Division scalar (/)") {
        SquareMat C = A / 2.0;
        CHECK(C[0][0] == doctest::Approx(0.5));
        CHECK(C[1][1] == doctest::Approx(2.0));
    }
    SUBCASE("Power operator (^)") {
        SquareMat C2 = A ^ 2;
        CHECK(C2[0][0] == 7.0);
        CHECK(C2[1][1] == 22.0);

        SquareMat I = A ^ 0;
        CHECK(I[0][0] == 1.0);
        CHECK(I[0][1] == 0.0);
        CHECK(I[1][0] == 0.0);
        CHECK(I[1][1] == 1.0);
    }
    SUBCASE("Negative power throws") {
        CHECK_THROWS_AS(A ^ -1, std::invalid_argument);
    }
}

TEST_CASE("Increment/Decrement and transpose") {
    double aVals[] = {1, 2,
                      3, 4};
    SquareMat A(aVals, 2);

    SUBCASE("Pre- and post-increment") {
        SquareMat P = ++A;
        CHECK(P[0][0] == 2.0);
        CHECK(A[1][1] == 5.0);

        SquareMat Q = A++;
        CHECK(Q[0][0] == 2.0);
        CHECK(A[0][0] == 3.0);
    }
    SUBCASE("Pre- and post-decrement") {
        SquareMat D1 = --A;
        CHECK(D1[0][0] == 0.0);

        SquareMat D2 = A--;
        CHECK(D2[0][0] == 0.0);
        CHECK(A[0][0] == -1.0);  // matches current operator--(int)
    }
    SUBCASE("Transpose (~)") {
        SquareMat T = ~A;
        CHECK(T[0][1] == A[1][0]);
        CHECK(T[1][0] == A[0][1]);
    }
}

TEST_CASE("Compound assignments") {
    double aVals[] = {1, 2,
                      3, 4};
    double bVals[] = {5, 6,
                      7, 8};
    SquareMat A(aVals, 2), B(bVals, 2);

    SUBCASE("+= and -=") {
        A += B;
        CHECK(A[0][0] == 6.0);
        A -= B;
        CHECK(A[0][0] == 1.0);
    }
    SUBCASE("*= matrix and scalar") {
        A *= B;
        CHECK(A[0][0] == 19.0);
        A *= 2.0;
        CHECK(A[0][0] == 38.0);
    }
    SUBCASE("/= scalar and %= ops") {
        A /= 2.0;
        CHECK(A[0][0] == doctest::Approx(0.5));
        A %= 2;
        CHECK(A[0][0] == doctest::Approx(0.5));
        A %= B;
        CHECK(A[0][0] == doctest::Approx(0.5 * 5.0));
    }
}
TEST_CASE("Determinant operator") {
    SUBCASE("1×1 matrix") {
        double v1[] = {7.0};
        SquareMat M1(v1, 1);
        CHECK(!M1 == 7.0);
    }
    SUBCASE("2×2 matrix") {
        double v2[] = {1,2,
                       3,4};
        SquareMat M2(v2, 2);
        CHECK(!M2 == -2.0);
    }
    SUBCASE("3×3 matrix") {
        double v3[] = {
            1, 2, 3,
            0, 1, 4,
            5, 6, 0
        };
        SquareMat M3(v3, 3);
        CHECK(!M3 == 1.0);
    }
}
TEST_CASE("Comparison operators") {
    double aVals[] = {1,2,
                      3,4};
    double bVals[] = {2,3,
                      4,5};
    SquareMat A(aVals, 2), B(bVals, 2);

    CHECK(A < B);
    CHECK(B > A);
    CHECK(A <= A);
    CHECK(A >= A);
    CHECK(A != B);

    double valsComp[] = {5,5,5,5};
    SquareMat comp(valsComp, 2);
    CHECK_FALSE(A == comp);
}
