#include "distribuidor.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Verifica si se proporcionó el mensaje como argumento
    if (argc < 2) {
        cerr << "ERROR: Se debe proporcionar un mensaje como argumento." << endl;
        return 1;
    }

    string mensaje = argv[1];  // Obtiene el mensaje del argumento pasado al programa

    // Procesa el mensaje
    procesarMensaje(mensaje);

    return 0;
}
