#include <stdio.h>
#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

#define SUCCESS 0

// Funções do C++
// cin >> codigo; Para no primeiro espaço
// cin.ignore(); pega o \n
// std::replace(texto.begin(), texto.end(), ' ', '#');

const string alfabeto = "abcdefghijklmnopqrstuvwxyz";

int findAlphabetIndex(char c) {
    for(int x = 0; x < 26; x++) {
        if(tolower(c) == alfabeto.at(x))
        return x;
    }
    return 0;
}

void rotate5LettersNext(string codigo, vector<char>& codigoCriptografado) {
    for(int i = 0; i < codigo.length(); i++) {
        int x = findAlphabetIndex(codigo[i]);
        
        if(tolower(codigo[i]) == tolower(alfabeto.at(x)))
            if(isupper(codigo[i]))
                codigoCriptografado.push_back(toupper(alfabeto.at((x + 5) % 26)));
            else 
                codigoCriptografado.push_back(alfabeto.at((x + 5) % 26));
        else if(codigo[i] == ' ') 
            codigoCriptografado.push_back('#');
    }
}

string rotate5LettersNext(string codigo) {
    string codigoDecodificado = "";
    for(int i = 0; i < codigo.length(); i++) {
        int x = findAlphabetIndex(codigo[i]);
        
        if(tolower(codigo[i]) == tolower(alfabeto.at(x))) {
            //printf("%d", &x);
            if(isupper(codigo[i]))
                codigoDecodificado += toupper(alfabeto.at((x - 5 + 26) % 26));
            else 
                codigoDecodificado += alfabeto.at((x - 5 + 26) % 26);
        }
        else if(codigo[i] == '#') 
            codigoDecodificado += ' ';
    }
    return codigoDecodificado;
}

void separateBy2Letters(vector<char>& codigoCripto) {
    string texto = "";
    for(int i = 0; i < codigoCripto.size(); i++) {
        if((i-2) % 2 == 0 && (i-2) >= 0) {
            texto += '-';
            texto += codigoCripto.at(i);
        } else {
            texto += codigoCripto.at(i);
        }
        codigoCripto.at(i) = texto[i];
    }
    int i = codigoCripto.size();
    int tamanho = texto.length();
    for(i; i < tamanho; i++)
        codigoCripto.push_back(texto[i]);
}

string separateBy2Letters(string codigoCripto) {
    string texto = "";
    for(int i = 0; i < codigoCripto.size(); i++) {
        if((i-2) % 2 == 0 && (i-2) >= 0) {
            texto += '-';
            texto += codigoCripto.at(i);
        } else {
            texto += codigoCripto.at(i);
        }
        codigoCripto.at(i) = texto[i];
    }
    int i = codigoCripto.size();
    int tamanho = texto.length();
    for(i; i < tamanho; i++)
        codigoCripto.push_back(texto[i]);

    return codigoCripto;
}

void reflectEachPair(vector<char>& codigoCripto) {
    char aux = 'a';
    for(int i = 0; i < codigoCripto.size() - 1; i++) {
        if(codigoCripto.at(i + 1) == '-') {
            codigoCripto.at(i - 1) = codigoCripto.at(i);
            codigoCripto.at(i) = aux; 
        }
        else if(i == codigoCripto.size() - 2) {
            if(codigoCripto.at(i) != '-') {
                aux = codigoCripto.at(i);
                codigoCripto.at(i) = codigoCripto.at(i + 1);
                codigoCripto.at(i + 1) = aux;
            }
        }
        aux = codigoCripto.at(i);
    }
}

string reflectEachPair(string codigoCripto) {
    char aux = 'a';
    for(int i = 0; i < codigoCripto.size() - 1; i++) {
        if(codigoCripto.at(i + 1) == '-') {
            codigoCripto.at(i - 1) = codigoCripto.at(i);
            codigoCripto.at(i) = aux; 
        }
        else if(i == codigoCripto.size() - 2) {
            if(codigoCripto.at(i) != '-') {
                aux = codigoCripto.at(i);
                codigoCripto.at(i) = codigoCripto.at(i + 1);
                codigoCripto.at(i + 1) = aux;
            }
        }
        aux = codigoCripto.at(i);
    }
    return codigoCripto;
}

void tradeLastPairToFirstPair(vector<char>& codigoCripto) {
    char a, b;
    a = codigoCripto.at(0);
    b = codigoCripto.at(1);
    codigoCripto.at(0) = codigoCripto.at(codigoCripto.size() - 2);
    codigoCripto.at(1) = codigoCripto.at(codigoCripto.size() - 1);
    codigoCripto.at(codigoCripto.size() - 2) = a;
    codigoCripto.at(codigoCripto.size() - 1) = b;
}

string tradeLastPairToFirstPair(string codigoCripto) {
    char a, b, c;
    int tamanho = codigoCripto.size();
    int x = 0, d = 0;
    for(int i = 0; i < tamanho / 2; i++) {
        c = codigoCripto.at(i);
        if(x % 2 == 0) {
            a = codigoCripto.at(i);
            b = codigoCripto.at(i + 1);
            codigoCripto.at(i) = codigoCripto.at(tamanho - i - 2);
            codigoCripto.at(i + 1) = codigoCripto.at(tamanho - i - 1);
            codigoCripto.at(tamanho - i - 2) = a;
            codigoCripto.at(tamanho - i - 1) = b;
            x++;
        }
        else if(codigoCripto.at(i) == '-') {
            d++;
        }
        if(d % 2 == 0 && d != 0) {
            x++;
            d = 0;
        }
            
    }
    
    return codigoCripto;
}

string eraseHifen(string codigoCripto) {
    string textoSemHifen = "";
    for(int i = 0; i < codigoCripto.size(); i++) 
    {
        if(codigoCripto.at(i) != '-') {
            textoSemHifen += codigoCripto.at(i);
        }
    }
    return textoSemHifen;
}

int main () {
    string codigo = "tinhkn#ftyH#y#wfxfitufjxmsfk#jrqjzjytrhjr#fwfiknxji#v#sjx#nhjy#w#f#jsju#t#xjcjjih#wkfw#F";
    cout << "\n";
    //getline(cin, codigo);
    vector<char> codigoCriptografado;

    for (char c : codigo) {
        cout << c;
    }
    cout << "\n\n";

    codigo = separateBy2Letters(codigo);
    for (char c : codigo) {
        cout << c;
    }
    cout << "\n\n";

    codigo = tradeLastPairToFirstPair(codigo);
    for (char c : codigo) {
        cout << c;
    }
    cout << "\n\n";

    codigo = reflectEachPair(codigo);
    for (char c : codigo) {
        cout << c;
    }
    cout << "\n\n";

    codigo = eraseHifen(codigo);
    for (char c : codigo) {
        cout << c;
    }
    cout << "\n\n";

   
    codigo = rotate5LettersNext(codigo);
    for (char c : codigo) {
        cout << c;
    }
    cout << "\n\n";
   
    return SUCCESS;
}