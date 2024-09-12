#ifndef COUNTWORD_H
#define COUNTWORD_H
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <filesystem>
#include <algorithm>    // Para std::transform
#include <cctype>       // Para std::tolower
#include <unistd.h>  // Para getpid()

using namespace std;

void menuContarPalabras();
void solicitarExtension(string &extension);
void solicitarPathCarpeta(string &inputPath);
void solicitarPathSalida(string &outputPath);
map<string, int> contarPalabras(const string& archivo);
void procesarArchivos(const string& extension, const string& inputPath, const string& outputPath);

#endif