# SquareMat Library

## A C++ library providing a SquareMat class for operations on square matrices of doubles.

### Features
- Construction from size or flat array
- Deep copy and assignment
- Element access with bounds checking
- Arithmetic: addition, subtraction, unary minus
- Matrix multiplication and scalar multiplication
- Element-wise (Hadamard) multiplication and scalar modulo
- Scalar division and matrix exponentiation
- Increment/decrement operators (++/--)
- Transpose and determinant
- Compound assignment operators (+=, -=, *=, /=, %=)
- Comparison by sum of elements (==, !=, <, >, <=, >=)
- operator<< for formatted output

### Project Structure
```bash
A_2/
├── SquareMat.hpp       # Class declaration
├── SquareMat.cpp       # Class implementation
├── main.cpp            # Demonstration program
├── Test.cpp            # doctest unit tests
├── Makefile            # Build and test commands
└── README.md           # This file
```
### Requirements

- C++17-compatible compiler (e.g., clang++ or g++)
- doctest header for unit testing
- valgrind (optional) for memory leak checks

### Build & Run
```bash
# Build everything (demo and tests)
make all

# Run demonstration
make Main

# Run unit tests
make test

# Check for memory leaks
make valgrind

# Clean build artifacts
make clean
```
