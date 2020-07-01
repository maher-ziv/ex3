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
        out << "B: " << b.n;
    }
    bool operator <(const B& rhs) const {
        return n < rhs.n;
    }
    B smaller (const B& b1, const B& b2);
};

B smaller (const B& b1, const B& b2) {
    if(b1 < b2)
        return b1;
    else
        return b2;
}





int main() {
    B b1(1), b2(2), b3(3);
    const B b4 = b1 + b2 + b3;
    cout << smaller(b1,b2) << endl;
    return 0;
}