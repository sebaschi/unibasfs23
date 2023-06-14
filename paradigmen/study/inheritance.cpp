#include <iostream>
#include <string>

using namespace std;

class C1 {
    public:
        virtual void f1() {
            f2();
            cout << "C1 - f1" << endl;
        }
        virtual void f2() {
            cout << "C1 - f2" << endl;
        }
};

class C2 : public C1 {
    public:
        void f1() {
            f2();
            cout << "C2 - f1" << endl;
        }
        void f2() {
            cout << "C2 - f2" << endl;
        }
        virtual void f3() {
            f1();
            cout << "C2 - f3" << endl;
        }
};
class C3 : public C2 {
    public:
        void f1() {
            f2();
            cout << "C3 - f1" << endl; 
        }   

};

int main() {
    C1* aa = new C1();
    C2* bb = new C2();
    C1* ab = bb;
    C1* ac = new C3();

    aa->f1(); cout << "----" << endl;
    bb->f1(); cout << "----" << endl;
    bb->f2(); cout << "----" << endl;
    ab->f2(); cout << "----" << endl;
    bb->f3(); cout << "----" << endl;
    ac->f1(); cout << "----" << endl;

    C2* cc = new C3();
    cc->f1(); cout << "----" << endl;
    cc->f2(); cout << "----" << endl;
        
    
    return 0;
}
