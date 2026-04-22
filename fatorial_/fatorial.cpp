#include <iostream>

using namespace std;

#define SUCCESS 0

int digits(int a) {
    if(a > 0) {
        return digits(a / 10) + 1;
    }
    else 
        return 0;
}

int* transformaEmVetor(int numero) {
    int tamanho = digits(numero), aux = 0;
    int* numero_vetor = new int[tamanho];
    for(int i = 0; i < tamanho; i++) {
        aux = numero % 10;
        numero = numero / 10;
        numero_vetor[i] = aux;
    }
    return numero_vetor;
}

int* mult(int* vetor1, int* vetor2,int tamanho, int tamanho2) {
  int aux1 = 0, aux2 = 0;
  for(int x = 0; x < tamanho2; x++) {
    for(int i = 0; i < tamanho; i++) {
      aux1 = vetor1[i]; 
      aux2 = vetor2[x];
      vetor1[i] = aux1 * aux2;
    }
  }
  return vetor1;
}

int* carryIn(int* vetor, int* tamanho) {
  int aux = 0;
  for(int i = 0; i < *tamanho; i++) {
    int x = vetor[i];
    if(vetor[i] > 9) {
      aux = vetor[i];
      vetor[i] = aux % 10;
      if(i == *tamanho - 1) {
        vetor[i + 1] = 0;
        vetor[i + 1] += aux / 10;
        *tamanho = *tamanho + 1;
      } else {
        vetor[i + 1] += aux / 10;
      }
    }
  }
  return vetor;
}

int main() {
  int numero = 10, *vetor1, *vetor2, *tamanho;

  *tamanho = digits(numero);

  vetor1 = new int[36000];
  vetor2 = new int[36000];

  vetor1 = transformaEmVetor(numero);
  for(int i = 0; i < *tamanho; i++) {
    printf("%d", vetor1[i]);
  }

  for(int i = numero - 1; i > 0; i--) {
    int tamanho2 = digits(i);
    vetor2 = transformaEmVetor(i);

    vetor1 = mult(vetor1, vetor2, *tamanho, tamanho2);
    vetor1 = carryIn(vetor1, tamanho);
  }

  printf("\n");
  for(int i = *tamanho - 1; i >= 0; i--) {
    printf("%d", vetor1[i]);
  }
}
