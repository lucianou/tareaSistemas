#include "cache.h"

int main(int argc, char *argv[]) {
    if (argc < 2) { 
        cerr << "ERROR: Parámetros insuficientes en la ejecución de CACHÉ.\n";
        return 1;
    }
    int PORT = stoi(argv[2]);
    int memory_size = stoi(argv[1]);
    iniciarCache(memory_size, PORT);

    return 0;
}
