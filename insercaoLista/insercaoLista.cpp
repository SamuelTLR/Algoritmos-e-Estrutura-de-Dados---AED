#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <fstream>
#include <sstream>

#define SUCCESS 0
#define MAXTAM 100

using namespace std;

typedef struct {
  int numero;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem item;
  TipoApontador prox;
} TipoCelula;

typedef struct 
{
  TipoApontador primeiro, ultimo;
} TipoLista;

void FLVazia(TipoLista *lista) {
  lista->primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
  lista->ultimo = lista->primeiro; 
  lista->primeiro->prox = NULL;
}

TipoLista* FListasVazia(int numeroDeListas) {
    TipoLista* listas = (TipoLista*) malloc(numeroDeListas * sizeof(TipoLista));
    for(int i = 0; i < numeroDeListas; i++) {
        FLVazia(&listas[i]);
    }
    return listas;
}

int Vazia(TipoLista lista) {
  return lista.primeiro == lista.ultimo;
}

void insere(TipoItem x, TipoLista *lista) {
  lista->ultimo->prox = (TipoApontador) malloc(sizeof(TipoCelula));
  lista->ultimo = lista->ultimo->prox; 
  lista->ultimo->item = x;
  lista->ultimo->prox = NULL;
}

void retira(TipoApontador p, TipoLista *Lista, TipoItem *Item) {
  TipoApontador q;
  if(Vazia(*Lista) || p == NULL || p->prox == NULL) {
    cout << "Erro: Lista vazia ou posição não existe\n";
    return;
  }
  q = p->prox;
  *Item = q->item; 
  p->prox = q->prox;
  if(p->prox == NULL) Lista->ultimo = p;
  free(q);
}

void insercao(TipoLista* listaFinal, TipoLista listas[], int numeroDeListas) {
  int terminou = 0, index;
  TipoApontador menor;

  while(terminou != numeroDeListas) {
    menor = NULL; 
    index = -1;
    terminou = 0;

    for(int i = 0; i < numeroDeListas; i++) {
      if(listas[i].primeiro->prox == NULL) {
        terminou++;
        continue;
      }

      TipoApontador x = listas[i].primeiro->prox;

      if(menor == NULL || menor->item.numero > x->item.numero)
      {
        menor = x;
        index = i;
      }
    }

    TipoItem x;
    if(menor != NULL && terminou != numeroDeListas) {
      insere(menor->item, listaFinal);
      retira(listas[index].primeiro, &listas[index], &x);
    }
  }
}


int main () {
  string nomeDoArquivo = "a.txt";
  
  int numeroDeListas;

  ifstream arquivo(nomeDoArquivo);

  if(!arquivo.is_open()) {
    cout << "Erro ao abrir arquivo!" << endl;
    return 1;
  }

  string linha;
  arquivo >> numeroDeListas;  arquivo.ignore();

  TipoLista *listas = FListasVazia(numeroDeListas), listaFinal;

  int numeroDeLinhas = 0;
  while(getline(arquivo, linha)) {
    stringstream fluxoLinha(linha);

    int numero, i = 0;
    while(fluxoLinha >> numero) {
      TipoItem x;
      x.numero = numero;
      insere(x, &listas[numeroDeLinhas]);
    }
    numeroDeLinhas++;
  }

  FLVazia(&listaFinal);
  insercao(&listaFinal, listas, numeroDeListas);

  cout << "Lista final: ";
  TipoApontador x = listaFinal.primeiro->prox;

  if(x != NULL)
  while(x->prox != NULL) {
    cout << x->item.numero << ",";
    x = x->prox;
  }
  cout << x->item.numero;
  arquivo.close();

  return SUCCESS;
}