#include <iostream>

using namespace std;

#define SUCCESS 0

int** buildMatrix(int tamanho) {
  int** matriz = new int*[tamanho];

  for(int i = 0; i < tamanho; i++)
  {
      matriz[i] = new int[i + 1];
  }
  return matriz;
}

void cleanMatrix(int** matrix, int linhas) {
  for (int i = 0; i < linhas; ++i) {
        delete[] matrix[i];
  }
  delete[] matrix;
}

void zera(int **generic, int linhas) {
  for(int  i = 0; i < linhas; i++) {
    for(int x = 0; x < i + 1; x++) {
      generic[i][x] = 0;
    }
  }
}

void funcaoSoma(int** soma, int **matriz, int linha, int coluna) {
  soma[linha][coluna] = matriz[linha][coluna];
  for(int i = linha - 1; i >= 0; i--) {
    for(int x = 0; x < i + 1; x++) {
     // cout << soma[linha][coluna] << " " << matriz[i][x] << '\n';
      soma[linha][coluna] += matriz[i][x];
     // cout << soma[linha][coluna] << '\n';
    }
  }
}

void acharIndexMaior(int** matriz, int tamanho) {
  int linha = 1, coluna = 1, maior = matriz[0][0];
  for(int i = 0; i < tamanho; i++) {
    for(int x = 0; x < i + 1; x++) {
      if(maior < matriz[i][x]) {
        linha = i + 1;
        coluna = x + 1;
        maior = matriz[i][x];
      }
    }
  }

  cout << "Resposta: camada " << linha << ", caixa " << coluna << ".\n";
}

int main() {
  int tamanho, aux;
  cin >> tamanho;
  int** matriz = buildMatrix(tamanho);
  int** soma = buildMatrix(tamanho);

  for(int i = 0; i < tamanho; i++) {
    for(int x = 0; x < i + 1; x++) {
      cin >> matriz[i][x];
    }
  }

  zera(soma, tamanho);
  for(int i = 0; i < tamanho; i++) {
    for(int x = 0; x < i + 1; x++) {
      funcaoSoma(soma, matriz, i, x);
    }
  }

  acharIndexMaior(soma, tamanho);

  cleanMatrix(matriz, tamanho);
  cleanMatrix(soma, tamanho);
}