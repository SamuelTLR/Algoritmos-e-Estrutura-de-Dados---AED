#include <iostream>
#include <vector>

#define SUCCESS 0
#define weight 0
#define value 1

using namespace std;

int **criaNovaMatriz(int linhas, int colunas) {
    int** matriz = new int*[linhas];
    for (int i = 0; i < linhas; i++) {
            matriz[i] = new int[colunas];
    }
    return matriz;
}

int achaMaiorValor(int** matriz, int numDeItens, int peso) {
  int pesoAtual = 0, valor, maiorValor = 0;
  for(int i = 0; i < numDeItens; i++) {
    pesoAtual = matriz[i][weight];
    valor = matriz[i][value];

    for(int x = 1; x < numDeItens; x++) {
      int z = x;
      for(int j = pesoAtual; j < peso;) {
        if((z + x) == numDeItens)
          break;
        if(matriz[x + z][weight] + pesoAtual <= peso) {
          pesoAtual += matriz[x + z][weight];
          valor += matriz[x + z][value];
        }
        z++;
      }
      if(maiorValor < valor) 
        maiorValor = valor;
      pesoAtual = matriz[i][weight];
      valor = matriz[i][value];
    }

    for(int x = numDeItens - 1; x > 0; x--) {
      int z = x;
      for(int j = pesoAtual; j < peso;) {
        if(x - z == 0)
          break;
        if(matriz[x - z][weight] + pesoAtual <= peso) {
          pesoAtual += matriz[x - z][weight];
          valor += matriz[x - z][value];
        }
        z++;
      }
      if(maiorValor < valor) 
        maiorValor = valor;
      pesoAtual = matriz[i][weight];
      valor = matriz[i][value];
    }
  }
  return maiorValor;
}

float retornaValor(int** matriz, vector<int> index, int peso) {
    float valor = 0, pesoAtual = 0;
    for(int i = 0; i < index.size(); i++) {
        int x = index[i];
        valor += matriz[x][value];
        pesoAtual += matriz[x][weight];
    }
    if(pesoAtual > peso)
        return 0;
        
    return valor;
}

void verificaValor(int** matriz, vector<int> index, int maiorValor,int  numDeItens, int peso) {
    float valorIndex;
    
    valorIndex = retornaValor(matriz, index, peso);

    if(valorIndex >= maiorValor) {
        printf("Solucao otima.\n");
    }else if(valorIndex == 0) {
        printf("Solucao inviavel.\n");
    }else {
        printf("Solucao viavel mas nao otima.\n");
    } 
}

int main() {
  int** catalogo, peso, numDeItens;
  vector<int> index;
  cin >> peso;
  cin >> numDeItens;

  catalogo = criaNovaMatriz(numDeItens, 2);
  for(int i = 0; i < numDeItens; i++) {
      cin >> catalogo[i][0];
      cin >> catalogo[i][1];
  }

  int entraOuNao;
  for(int i = 0; i < numDeItens; i++) {
      cin >> entraOuNao;
      if(entraOuNao)
          index.push_back(i);
  }

  int maiorValor = achaMaiorValor(catalogo, numDeItens, peso);
  verificaValor(catalogo, index, maiorValor, numDeItens, peso);

  return SUCCESS;
}