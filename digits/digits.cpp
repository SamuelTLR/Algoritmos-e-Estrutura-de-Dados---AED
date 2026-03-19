#include <stdio.h>
#include <iostream>

#define SUCCESS 0

using namespace std;

int Digitos(int N) {
    if(N / 10 > 0) {
        return Digitos(N / 10) + 1;
    } else {
        return 1;
    }
}

int main() {
    int number = 0;
    cout << "Digite um numero inteiro: ";
    cin >> number;
    cout << "Resultado: " << Digitos(number) << "\n";
    return SUCCESS;
}