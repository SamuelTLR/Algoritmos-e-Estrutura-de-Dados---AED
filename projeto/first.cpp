#include <iostream>
#include <stdlib.h>

#define SUCCESS 0
#define MAX 50
// 0 128 255 4 5 6 0 255
using namespace std;

int maquinaDeEstadosFinitos(int* numeros, int tamanho, int* impedimento) 
{
    int estadoAtual = 0, possivelImpedimento = 0;

    for(int i = 0; i < tamanho; i++) {
        if(numeros[i] == 0 && estadoAtual == 0) 
        {
                estadoAtual++;
                continue;
        }
        if(estadoAtual == 1) 
        {
            if(numeros[i] == 255) 
            {
                estadoAtual++;
            } 
            else if(numeros[i] != 0) 
            {
                estadoAtual = 0;
            }
            continue;
        }
        if(estadoAtual == 2) 
        {
            if(numeros[i] == 128) 
            {
                estadoAtual++;
            } 
            else if (numeros[i] != 255) 
            {
                estadoAtual = 0;
            }
            continue;
        }
        if(estadoAtual == 3) 
        {
            if(numeros[i] == 255) 
            {
                estadoAtual++;
            } 
            else if(numeros[i] != 128) 
            {
                estadoAtual--;
                possivelImpedimento = 1;
            }
            continue;
        }
        if(estadoAtual == 4) {
          if(numeros[i] == 0) {
            if(possivelImpedimento)
                *impedimento = 1;
            return 1;
          } else if(numeros[i] != 255) {
            estadoAtual = 2;
            possivelImpedimento = 1;
          }
          continue;
        }
        if(possivelImpedimento && numeros[i] == 0 || numeros[i] == 255) {
            estadoAtual = 1;
            possivelImpedimento = 0;
        }
    }

    return 0;
}

int main() 
{
    int num_perfis = 0, t_numeros = 1, numero, resultado, impedimento = 0, padraoEncontrado;
    int temPadrao = 0;

    cin >> num_perfis;
    for(int i = 0; i < num_perfis; i++) {
        cin >> t_numeros;
        int numeros[t_numeros];

        for(int i = 0; i < t_numeros; i++) 
        {
            cin >> numeros[i];
        }

        padraoEncontrado = maquinaDeEstadosFinitos(numeros, t_numeros, &impedimento);
        if(padraoEncontrado) {
            temPadrao = 1;
        }
    }

    if(temPadrao && !impedimento) 
        cout << "Resultado: Pista sem impedimento.\n";
    else if(temPadrao && impedimento)
        cout << "Resultado: Pista com impedimento.\n";
    else
        cout << "Resultado: Padrao nao encontrado.\n";
    return SUCCESS;
}