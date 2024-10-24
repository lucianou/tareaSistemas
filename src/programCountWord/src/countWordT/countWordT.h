#ifndef COUNTWORDT_H
#define COUNTWORDT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>
#include <atomic>
#include <set>
#include <filesystem>
#include <sstream>


namespace fs = std::filesystem;
using namespace std;

bool menuCWT( string extension, string pathEntrada, string pathSalida, string cantidadThreadsStr, string mapPath, string stopPath);
vector<string> cargarArchivos(const string& directorio, const string& extension, string mapPath);   // funcion para cargar archivos
void crearMap(string extension, string entradaPath, string mapPath, vector<string> archivos);
void contarPalabrasEnArchivo(const string& archivo, const string& pathSalida, string extension);
void countWordThreads(const vector<string>& archivos, int cantidadThreads, const string& pathSalida, string extension);
void procesarArchivos(const string& inputPath, const string& outputPath, const string& extension, int cantidadThreads, string mapPath, string stopPath);
string limpiarPalabra(const string& palabra);
set<string> leerPalabras(const string& archivoPalabras);
void eliminarPalabras(const string& archivoObjetivo, const set<string>& palabrasAEliminar);
#endif 