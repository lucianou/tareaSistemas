#include "core.h"

// Función para realizar operaciones matemáticas
double realizar_operacion(const string& operacion, double num1, double num2) {
    if (operacion == "suma") {
        return num1 + num2;
    } else if (operacion == "resta") {
        return num1 - num2;
    } else if (operacion == "multiplicacion") {
        return num1 * num2;
    } else if (operacion == "division") {
        if (num2 != 0) {
            return num1 / num2;
        } else {
            cerr << "Error: División por cero" << endl;
            return 0;
        }
    } else {
        cerr << "Operación no soportada" << endl;
        return 0;
    }
}

// Función que procesa el mensaje recibido
void realizar_calculo(const string& mensaje) {
    stringstream ss(mensaje);
    string id, operacion, valores;
    double num1, num2;

    // Extraemos los componentes del mensaje
    getline(ss, id, ';');
    getline(ss, operacion, ';');
    getline(ss, valores, ';');

    // Convertimos los valores a números
    stringstream valStream(valores);
    char coma;  // Para leer la coma entre los dos números
    valStream >> num1 >> coma >> num2;

    // Realizamos la operación
    double resultado = realizar_operacion(operacion, num1, num2);

    // Formateamos y mostramos el resultado
    cout << id << ";" << operacion << ";" << num1 << "," << num2 << " => " << resultado << endl;
}
