#include <iostream>
#include <vector>

#define SUCCESS 0
#define value 1
#define weigth 0
using namespace std;

int verificaSeTaNaMochila(int i, vector<int> indexVetor) {
    for(int x = 0; x < indexVetor.size(); x++) {
        if(i == indexVetor[x]) {
            return 0;
        } 
    }
    return 1;
}

int retornaIndexDoMaiorPeso(int** matriz, int numDeItens, int pesoMaximo, vector<int> indexBloqueado) {
    int maior = matriz[0][0], index = 0;
    for(int i = 1; i < numDeItens; i++) {
        if(matriz[i][0] > maior && matriz[i][0] < pesoMaximo) {
            if(verificaSeTaNaMochila(i, indexBloqueado)) {
                maior = matriz[i][0];
                index = i;
            }
        }
    }
    return index;
}



int retornaMelhorItem(int** matriz, int numDeItens, int pesoMaximo, int* pesoVetor, vector<int> indexVetor) {
    int peso, valor, index = retornaIndexDoMaiorPeso(matriz, numDeItens, pesoMaximo, indexVetor);
    int **matrizNova;

    peso = matriz[index][weigth];
    valor = matriz[index][value];

    while(peso + *pesoVetor > pesoMaximo) {
        indexVetor.push_back(index);
        index = retornaIndexDoMaiorPeso(matriz, numDeItens, pesoMaximo, indexVetor);
        peso = matriz[index][weigth];
        valor = matriz[index][value];
    }

    for(int i = 0; i < numDeItens; i++) {
        if(matriz[i][0] < peso && matriz[i][1] > valor && (matriz[i][0] + *pesoVetor) < pesoMaximo) {
            if(verificaSeTaNaMochila(i, indexVetor)) {
                index = i;
                peso = matriz[index][weigth];
                valor = matriz[index][value];
            }
        }
    } 
    if(verificaSeTaNaMochila(index, indexVetor))
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
    int pesoVetor = 0, y = 0;
    int numDeItensNovo = numDeItens;
    vector<int> indexVetor;

    indexVetor.push_back(retornaMelhorItem(matriz, numDeItens, pesoMaximo, &pesoVetor, indexVetor));
    while(pesoVetor < pesoMaximo && y < numDeItens) {
        int index = retornaMelhorItem(matriz, numDeItens, pesoMaximo, &pesoVetor, indexVetor);
        if(verificaSeTaNaMochila(index, indexVetor))
            indexVetor.push_back(index);
        y++;
    }
    for(int x = 0; x < indexVetor.size(); x++) {
        int index = indexVetor[x];
        printf("Peso: %d Valor:%d Index: %d\n", matriz[index][weigth], matriz[index][value], index);
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