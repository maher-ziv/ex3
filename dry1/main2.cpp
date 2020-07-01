#include <iostream>
using namespace std;
class A {
public:
    A() {}
    A(const A& a) { cout << "A copy ctor" << endl; }
    virtual ~A() { cout << "A dtor" << endl; }
    virtual void type() const { cout << "This is A" << endl; }
};
class B: public A {
public:
    virtual ~B() { cout << "B dtor" << endl; }
    void type() const override { cout << "This is B" << endl; }
};
A f(A a) {
    a.type();
    return a;
}
const A& g(const A& a) {
    a.type();
    return a;
}
int main()
{
    A* pa = new B();
    cout << "applying function f:" << endl;
    f(*pa).type();
    cout << "applying function g:" << endl;
    g(*pa).type();
    delete pa;
    return 0;
}

/*
applying function f:  ---  Standard output stream

A copy ctor --- f(*pa) passing a copy of *pa, the function is excepting 'A' type
                and copying an A type value. the COPY is 'sliced' from 'B' to 'A' type

This is A --- inside the function f the function type() of the copy we made is being called
              as mentioned before the copy is an A type


A copy ctor --- a copy ctor is being called again when returning 'a' by value
                the copy is A type

This is A -- after returning a copy of *pa from function f we call type()

A dtor - dtor for the first copy we made when we copied to f

A dtor - dtor for the second copy we made when we returned a value from f by value

applying function g: ---  Standard output stream

This is B --- g gets *pa by reference so 'a' is exactly *pa and stays 'B' type
              B is subclass of A so 'g(const A& a)' can get A& and B& (not if it's by value)
              (this is the outcome from type() inside the function g)

This is B --- g returns again 'a' by reference so returning *pa again so stays 'B' type
              B is subclass of A so const 'A& g(const A& a)' can return A& and B& (not if it's by value)
              (this is the outcome from type() outside the function g)

B dtor --- *pa which is 'B' type and didn't change , so first this dtor is being called
A dtor --- when B dtor finished he is calling to A dtor


 */