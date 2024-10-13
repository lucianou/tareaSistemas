#ifndef COUNTWORDL_H
#define COUNTWORDL_H

#include <iostream>
#include <filesystem>
#include <unistd.h>  // Para getpid()
#include <map>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

void menuCWL();                 
void solicitarExtension(string &extension);
void solicitarPathCarpeta(string &inputPath);
void solicitarPathSalida(string &outputPath);
void procesarArchivos(const string& extension, const string& inputPath, const string& outputPath);

#endif 