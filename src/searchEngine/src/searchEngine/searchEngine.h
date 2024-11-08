#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

#define PORT 2021

using namespace std;

struct Document {
    string name; // Nombre del documento
    int score;   // Puntuación asociada
};

extern map<string, vector<Document>> invertedIndex;  // Índice invertido

void iniciarMotorBusqueda(const string& indexPath, int topK);
void cargarIndiceInvertido(const string& indexPath);
vector<Document> buscar(const vector<string>& queryWords, int topK);
void procesarConsulta(int client_socket, int topK);
void iniciarServidorBusqueda(int topK);

#endif 
