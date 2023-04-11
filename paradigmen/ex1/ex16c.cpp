#include <iostream>

int main() {
    int a = 4; // variable named 'a' is declared and initialized with int value 4.
    int b = a + 6; //variable named 'b' is declared and initialized with value a+6 = 10, i.e. after this line we have that b=10.
    int *p = &a, **q = &p; // two pointer variables, p and q, are declared. p is initialized with the address of a, while q is initialized to point to the address of p, hence why it is declared as q**, a "pointer to a pointer". 
    std::cout << "Value of p: " << p << ". Value AT p: " << *p << std::endl;
    std::cout << "Address of a: " << &a << ". Value OF a: " << a << std::endl;
    *p *= 4**&b***q; // We access the value at memmorylocation stored in p, i.e. a. The following is done: *p(=a=4) = 4 * (*(&(b)) * (*(*(q)) * *p = 4 * deref address of b * deref deref q * deref p = 4 * 10 * 4 * 4 = 640 = a;
    std::cout << "After crazy ops...:\nValue of p: " << p << ". Value AT p: " << *p << std::endl;
    std::cout << "Address of a: " << & a << " Value of a(should be 640): " << a << std::endl;
    p = &b; // p is assigned the address of b. 
    *p = a + 5; // now b == 640 + 5 = 640.
    std::cout << "*p then b: " << *p << " " << b << std::endl;
    (*p)++; // b = 646.

    std::cout << "*p then b: " << *p << " " << b << std::endl;
    p *= 2; // Invalid operation: p is type (int *) but 2 is an int.
   
    std::cout << p-8<<std::endl;
    // a==640, b==646, p==&b, last one is some integer. (p-8) first is intepreted as some integer, then added to the address in p, which again is some integer. This only works if we use reinterpret_cast<int>, otherwise the compiler throws an error. The + operator does not work for (int*) + (int*) and p-8 is still interpreted as a pointer.
    std::cout << a << " " << b << " " << p << " " << (p + (p - 8)) << std::endl;
    //This works because first p-p is evaluated to an int, then we subtract 8 so all in all we get -8.
    std::cout << a << " " << b << " " << p << " " << (p - p - 8) << std::endl;
    return 1;
}
