#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

struct Document {
    string name;
    int score;
};

void iniciarMotorBusqueda(string indexPath);
void cargarIndiceInvertido(const string& indexPath);
vector<Document> buscar(const vector<string>& queryWords);


#endif