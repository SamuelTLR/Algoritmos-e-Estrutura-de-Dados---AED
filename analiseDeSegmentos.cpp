#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

#define SUCCESS 0

void imprimeMatriz(int **matriz, int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++)
            printf("%d ", matriz[i][j]);
        printf("\n");
    }
}

int* alocaDinamicamenteVetor(int *vetor, int tamanho)
{
    vetor = (int *)realloc(vetor, tamanho * sizeof(int));
    return vetor;
}

int ** alocaDinamicamenteMatriz(int **matriz, int linhas, int colunas)
{
    matriz = (int **)realloc(matriz, linhas * sizeof(int *));
    for(int i = 0; i < linhas; i++) {
        matriz[i] = (int *)realloc(matriz[i], colunas * sizeof(int));
    }

    return matriz;
}

int ** numeroDeRepeticoes(int* vetor, int** matriz, int tamanho, int tamanhoMatriz) 
{
    int aux = 0, y = 0, aux2 = 0;
    for(int x = 0; x < tamanhoMatriz; x++) 
    {    
        aux = 0;
        for(int i = aux2; i < tamanho; i++) 
        {
            if(vetor[i] == matriz[1][x]) 
            {
                y = 1;
                aux++;
            } else if(y) 
                break;
        }
        y = 0;
        aux2 += aux;
        matriz[1][x] = aux;
    }
    return matriz;
}

void identificaTiposDeSegmentos(int *vetor, int **matriz, int tamanho)
{
    int tamanhoMatriz = 0, novoSegmento = 0, tipoDeSegmento = 1;
    for (int i = 0; i < tamanho; i++)
    {
        if (vetor[i] == vetor[i - 1] && i != 0)
        {
            novoSegmento++;
        }
        
        if (novoSegmento == 0)
        {
            int y = 1;
            for(int x = 0; x < tamanhoMatriz; x++) {
                if(vetor[i] == matriz[1][x]) {
                    matriz[0][tamanhoMatriz] = matriz[0][x];
                    matriz[0][tamanhoMatriz] = matriz[0][x];
                    y--;
                }
            }
            if(y) {
                matriz[0][tamanhoMatriz] = tipoDeSegmento;
                matriz[1][tamanhoMatriz] = vetor[i]; 
                tipoDeSegmento++;
                y = 1;
            }
            tamanhoMatriz++;
            alocaDinamicamenteMatriz(matriz, 2, tamanhoMatriz);
        }
        novoSegmento = 0;
    }
    //imprimeMatriz(matriz, 2, tamanhoMatriz);
    matriz = numeroDeRepeticoes(vetor, matriz, tamanho, tamanhoMatriz);
    imprimeMatriz(matriz, 2, tamanhoMatriz);
}

int main()
{
    int *vetor = NULL, tamanho, **matriz = NULL;
    cin >> tamanho;
    vetor = alocaDinamicamenteVetor(vetor, tamanho);
    for (int i = 0; i < tamanho; i++)
    {
        cin >> vetor[i];
    }
    matriz = alocaDinamicamenteMatriz(matriz, 2, 2);
    identificaTiposDeSegmentos(vetor, matriz, tamanho);

    return SUCCESS;
}
