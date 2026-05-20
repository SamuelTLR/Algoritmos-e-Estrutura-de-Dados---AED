#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define SUCCESS 0

typedef struct TipoCelula *TipoApontador;

typedef int TipoChave;

typedef struct TipoItem {
    TipoChave chave;
} TipoItem;

typedef struct TipoCelula {
    TipoItem item;
    TipoApontador prox;
} TipoCelula;

typedef struct TipoFila {
    TipoApontador frente, tras;
} TipoFila;

void FFVazia(TipoFila *Fila) {
    Fila->frente = (TipoApontador) malloc(sizeof(TipoCelula));
    Fila->tras = Fila->frente;
    Fila->frente->prox = NULL;
}

int Vazia(TipoFila Fila) {
    return (Fila.frente == Fila.tras);
}

void Enfileira(TipoItem x, TipoFila *Fila) {
    Fila->tras->prox = (TipoApontador) malloc(sizeof(TipoCelula));
    Fila->tras = Fila->tras->prox;
    Fila->tras->item = x;
    Fila->tras->prox = NULL;
}

void Desenfileira(TipoFila *Fila, TipoItem *Item) {
    TipoApontador q;
    if(Vazia(*Fila)) {
        printf("Erro fila deve estar vazia\n");
        return;
    }
    q = Fila->frente;
    Fila->frente = Fila->frente->prox;
    *Item = Fila->frente->item;
    free(q);
}

void Imprime(TipoFila Fila) {
    TipoApontador Aux;
    Aux = Fila.frente->prox;
    while(Aux != NULL) {
        printf("%d\n", Aux->item.chave);
        Aux = Aux->prox;
    }
}

void AumentarPrioridade(TipoApontador p, TipoFila *Fila) {
    TipoApontador aux = Fila->frente;
    while(aux != NULL) {
        if(aux->prox == p) {
            Fila->frente->prox = p;
            aux->prox = aux->prox->prox;
        }
        aux = aux->prox;
    }
}