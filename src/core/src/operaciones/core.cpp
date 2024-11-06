#include "core.h"

// Función que convierte una cadena de texto a una operación del enum
Operacion obtenerOperacion(const string& operacionStr) {
    if (operacionStr == "suma") return Operacion::SUMA;
    if (operacionStr == "resta") return Operacion::RESTA;
    if (operacionStr == "multiplicacion") return Operacion::MULTIPLICACION;
    if (operacionStr == "division") return Operacion::DIVISION;
    return Operacion::INVALIDA;
}

// Función principal que realiza el cálculo según la operación
double calcular(Operacion operacion, double num1, double num2) {
    switch (operacion) {
        case Operacion::SUMA:
            return num1 + num2;
        case Operacion::RESTA:
            return num1 - num2;
        case Operacion::MULTIPLICACION:
            return num1 * num2;
        case Operacion::DIVISION:
            if (num2 != 0) {
                return num1 / num2;
            } else {
                cerr << "ERROR: División por cero." << endl;
                return 0;  // o algún valor de error
            }
        default:
            cerr << "ERROR: Operación no válida." << endl;
            return 0;
    }
}
