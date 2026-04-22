#include <iostream>
#include <stdio.h>   
#include <stdlib.h> 

using namespace std;
int digits(int a) {
    if(a > 0) {
        return digits(a / 10) + 1;
    }
    else 
        return 0;
}

void numeroParaVetorDeDigitos(int a, int tamanho, int* numero) {
    int aux = 0;
    for(int i = 0; i < tamanho; i++) {
        aux = a % 10;
        a = a / 10;
        numero[i] = aux;
    }

}

void somador(int* numeroFatorial, int* numero, int a, int numeroDeDigitos) {
    int aux = 0;
    while(a > 0) {
        for(int i = 0; i < a; i++) {
            for(int y = 0; y < numeroDeDigitos; i++) {
                aux = numeroFatorial[y] + numero[y];
                if(aux < 10)
                    numeroFatorial[y] = aux; 
                else {
                    numeroFatorial[y] = aux % 10;
                    numeroFatorial[y + 1] += aux / 10;
                }
            }
        }
        a = a - 1;
    }
}

int main() {
    int numberOne[36000];
    int a = 100, i = 0, numDigitos = 0;

    numDigitos = digits(a);
    cout << "Numero de digitos: " << numDigitos << "\n";

    int* numero = new int[numDigitos];

    numeroParaVetorDeDigitos(a, numDigitos, numero);
    for(int i = 0; i < numDigitos; i++)
        cout << numero[i];
    cout << "\n";

    somador(numberOne, numero, a, numDigitos);
    for(int i = 0; i < numDigitos; i++)
        cout << numberOne[i];
    cout << "\n";

    delete[] numero;
    return 0;
}