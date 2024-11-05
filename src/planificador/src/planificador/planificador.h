#ifndef PLANIFICADOR_H
#define PLANIFICADOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unistd.h>

using namespace std;

void planificador();                                    // Función principal del planificador
bool validarFormatoMensaje(const string& mensaje);      // Función para validar el formato del mensaje
void loadEnv(const std::string& filename);              // Función para cargar las variables de entorno

#endif
