#include <iostream>
#include <complex>

#include "triMatrix.h"

using namespace std;

// Constructor
//
triMatrix::triMatrix() {
    this->n = 0;
    this->matrix = NULL;
}
triMatrix::triMatrix(int n, complex<double>* matrix) {
    this->n = n;
    this->matrix = new complex<double>*[n];
    int k = 0;
    for (int i=0; i<n; i++) {
        this->matrix[i] = new complex<double>[n];
        for (int j=0; j<i; j++) {
            this->matrix[i][j] = matrix[k];
            k++;
        }
        for (int j=i+1; j<n; j++) {
            this->matrix[i][j] = 0.0;
        }
    }
}

triMatrix::triMatrix(int n=0,complex<double>** matrix=NULL) {
    this->n = n;
    this->matrix = matrix;
}

triMatrix::triMatrix(const triMatrix& other) {
    this->n = other.n;
    this->matrix = other.matrix;
}

triMatrix::~triMatrix() {
    delete[] matrix;
}

triMatrix& triMatrix::operator=(const triMatrix& other) {
    this->n = other.n;
    this->matrix = other.matrix;
    return *this;
}
triMatrix& triMatrix::operator+=(const triMatrix& other) {
    if (this->n != other.n) {
        cout << "Error: matrix size not match!" << endl;
        return *this;
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            this->matrix[i][j] += other.matrix[i][j];
        }
    }
    return *this;
}
triMatrix triMatrix::operator+(const triMatrix& other) {
    triMatrix result(*this);

    if (this->n != other.n) {
        cout << "Error: matrix size not match!" << endl;
        return result;
    }

    result += other;

    return result;
}       

triMatrix triMatrix::transposed() {
    triMatrix result(this->n);

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            result.matrix[i][j] = this->matrix[j][i];
        }
    }

    return result;
}

triMatrix triMatrix::operator*(const triMatrix& other) {
    triMatrix result(this->n);
    triMatrix thisT = this->transposed();
    if (this->n != other.n) {
        cout << "Error: matrix size not match!" << endl;
        return result;
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            result.matrix[i][j] = thisT.matrix[i][j] * other.matrix[i][j];
         }
    }

    return result;
}
