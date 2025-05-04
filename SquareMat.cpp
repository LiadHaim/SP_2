//liadi.haim@gmail.com

#include "SquareMat.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace matrix {
 //Constructor that allocates an n×n matrix initialized to 0
SquareMat::SquareMat(size_t n) : size(n), data(nullptr) {
    if (n == 0) throw std::invalid_argument("Matrix size must be > 0");
    data = new double[n * n];
    for (size_t i = 0; i < n * n; ++i) data[i] = 0.0;
}
//Constructor from a flat array of length n*n. Copies the values into a new n×n matrix. Throws if pointer is null or n == 0
SquareMat::SquareMat(const double* values, size_t n) : size(n), data(nullptr) {
    if (!values || n == 0) throw std::invalid_argument("Input data invalid");
    data = new double[n * n];
    for (size_t i = 0; i < n * n; ++i) data[i] = values[i];
}
//Copy-constructor
SquareMat::SquareMat(const SquareMat& o) : size(o.size), data(nullptr) {
    data = new double[size * size];
    for (size_t i = 0; i < size * size; ++i) data[i] = o.data[i];
}
//Copy-assignment operator
// This operator is used to assign one SquareMat object to another
SquareMat& SquareMat::operator=(const SquareMat& o) {
    if (this == &o) return *this;
    delete[] data;
    size = o.size;
    data = new double[size * size];
    for (size_t i = 0; i < size * size; ++i) data[i] = o.data[i];
    return *this;
}
//Destructor
SquareMat::~SquareMat() {
    delete[] data;
}

double* SquareMat::operator[](size_t r) {
    if (r >= size) throw std::out_of_range("Row index out of range");
    return &data[r * size];
}
//Row-index operator: returns a pointer to the start of row row. Throws std::out_of_range if row >= size.
const double* SquareMat::operator[](size_t r) const {
    if (r >= size) throw std::out_of_range("Row index out of range");
    return &data[r * size];
}

//Computes and returns the sum of all elements in the matrix.
double SquareMat::getSum() const {
    double s = 0.0;
    for (size_t i = 0; i < size * size; ++i) s += data[i];
    return s;
}

//Element-wise addition: returns a new matrix whose entries are this[i,j] + o[i,j]. Sizes must match.
SquareMat SquareMat::operator+(const SquareMat& o) const {
    if (size != o.size) throw std::invalid_argument("Size mismatch");
    SquareMat r(size);
    for (size_t i = 0; i < size * size; ++i) r.data[i] = data[i] + o.data[i];
    return r;
}
//Element-wise subtraction: returns a new matrix whose entries are this[i,j] - o[i,j]. Sizes must match.
SquareMat SquareMat::operator-(const SquareMat& o) const {
    if (size != o.size) throw std::invalid_argument("Size mismatch");
    SquareMat r(size);
    for (size_t i = 0; i < size * size; ++i) r.data[i] = data[i] - o.data[i];
    return r;
}
//Unary minus: returns a new matrix whose entries are -this[i,j].
SquareMat SquareMat::operator-() const {
    SquareMat r(*this);
    for (size_t i = 0; i < size * size; ++i) r.data[i] = -r.data[i];
    return r;
}
//Matrix multiplication: returns a new matrix whose entries are the result of matrix multiplication. Sizes must match.
SquareMat SquareMat::operator*(const SquareMat& o) const {
    if (size != o.size) throw std::invalid_argument("Size mismatch");
    SquareMat r(size);
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < size; ++k)
                sum += (*this)[i][k] * o[k][j];
            r[i][j] = sum;
        }
    }
    return r;
}
//Scalar multiplication: returns a new matrix whose entries are this[i,j] * sc.
SquareMat SquareMat::operator*(double sc) const {
    SquareMat r(*this);
    for (size_t i = 0; i < size * size; ++i) r.data[i] *= sc;
    return r;
}
//Scalar multiplication: returns a new matrix whose entries are sc * this[i,j].
SquareMat SquareMat::operator%(const SquareMat& o) const {
    if (size != o.size) throw std::invalid_argument("Size mismatch");
    SquareMat r(size);
    for (size_t i = 0; i < size * size; ++i) r.data[i] = data[i] * o.data[i];
    return r;
}
//Scalar multiplication: returns a new matrix whose entries are this[i,j] % sc.
SquareMat SquareMat::operator%(int sc) const {
    if (sc == 0) throw std::invalid_argument("Modulo by zero");
    SquareMat r(size);
    for (size_t i = 0; i < size * size; ++i) r.data[i] = std::fmod(data[i], sc);
    return r;
}
//Scalar division: returns a new matrix whose entries are this[i,j] / sc. Throws if sc == 0.
SquareMat SquareMat::operator/(double sc) const {
    if (sc == 0) throw std::invalid_argument("Divide by zero");
    SquareMat r(*this);
    for (size_t i = 0; i < size * size; ++i) r.data[i] /= sc;
    return r;
}
//Matrix power: returns a new matrix whose entries are this^p. Throws if p < 0.
SquareMat SquareMat::operator^(int p) const {
    if (p < 0) throw std::invalid_argument("Negative power");
    if (p == 0) {
        SquareMat I(size);
        for (size_t i = 0; i < size; ++i) I.data[i*size + i] = 1.0;
        return I;
    }
    SquareMat r(*this);
    for (int k = 1; k < p; ++k) r = r * (*this);
    return r;
}

