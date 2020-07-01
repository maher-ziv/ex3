#include <iostream>
using namespace std;

class B {
private:
    int n;
public:
    B(int x) : n(x) {}
    B operator +(B& b) {
        return B(n+b.n);
    }
    friend ostream& operator <<(ostream &out, const B& b) {
        out << "B: " << n; //operator << is a friend function that doesn't get *this and we must write b.n
        return out;
    }
    bool operator <(const B& rhs) const {
        return n < rhs.n;
    }
};

B smaller (const B& b1, const B& b2) { 
    if(b1 < b2)                        //operator works only when b1 isn't const. changed operator < to const.           
        return b1;
    else
        return b2;
}


int main() {
    B b1(1), b2(2), b3(3);
    const B b4 = b1 + (b2 + b3); // operator () is undefined for class B and isn't needed in this case
    cout << smaller(b1,b2) << endl;
    return 0;
}

