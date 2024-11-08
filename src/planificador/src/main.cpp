#include "planificador.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) { // Ajusta según el número de argumentos que esperes
        cerr << "ERROR: Parámetros insuficientes en la ejecución de planificador.\n";
        return 1;
    }

    string procesos = argv[1];
    int cantidadCores = stoi(argv[2]);
    string resultados = argv[3];

    // Ahora puedes usar 'procesos', 'cantidadCores' y 'resultados' en el código.
    cout << "Ruta de PROCESOS: " << procesos << endl;
    cout << "CANTIDAD_CORES: " << cantidadCores << endl;
    cout << "Ruta de RESULTADOS: " << resultados << endl;

    cout << "-------- [Planificador de operaciones] --------\n\n";
    planificador(procesos, cantidadCores, resultados);
    cout << "-----------------------------------------------\n\n";
    return 0;
}
