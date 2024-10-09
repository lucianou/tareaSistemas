#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <filesystem>
#include <unistd.h>  // Para getpid()
#include <map>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

void mostrarMenuPCW(); // Función principal del programa contador de palabras
void solicitarExtension(string &extension);
void solicitarPathCarpeta(string &inputPath);
void solicitarPathSalida(string &outputPath);
void procesarArchivos(const string& extension, const string& inputPath, const string& outputPath);

#endif 