//Compound assignment operators
SquareMat& SquareMat::operator+=(const SquareMat& o) {
    if (size != o.size) throw std::invalid_argument("Size mismatch");
    for (size_t i = 0; i < size * size; ++i) data[i] += o.data[i];
    return *this;
}
//Compound assignment operator for subtraction
SquareMat& SquareMat::operator-=(const SquareMat& o) {
    if (size != o.size) throw std::invalid_argument("Size mismatch");
    for (size_t i = 0; i < size * size; ++i) data[i] -= o.data[i];
    return *this;
}
//Compound assignment operator for multiplication
SquareMat& SquareMat::operator*=(const SquareMat& o) {
    *this = *this * o;
    return *this;
}
//Compound assignment operator for scalar multiplication
SquareMat& SquareMat::operator*=(double sc) {
    for (size_t i = 0; i < size * size; ++i) data[i] *= sc;
    return *this;
}
//Compound assignment operator for scalar division
SquareMat& SquareMat::operator/=(double sc) {
    if (sc == 0) throw std::invalid_argument("Divide by zero");
    for (size_t i = 0; i < size * size; ++i) data[i] /= sc;
    return *this;
}
//Compound assignment operator for element-wise multiplication
SquareMat& SquareMat::operator%=(const SquareMat& o) {
    if (size != o.size) throw std::invalid_argument("Size mismatch");
    for (size_t i = 0; i < size * size; ++i) data[i] *= o.data[i];
    return *this;
}
//Compound assignment operator for element-wise modulo
SquareMat& SquareMat::operator%=(int sc) {
    if (sc == 0) throw std::invalid_argument("Modulo by zero");
    for (size_t i = 0; i < size * size; ++i) data[i] = std::fmod(data[i], sc);
    return *this;
}

//Pre-increment operator: increments all elements by 1
SquareMat& SquareMat::operator++() {
    for (size_t i = 0; i < size * size; ++i) data[i] += 1.0;
    return *this;
}
//Pre-increment operator: increments all elements by 1 and returns the old value
SquareMat SquareMat::operator++(int) {
    SquareMat tmp(*this);
    ++(*this);
    return tmp;
}
//Post-decrement operator: decrements all elements by 1
SquareMat& SquareMat::operator--() {
    for (size_t i = 0; i < size * size; ++i) data[i] -= 1.0;
    return *this;
}
//Post-decrement operator: decrements all elements by 1 and returns the old value
SquareMat SquareMat::operator--(int) {
    SquareMat tmp(*this);
    --(*this);
    return tmp;
}

//Transpose operator: returns a new matrix whose entries are the transpose of this matrix.
SquareMat SquareMat::operator~() const {
    SquareMat r(size);
    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size; ++j)
            r.data[j*size + i] = data[i*size + j];
    return r;
}

//Helper function to calculate the cofactor of a matrix
double* SquareMat::getCofactor(const double* mat, size_t p, size_t q, size_t n) const {
    double* cof = new double[(n-1)*(n-1)];
    size_t idx = 0;
    for (size_t i = 0; i < n; ++i) {
        if (i == p) continue;
        for (size_t j = 0; j < n; ++j) {
            if (j == q) continue;
            cof[idx++] = mat[i*n + j];
        }
    }
    return cof;
}
//Recursive function to calculate the determinant of a matrix
double SquareMat::calculateDeterminantRec(const double* mat, size_t n) const {
    if (n == 1) return mat[0];
    double det = 0.0;
    int sign = 1;
    for (size_t j = 0; j < n; ++j) {
        double* cof = getCofactor(mat, 0, j, n);
        det += sign * mat[j] * calculateDeterminantRec(cof, n-1);
        delete[] cof;
        sign = -sign;
    }
    return det;
}

double SquareMat::operator!() const {
    return calculateDeterminantRec(data, size);
}

//Comparison operators based on the sum of the elements
bool SquareMat::operator==(const SquareMat& o) const { return getSum() == o.getSum(); }
bool SquareMat::operator!=(const SquareMat& o) const { return !(*this == o); }
bool SquareMat::operator< (const SquareMat& o) const { return getSum() <  o.getSum(); }
bool SquareMat::operator> (const SquareMat& o) const { return getSum() >  o.getSum(); }
bool SquareMat::operator<=(const SquareMat& o) const { return getSum() <= o.getSum(); }
bool SquareMat::operator>=(const SquareMat& o) const { return getSum() >= o.getSum(); }

//Output operator: prints the matrix in a readable format
std::ostream& operator<<(std::ostream& os, const SquareMat& m) {
    for (size_t i = 0; i < m.size; ++i) {
        os << "[";
        for (size_t j = 0; j < m.size; ++j) {
            os << m.data[i*m.size + j];
            if (j + 1 < m.size) os << ", ";
        }
        os << "]";
        if (i + 1 < m.size) os << "\n";
    }
    return os;
}

} 