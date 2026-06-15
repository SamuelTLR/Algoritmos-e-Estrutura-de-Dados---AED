#include <iostream>
#include <stdlib.h>

#define SUCCESS 0
#define MAX 50

using namespace std;

int maquinaDeEstadosFinitos(int* numeros, int tamanho) 
{
    int estadoAtual = 0;

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
                estadoAtual = 0;
            }
            continue;
        }
        if(estadoAtual == 4) {
          if(numeros[i] == 0) {
            return 1;
          } else if(numeros[i] != 255) {
            estadoAtual = 0;
          }
          continue;
        }
    }

    return 0;
}

int main() 
{
    int t_numeros = 1, numero, resultado;

    cin >> t_numeros;
    int numeros[t_numeros];

    for(int i = 0; i < t_numeros; i++) 
    {
        cin >> numeros[i];
    }

    if(maquinaDeEstadosFinitos(numeros, t_numeros)) 
        cout <<  "Resultado: Padrao encontrado.\n";
    else   
        cout << "Resultado: Padrao nao encontrado.\n";

    return SUCCESS;
}