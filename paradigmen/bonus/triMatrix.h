#include <complex>
class triMatrix {
    public:
       int n=0;
       std::complex<double>** matrix;
       triMatrix();
       triMatrix(int n, std::complex<double>* matrix);
       triMatrix(int n, std::complex<double>** matrix);
       ~triMatrix();
       triMatrix(const triMatrix& other); // copy constructor

       triMatrix& operator=(const triMatrix& other); // assignment operator
       triMatrix& operator+=(const triMatrix& other);
       triMatrix operator+(const triMatrix& other);
       triMatrix transposed();
       triMatrix operator*(const triMatrix& other);
};       
