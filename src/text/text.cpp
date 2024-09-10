#include <string>
#include <algorithm>
#include <iostream>
#include "text.h"

using namespace std;

bool palindromo(string frase){
    bool esPal = true;
    string fraseLimpia = limpiaCadena(frase);
    string reversed(fraseLimpia.rbegin(), fraseLimpia.rend());
    long unsigned int i = 0;
    while(esPal && i < fraseLimpia.size()){
        if(tolower(fraseLimpia[i]) != tolower(reversed[i])){
            esPal = false;
            cout << "\nLa frase: " << frase << ", no es palíndromo.\n\n";
            return esPal;
            }
        i++;
    }
    cout << "\nLa frase: " << frase << ", es palíndromo.\n\n";
    return esPal;
}

string limpiaCadena(string frase){
    string limpia;
    for(char c: frase){
        if(isalnum(c)) limpia += c;
    }
    return limpia;
}

int contarVocales(string frase){
    int numVoc = 0;
    string vocales = "aeiou";
    for(char v: vocales){
        numVoc += encontrarCaracter(v,frase);
    }
    cout << "\nLa frase: " << frase << ", cuenta con " << numVoc << " vocales. \n\n";
    return numVoc;
}

int contarLetras(string frase){
    int numLet = 0;
    string letras = "abcdefghijklmnñopqrstuvwxyz";
    for(char l: letras){
        numLet += encontrarCaracter(l,frase);
    }
    cout << "\nLa frase: " << frase << ", cuenta con " << numLet << " letras. \n\n";
    return numLet;
}

int encontrarCaracter(char c, string s){
    int contador = 0;
    for(char i : s){
        if(tolower(i) == c) contador++;
    }
    return contador;
}

bool esAlfanumerico(string s){
    for(char c: s){
        if(!isalnum(c)){
            return false;
        }
    }
    return true;
}

bool esAlfabeto(string s){
    for(char c: s){
        if(!isalpha(c)){
            return false;
        }
    }
    return true;
}