#include "core.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cerr << "ERROR: No se proporcionaron suficientes argumentos." << endl;
        return 1;
    }

    string operacionStr = argv[1];
    double num1 = stod(argv[2]);
    double num2 = stod(argv[3]);

    // Convertir la operación de string a Operacion
    Operacion operacion = obtenerOperacion(operacionStr);

    // Realizar el cálculo
    double resultado = calcular(operacion, num1, num2);
    cout << resultado << endl;

    return 0;
}
