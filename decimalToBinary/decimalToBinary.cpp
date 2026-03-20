#include <stdio.h>
#include <iostream>

#define SUCCESS 0

using namespace std;

void dec2bin(int dec) {
    if(dec > 0 ) {
        dec2bin(dec / 2);
        cout << dec % 2;
    } 
}

int main() {
    int dec;
    cout << "Digite um numero inteiro: ";
    cin >> dec;
    cout << "Resultado: ";
    dec2bin(dec);
    cout << "\n";
}