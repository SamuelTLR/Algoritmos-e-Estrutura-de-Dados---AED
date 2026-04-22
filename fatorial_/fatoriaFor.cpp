#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;
#define tamanhoV 36000

int digits(int a) {
    if(a > 0) {
        return digits(a / 10) + 1;
    }
    else 
        return 0;
}

int divideNumero(int numero, int opcao) 
{
    int tamanho = digits(numero) - 1, aux, aux1 = (int) pow(10, tamanho);
    if(opcao) {
        aux = numero / aux1;
        return aux * aux1;
    }
    aux = numero % aux1;
    return aux;
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

int* soma(int *aux1, int*aux2, int t1, int t2) {
    int* resposta, t = t1;
    if(t1 < t2) 
        t = t2;

    resposta = new int[t1];

    for(int i = 0; i < t; i++) {
        if(i < t1 && i < t2)
        resposta[i] = aux1[i] + aux2[i];
        else if(i >= t1 && i < t2)
        resposta[i] = aux2[i];
        else if(i >= t2 && i < t1)
        resposta[i] = aux1[i];
        cout << resposta[i];
    }
    return resposta;
}

int fatorial(int a) {
    if(a > 1)
        return a*fatorial(a - 1);
    return 1;    
}



int main() {
    int numero = 10, *resposta, aux1, aux2, tamanho;
    int* aux1_vetor, *aux2_vetor;

    tamanho = digits(numero);
    if(tamanho >= 2) {
        aux1 = divideNumero(numero - 1, 1);
        aux2 = divideNumero(numero - 1, 0);

        aux1 = aux1 * numero;
        aux2 = aux2 * numero;

    } else {
        aux1 = fatorial(numero);
        aux2 = 0;
    }
    aux1_vetor = transformaEmVetor(aux1);
    aux2_vetor = transformaEmVetor(aux2);

    int t1 = digits(aux1), t2 = digits(aux2), t = 0;
    resposta = soma(aux1_vetor, aux2_vetor, t1, t2);

    if(t1 >= t2 && t < t1) {
        t = t1;
    }else if(t2 > t1 && t < t2)
        t = t2;

    cout << "Vetor:";
    for(int i = t - 1; i >= 0; i--) {
        cout << resposta[i];
    }
    

    return 0;
}