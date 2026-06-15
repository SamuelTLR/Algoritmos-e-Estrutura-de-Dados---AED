#include <iostream>
#include <vector>
#include <fstream>
#include <ctype.h>

#define SUCCESS 0
#define INICIOARRANJO 1
#define MAXTAM 100

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
  TipoListaPosicao ocorrencias;
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

int VaziaPosicao(TipoListaPosicao Lista) {
  return (Lista.Primeiro == Lista.Ultimo);
}

void InserePosicao(TipoItemPosicao x, TipoListaPosicao* Lista) {
  if(Lista->Ultimo > MAXTAM)
    cout << "Lista esta cheia\n";
    else {
      Lista->Item[Lista->Ultimo - 1] = x;
      Lista->Ultimo++;  
    }
}


void Insere(TipoItem x, TipoItemPosicao y, TipoLista* Lista) {
  if(Lista->Ultimo > MAXTAM) 
    cout << "Lista está cheia//n";
  else {
    if(!Vazia(*Lista)) {
      for(int aux = Lista->Primeiro - 1; aux <= (Lista->Ultimo - 2); aux++) 
        if(Lista->Item[aux].palavra == x.palavra) {
          InserePosicao(y, &Lista->Item[aux].ocorrencias);
          return;
        } 
    } 
    LPVazia(&x.ocorrencias);
    InserePosicao(y, &x.ocorrencias);
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


void Imprime(TipoLista Lista, TipoItem palavraPadrao) {
    int Aux;

    for(Aux = Lista.Primeiro - 1; Aux <= (Lista.Ultimo - 2); Aux++) {
        cout << Lista.Item[Aux].palavra << ": ";
        
        for(int i = Lista.Item[Aux].ocorrencias.Primeiro - 1; i <= (Lista.Item[Aux].ocorrencias.Ultimo - 2); i++) {
            cout << Lista.Item[Aux].ocorrencias.Item[i].posicao << " ";
        }
        cout << "\n";
    }

    cout << "\nOcorrências do padrão \"" << palavraPadrao.palavra << "\": ";
    for(int i = palavraPadrao.ocorrencias.Primeiro - 1; i <= (palavraPadrao.ocorrencias.Ultimo - 2); i++) {
        cout << palavraPadrao.ocorrencias.Item[i].posicao << " ";
    }
}

void ordenaAlfabeticamente(TipoLista *lista) {
  int ultimaPosicao = lista->Ultimo - 2;

  while(ultimaPosicao > 0) {
    for(int i = (lista->Primeiro - 1); i < ultimaPosicao; i++) {
      if(lista->Item[i].palavra > lista->Item[i + 1].palavra) {
        swap(lista->Item[i], lista->Item[i + 1]);
      }
    }
    ultimaPosicao--;
  }
}

string limpaPalavra(string palavra){
  string palavraLimpa = "";
  for(int i = 0; i < palavra.size(); i++) {
    if(isalpha(palavra[i]))
      palavraLimpa += tolower(palavra[i]);
  }
  return palavraLimpa;
}

TipoItem pesquisaBinaria(TipoLista lista, string palavraPadrao) {
  int inicio = lista.Primeiro - 1, fim = lista.Ultimo - 2;

  while (inicio <= fim) {
    int meio = inicio + (fim - inicio) / 2;


    if(lista.Item[meio].palavra == palavraPadrao) {
      return lista.Item[meio];
    }
    else if(lista.Item[meio].palavra > palavraPadrao) {
      fim = meio - 1;
    } else {
      inicio = meio + 1;
    }
  }

  TipoItem itemvazio;
  itemvazio.palavra = palavraPadrao;
  LPVazia(&itemvazio.ocorrencias);
  return itemvazio;
}


int main() {
  string nomeDoArquivo, palavraPadrao, texto, palavra;

  cout << "Digite o nome do arquivo: ";
  cin >> nomeDoArquivo;
  
  TipoLista* lista = new TipoLista(); 
  int index = 1;
  FLVazia(lista); 
  
  ifstream arquivoLeitura(nomeDoArquivo);
  if(!arquivoLeitura.is_open()) {
    cout << "Erro ao abrir o arquivo!" << endl;
    delete lista; 
    return 1;
  }

  getline(arquivoLeitura, palavraPadrao);
  palavraPadrao = limpaPalavra(palavraPadrao);
  getline(arquivoLeitura, texto);
  
  TipoItem x;
  TipoItemPosicao y;
  for(int i = 0; i < texto.size(); i++) {
    if(isalpha(texto[i])) {
        palavra += tolower(texto[i]);
    } else {
        if(!palavra.empty()) {
            x.palavra = palavra;
            y.posicao = i - palavra.size() + 1;
            Insere(x, y, lista); 
            palavra = "";
        }
    }
  }

  if(!palavra.empty()) {
      x.palavra = palavra;
      y.posicao = texto.size() - palavra.size() + 1;
      Insere(x, y, lista); 
  }

  ordenaAlfabeticamente(lista); 
  TipoItem itemPalavraPadrao = pesquisaBinaria(*lista, palavraPadrao);

  Imprime(*lista, itemPalavraPadrao); 
  arquivoLeitura.close();
  
  delete lista; 
  return 0;
}