#include <stdio.h>
#include <iostream>

#define SUCCESS 0

using namespace std;

int mdc(int a, int b) {
    if(b == 0) 
        return a;
    else {
        return mdc(b, a % b);
    }
}

int main() {
    int a, b, mdcAnswer;
    cout << "Digite dois numeros inteiros: ";
    cin >> a >> b;
    mdcAnswer = mdc(a, b);
    cout << "Resultado: " << mdcAnswer << "\n";
}