//liadi.haim@gmail.com


#ifndef SQUAREMAT_HPP
#define SQUAREMAT_HPP

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <cmath>

namespace matrix {
// A square matrix of doubles stored in row-major order.
class SquareMat {
private:
    size_t size;     // matrix dimension (n for n×n)
    double* data;    // pointer to the data array (size * size doubles)

    double calculateDeterminantRec(const double* mat, size_t n) const;
    double* getCofactor(const double* mat, size_t p, size_t q, size_t n) const;

public:
    explicit SquareMat(size_t n);// allocate zero n×n matri
    SquareMat(const double* values, size_t n);// copy from flat array
    SquareMat(const SquareMat& other);
    SquareMat& operator=(const SquareMat& other);
    ~SquareMat(); //free the data
    //Row-index operator: returns a pointer to the start of row row. Throws std::out_of_range if row >= size.
    double* operator[](size_t row);
    const double* operator[](size_t row) const;
    double getSum() const;

    //Matrix determinant: returns the determinant of the matrix.
    SquareMat operator+(const SquareMat& o) const;
    SquareMat operator-(const SquareMat& o) const;
    SquareMat operator-() const;
    SquareMat operator*(const SquareMat& o) const;
    SquareMat operator*(double sc) const;
    friend SquareMat operator*(double sc, const SquareMat& m) { return m * sc; }
    
    SquareMat operator%(const SquareMat& o) const;
    SquareMat operator%(int sc) const;
    //Scalar multiplication: returns a new matrix whose entries are this[i,j] * sc.
    SquareMat operator/(double sc) const;

    SquareMat operator^(int p) const;
    //Matrix power: returns a new matrix whose entries are this^p. Throws if p < 0.
    SquareMat& operator+=(const SquareMat& o);
    SquareMat& operator-=(const SquareMat& o);
    SquareMat& operator*=(const SquareMat& o);
    SquareMat& operator*=(double sc);
    SquareMat& operator/=(double sc);
    SquareMat& operator%=(const SquareMat& o);
    SquareMat& operator%=(int sc);
    //Compound assignment operators
    SquareMat& operator++();
    SquareMat  operator++(int);
    SquareMat& operator--();
    SquareMat  operator--(int);

    SquareMat operator~() const;

    double operator!() const;
    //Determinant operator: returns the determinant of the matrix.
    bool operator==(const SquareMat& o) const;
    bool operator!=(const SquareMat& o) const;
    bool operator<(const SquareMat& o) const;
    bool operator>(const SquareMat& o) const;
    bool operator<=(const SquareMat& o) const;
    bool operator>=(const SquareMat& o) const;

    friend std::ostream& operator<<(std::ostream& os, const SquareMat& m);
};

}

#endif 