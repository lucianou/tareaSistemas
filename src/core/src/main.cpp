#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <string>
#include "operaciones.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cerr << "ERROR: No se proporcionaron suficientes argumentos." << endl;
        return 1;
    }

    string operacion = argv[1];
    double num1 = stod(argv[2]);
    double num2 = stod(argv[3]);

    double resultado = calcular(operacion, num1, num2);
    cout << resultado << endl;

    return 0;
}