#include "triMatrix.cpp"
#include <iostream>
#include <complex>

using namespace std;

int main() {
    triMatrix *a = new triMatrix(5, { 1.2 + 0.2*i ,
                                      3.2 - 0.2*i , -12.4 ,
                                      0.0         ,   5.4 , 4.3     ,
                                      12.2 + 2.1*i , -4.3 , 3.2 - 0.3*i , 5.5 ,
                                      8.7 + 3.0*i , 6.5 , 1.0 , -3.1, 4.3});
    triMatrix *b = new triMatrix(5, { -6.3 ,
                                      2.3 , 4.3 - 1.2*i,
                                      5         , 11.2 , 3.1     ,
                                      -0.1 , 7.7 , 1.3 , -9.1 ,
                                      21.3 , 8.8 , 8.9 , 0, 2.0});
    triMatrix *c;

    c = (triMatrix*) malloc (sizeof(triMatrix));

    *c = *a + *b;
    *b += a->transposed();
    *a += 2 * *b;

    delete a, b, c;

    return(0);
}
