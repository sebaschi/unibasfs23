#include <iostream>
#include <math.h>

int compare_sin(double *arr1, double *arr2);
int compare_taxicab(double *arr1, double *arr2);
int compare(double *arr1, double *arr2, int  cmp(double *, double *));

// Implementation of the compare_sin function
int compare_sin(double *arr1, double *arr2) {
    double res;
    //Get sines of second component and subtract.
    res = sin(arr1[1]) - sin (arr2[1]);
    // Then sine in first array was larger
    if (res > 0) return 1;
    //If second arrays sine was larger
    if (res < 0) return -1;
    // If equal
    if (res == 0) return 0;
    //Debug help
    std::cout << "Error of some kind " << res << std::endl;
    return res;
}

// Implementation of compare_taxicab function
int compare_taxicab(double *arr1, double *arr2) {
    double norm1, norm2;
    //We can just take the absolute values since we're starting from the origin (0,0,0)
    //Take L1 norm of each array, i.e. treat as point in Euclidean Space
    //and measure distance from origin according to taxicab norm.
    norm1 = abs(arr1[0]) + abs(arr1[1]) + abs(arr1[2]);
    norm2 = abs(arr2[0]) + abs(arr2[1]) + abs(arr2[2]);
    //Compare L1 norms and return -1,0,1 accordingly.
    if ( norm1 > norm2) return 1;
    if (norm1 < norm2) return -1;
    if(norm1==norm2) return 0;
    //Debug help
    std::cout << "Error of some kind in taxicab." << std::endl;
    return norm1-norm2;
}


//Implementation compare function
int compare(double *arr1, double *arr2, int  cmp(double *, double *)) {
    int res;
    //Compare using function passed as parameter and return result
    res = cmp(arr1, arr2);
    return res;

}

int main() {
    double *array1 = new double[3] {75, 4, 29};
    double *array2 = new double[3] {1, 10, 7};
    //Notice that c++ will automatically convert the parameters compare_sin and compare_taxicab into function pointers, so no need to use &
    std::cout << compare(array1, array2, compare_sin) << std::endl;
    std::cout << compare(array1, array2, compare_taxicab) << std::endl;
}
