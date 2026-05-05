#include <iostream>
#include <vector>

#define SUCCESS 0;

using namespace std;

void decomposicao2(int numero) {
    if(numero > 1) {
        printf(" %d", numero);
        decomposicao2(numero - 1);
    } else {
        printf(" %d %d", numero, numero);
    }
    printf("\n");
}

void decomposicao(int numero, int aux) {
    if(aux > 1) {
        printf("%d %d\n", numero, aux);
        printf("%d", numero);
        decomposicao2(aux - 1);
    } else {
        printf("%d %d\n", numero, aux);
    }
    if(numero - 1 > aux + 1)
        decomposicao(numero - 1, aux + 1);
    else {
        
    }
}

int main() {
    int numero;
    cin >> numero;
    printf("Decomposicao:\n%d\n", numero);
    decomposicao(numero - 1, 1);
}