#ifndef PLANIFICADOR_H
#define PLANIFICADOR_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <string>
#include <fstream>

using namespace std;

void planificador(const string& procesosPathStr, int cantidadCores, const string& resultadosPathStr);                                    // Función principal del planificador
bool validarFormatoMensaje(const string& mensaje);      // Función para validar el formato del mensaje
void loadEnv(const std::string& filename);              // Función para cargar las variables de entorno

#endif
