#ifndef COUNTWORD_H
#define COUNTWORD_H
#include <iostream>
#include <filesystem>
#include <iostream>
#include <filesystem>
#include <map>        // Agregar map
#include <fstream>    // Agregar ifstream
#include <algorithm>  // Para usar transform (para convertir a minúsculas)

namespace fs = std::filesystem;
using namespace std;

map<string, int> contarPalabras(const string& archivo);

#endif