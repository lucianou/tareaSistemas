#include "core.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "ERROR: No se proporcionaron suficientes argumentos." << endl;
        return 1;
    }

    string mensaje = argv[1];  // Tomamos el mensaje del argumento pasado al programa

    // Realizamos el cálculo con el mensaje
    realizar_calculo(mensaje);

    return 0;
}
