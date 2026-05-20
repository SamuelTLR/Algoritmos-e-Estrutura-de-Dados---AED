#include <iostream>
#include <vector>
#include <fstream>
#include <ctype.h>

#define SUCCESS 0
#define INICIOARRANJO 1
#define MAXTAM 1000

using namespace std;

typedef int TipoApontador;
typedef int TipoChave;

typedef struct { 
  int posicao;
} TipoItemPosicao;

typedef struct {
  TipoItemPosicao Item[MAXTAM];
  TipoApontador Primeiro, Ultimo;
} TipoListaPosicao;

typedef struct {
  string palavra;
  vector<int> ocorrencias;
} TipoItem;

typedef struct {
  TipoItem Item[MAXTAM];
  TipoApontador Primeiro, Ultimo;
} TipoLista;

void FLVazia(TipoLista *Lista) {
  Lista->Primeiro = INICIOARRANJO; Lista->Ultimo = Lista->Primeiro;
}

int Vazia(TipoLista Lista) {
  return (Lista.Primeiro == Lista.Ultimo);
}

void LPVazia(TipoListaPosicao *Lista) {
  Lista->Primeiro = INICIOARRANJO; Lista->Ultimo = Lista->Primeiro;
}

void Insere(TipoItem x, TipoLista* Lista) {
  if(Lista->Ultimo > MAXTAM) 
    cout << "Lista está cheia//n";
  else {
    if(!Vazia(*Lista)) {
      for(int aux = Lista->Primeiro - 1; aux <= (Lista->Ultimo - 2); aux++) 
        if(Lista->Item[aux].palavra == x.palavra) {
          Lista->Item[aux].ocorrencias.push_back(x.ocorrencias.at(0));
          return;
        } 
    } 
    Lista->Item[Lista->Ultimo - 1] = x;
    Lista->Ultimo++;  
  }
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item) {
  int Aux;
  if(Vazia(*Lista) || p >= Lista->Ultimo) {
    cout << "Erro posição não existe//n";
    return;
  }
  *Item = Lista->Item[p - 1];
  Lista->Ultimo--;
  for(Aux = p; Aux < Lista->Ultimo; Aux++) 
    Lista->Item[Aux - 1] = Lista->Item[Aux];
}


void Imprime(TipoLista Lista, string palavraPadrao) {
  int Aux;
  vector<int> ocorrencias;
  for(Aux = Lista.Primeiro - 1; Aux <= (Lista.Ultimo - 2); Aux++) {
    cout << Lista.Item[Aux].palavra << " ";
    for(int i = 0; i < Lista.Item[Aux].ocorrencias.size(); i++) {
      cout << Lista.Item[Aux].ocorrencias.at(i) << " ";
    }
    if(Lista.Item[Aux].palavra == palavraPadrao) {
      ocorrencias = Lista.Item[Aux].ocorrencias;
    }
    cout << "\n";
  }
  cout << "\nOcorrências do padrão \"" << palavraPadrao << "\":";
  for(int i = 0; i < ocorrencias.size(); i++) 
    cout << ocorrencias[i] << " ";
}

void calculaNovoIndex(string palavra, int* index) {
  *index = palavra.length() + *index + 1;
}

string limpaPalavra(string palavra) {
  string palavraLimpa;
  for(int i = 0; i < palavra.length(); i++) {
    if(isalpha(palavra[i])) 
      palavraLimpa += tolower(palavra[i]);
  }
  return palavraLimpa;
}

int main() {
  string nomeDoArquivo = "arquivo.txt", palavraPadrao, texto, palavra;
  TipoLista lista;
  int index = 1;

  FLVazia(&lista);
  ifstream arquivoLeitura(nomeDoArquivo);

  if(!arquivoLeitura.is_open()) {
    cout << "Erro ao abrir o arquivo!" << endl;
    return 1;
  }

  getline(arquivoLeitura, palavraPadrao);

  while(arquivoLeitura >> palavra) {
    TipoItem x;
    x.palavra = limpaPalavra(palavra);
    x.ocorrencias.push_back(index);
    Insere(x, &lista);
    calculaNovoIndex(palavra, &index);
  }

  Imprime(lista, palavraPadrao);
  arquivoLeitura.close();
  return 0;
}