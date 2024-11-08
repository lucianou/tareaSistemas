#ifndef BUSCADOR_H
#define BUSCADOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // Para getenv
#include <map>

using namespace std;

map<string, string> cargarMapaArchivos(const string& ruta);         // Cargar el mapa de archivos
void enviarMensaje(const string& destino, const string& mensaje);   // Enviar mensaje a CACHE y MOTOR DE BÚSQUEDA

#endif