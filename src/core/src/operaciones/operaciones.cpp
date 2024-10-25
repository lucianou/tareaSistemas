#include "core.h"

double calcular(const string &operacion, double num1, double num2) {
    if (operacion == "suma") {
        return num1 + num2;
    } else if (operacion == "resta") {
        return num1 - num2;
    } else if (operacion == "multiplicacion") {
        return num1 * num2;
    } else if (operacion == "division") {
        return num2 != 0 ? num1 / num2 : 0;
    }
    cerr << "Operación no válida: " << operacion << endl;
    return 0;
}