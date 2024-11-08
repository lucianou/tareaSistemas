#include "searchEngine.h"

int main(int argc, char *argv[]) {
    if (argc < 2) { 
        cerr << "ERROR: Parámetros insuficientes en la ejecución de searchEngine.\n";
        return 1;
    }
    string index = argv[1];
    
    iniciarMotorBusqueda(index);
    return 0;
}