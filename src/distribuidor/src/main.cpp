#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <string>
#include "distribuidor.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "ERROR: No se proporcionó el mensaje desde PLANIFICADOR." << endl;
        return 1;
    }

    string mensaje(argv[1]);
    int coreId;
    string operacion;
    double num1, num2;

    // Extraer datos del mensaje
    stringstream ss(mensaje);
    char delimiter;
    ss >> delimiter >> coreId >> delimiter >> operacion >> delimiter >> num1 >> delimiter >> num2;

    // Ejecutar el CORE correspondiente
    string command = "./core " + operacion + " " + to_string(num1) + " " + to_string(num2);
    string resultado = to_string(system(command.c_str()));

    // Guardar el resultado en el archivo RESULTADOS
    ofstream resultados("resultados.txt", ios::app);
    resultados << mensaje << "=>" << resultado << endl;
    resultados.close();

    return 0;
}