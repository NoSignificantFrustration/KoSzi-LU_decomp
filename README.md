# About

Approximations and symbolic computation course project for extra credit.
Uses LU decomposition to solve Ax = b equation systems for multiple b vectors fast.


# Usage

1. Input integer n, such as your A matrix is size n\*n
2. Input your A vector, each scalar member separated by a whitespace character
3. Input vector b (size n), repeat for as many b vectors as you want


# Limitations

This is a very rudimentary solver, it does not check if a matrix is singular, or if main diagonal element gets zeroed out in the gaussian elimination process.
Both of these cases result in an exception.