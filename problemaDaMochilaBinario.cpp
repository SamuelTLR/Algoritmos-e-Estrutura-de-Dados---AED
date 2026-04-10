#include <iostream>
#include <vector>

#define SUCCESS 0
#define value 1
#define weigth 0
using namespace std;

int retornaIndexDoMaiorPeso(int** matriz, int numDeItens, int pesoMaximo) {
    int maior = matriz[0][0], index = 0;
    for(int i = 1; i < numDeItens; i++) {
        if(matriz[i][0] > maior && matriz[i][0] < pesoMaximo) {
            maior = matriz[i][0];
            index = i;
        }
    }
    return index;
}

int retornaMelhorItem(int** matriz, int numDeItens, int pesoMaximo, int* pesoVetor) {
    int peso, valor, index = retornaIndexDoMaiorPeso(matriz, numDeItens, pesoMaximo);

    peso = matriz[index][0];
    valor = matriz[index][1];
    for(int i = 0; i < numDeItens; i++) {
        if(matriz[i][0] < peso && matriz[i][1] > valor && (matriz[i][0] + *pesoVetor) <= pesoMaximo) {
            index = i;
        }
    }
    *pesoVetor += matriz[index][0];
    return index;
}

int **criaNovaMatriz(int linhas, int colunas) {
    int** matriz = new int*[linhas];
    for (int i = 0; i < linhas; i++) {
            matriz[i] = new int[colunas];
    }
    return matriz;
}

int calculaValorTotal(int** matriz, vector<int> vetor) {
    int valorT = 0;
    for(int i = 0; i < vetor.size(); i++) {
        valorT += matriz[vetor.at(i)][value];
    }
    return valorT;
}

int calculaMelhorSolucao(int** matriz, int numDeItens, int pesoMaximo) {
    int pesoVetor = 0;
    int numDeItensNovo = numDeItens, jaTaNaMochila = 1;
    vector<int> indexVetor;

    indexVetor.push_back(retornaMelhorItem(matriz, numDeItens, pesoMaximo, &pesoVetor));
    while(pesoVetor < pesoMaximo) {
        numDeItensNovo--;
        int **matrizNovo = criaNovaMatriz(numDeItensNovo, numDeItensNovo);
        if(numDeItensNovo > 0) {
            for(int i = 0; i < numDeItens; i++) {
                for(int x = 0; x < indexVetor.size(); x++) {
                    if(i == indexVetor[x]) {
                        jaTaNaMochila = 0;
                    } 
                }
                if(jaTaNaMochila) {
                    matrizNovo[i][0] = matriz[i][0];
                    matrizNovo[i][1] = matriz[i][1];
                }
                jaTaNaMochila = 1;
            }
            indexVetor.push_back(retornaMelhorItem(matrizNovo, numDeItensNovo, pesoMaximo, &pesoVetor));
        } else {
            break;
        }
    }

    int valorTotal = calculaValorTotal(matriz, indexVetor);
    return valorTotal;
}



int main() {
    int peso, numDeItens, entraOuNao;
    vector<int> index, melhorSolucao;
    cin >> peso;
    cin >> numDeItens;
    int **catalago = criaNovaMatriz(numDeItens, numDeItens);
    for(int i = 0; i < numDeItens; i++) {
        cin >> catalago[i][0];
        cin >> catalago[i][1];
    }
    for(int i = 0; i < numDeItens; i++) {
        cin >> entraOuNao;
        if(entraOuNao)
            index.push_back(i);
    }

    printf("ValorTotal: %d ", calculaMelhorSolucao(catalago, numDeItens, peso));


    return SUCCESS;
}