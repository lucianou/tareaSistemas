#include "cache.h"

int main(int argc, char *argv[]) {
    if (argc < 2) { 
        cerr << "ERROR: Parámetros insuficientes en la ejecución de planificador.\n";
        return 1;
    }
    int memory_size = stoi(argv[1]);
    iniciarCache(memory_size);

    return 0;
}
