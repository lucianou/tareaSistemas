#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <cstring>
#include <unistd.h>
#include <string>
#include <fstream>

using namespace std;

enum class Operacion {
    SUMA,
    RESTA,
    MULTIPLICACION,
    DIVISION,
    INVALIDA  
}; 

double calcular(Operacion operacion, double num1, double num2);
Operacion obtenerOperacion(const string& operacionStr);

#endif