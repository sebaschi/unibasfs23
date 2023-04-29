#include "dynarr.h"
#include <cassert>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

// Define default ctor  
template <class T> Darray<T>::Darray() {
    cap = 10;
    len = 0;
    arr = new T[cap];
}

// Constructor with len
template <class T> Darray<T>::Darray(int c) {
    assert(c > 0);
    cap = c;
    len = 0; 
    arr = new T[cap];
}

// Copy ctor
template <class T> Darray<T>::Darray(const Darray& ref) {
    len = ref.len;
    cap = ref.cap;
    arr = new T[cap];
    memcpy(arr, ref.arr, cap*sizeof(T));
}

// Assignment operator
template <class T> Darray<T>& Darray<T>::operator=(const Darray& rhs) {
    if (&rhs == this)
        return *this;

    if (cap != rhs.cap) {
        delete[] arr;
        arr = new T[rhs.cap];
    }

    len = rhs.len;
    memcpy(arr, rhs.arr, cap * sizeof(T));

    return *this;
}

// Destructor
template <class T> Darray<T>::~Darray() {
    delete[] arr;
}

template <class T> void Darray<T>::resize() {
    //Conditional resize so resize() can be called blindly before every add()
    if (len + 5 >= cap) {
        int newCap = ceil(cap * 1.8);
        assert(newCap ==  ceil(cap * 1.8));
        T* newArr = new T[newCap];
        memcpy(newArr, arr, len * sizeof(T));
        cap = newCap;
        // Release old memory
        delete[] arr;
        // Let T* point to new, resized array
        arr = newArr;
    }
}

template <class T> void Darray<T>::add(T item) {
    resize();
    arr[len] = item;
    len++;
}

template <class T> T Darray<T>::get(int index) {
    assert(index < len);
    assert(index >= 0);
    return arr[index];
}

template <class T> void Darray<T>::removeLast() {
    assert(len>0);
    len--;
}

template <class T> void Darray<T>::set(int index, T item) {
    assert(index < len);
    assert(index >= 0);
    arr[index] = item;
}

template <class T> void Darray<T>::printArr() const {
    cout << "Length: " << len << " Capacity: " << cap;
    for (int i = 0; i < len; i++) {
        cout << " " << arr[i];
    } 
    cout << endl;
}

int main() {

    /* Showcase char */
    Darray<char> charArr(3);
    charArr.printArr();
    char d = 'a';
    charArr.add(d);
    charArr.printArr();
    charArr.add(d++);
    charArr.add(d++);
    charArr.add(d++);
    charArr.add(d++);
    charArr.printArr();
    charArr.removeLast();
    charArr.printArr();
    cout << charArr.get(0) << endl;
    charArr.set(0,d++);
    charArr.printArr();
    Darray<char> cpCharArr(charArr);
    cpCharArr.printArr();
    cpCharArr.add(d--);
    cpCharArr.printArr();
    charArr.printArr();
    charArr = cpCharArr;
    charArr.printArr();

    cout << endl << endl;
    /* Showcase int */
    Darray<int> intArr(3);
    intArr.printArr();
    int n = 0;
    intArr.add(n);
    intArr.printArr();
    intArr.add(n++);
    intArr.add(n++);
    intArr.add(n++);
    intArr.add(n++);
    intArr.printArr();
    intArr.removeLast();
    intArr.printArr();
    cout << intArr.get(0) << endl;
    intArr.set(0,n++);
    intArr.printArr();
    Darray<int> cpIntArr(intArr);
    cpIntArr.printArr();
    cpIntArr.add(n--);
    cpIntArr.printArr();
    intArr.printArr();
    intArr = cpIntArr;
    intArr.printArr();

    cout << endl << endl;
    /* Showcase double */
    Darray<double> doubleArr(3);
    doubleArr.printArr();
    double x = 1;
    doubleArr.add(x);
    doubleArr.printArr();
    doubleArr.add(x *= 1.2);
    doubleArr.add(x *= 1.2);
    doubleArr.add(x *= 1.2);
    doubleArr.add(x *= 1.2);
    doubleArr.printArr();
    doubleArr.removeLast();
    doubleArr.printArr();
    cout << doubleArr.get(0) << endl;
    doubleArr.set(0,x *= 1.2);
    doubleArr.printArr();
    Darray<double> cpdoubleArr(doubleArr);
    cpdoubleArr.printArr();
    cpdoubleArr.add(x/=2);
    cpdoubleArr.printArr();
    doubleArr.printArr();
    doubleArr = cpdoubleArr;
    doubleArr.printArr();


}

