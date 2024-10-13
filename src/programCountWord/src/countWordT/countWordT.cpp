#include "countWordT.h"

void menuCWT(){
    int opcion;

    while (true) {
        cout << "------- [Programa contador de palabras] -------\n\n";
        cout << "------------------ [Threads] ------------------\n\n";
        cout << "(0) Salir\n";
        cout << "(1) Extensión del archivo a procesar\n";
        cout << "(2) Path de carpeta de entrada\n";
        cout << "(3) Path de carpeta de salida\n";
        cout << "(4) Procesar\n";
        cout << "Seleccione la opción:";
        cin >> opcion;
        cout << "\n";
        cout << "-----------------------------------------------\n\n";

        if (opcion == 1) {
            // solicitar extension
        } else if (opcion == 2) {
            // solicitar Path de carpeta input
        } else if (opcion == 3) {
            // solicitar Path de carpeta output
        } else if (opcion == 4) {
           // procesar archivos
        } else if (opcion == 0) {
            return;
        } else {
            cerr << "Opción no válida. Intente nuevamente.\n";
        }
    }
}

void countWordThreads(const vector<string>& archivos, int cantidadThreads) {
    // Contar palabras con threads
}

vector<string> cargarArchivos(const string& directorio, const string& extension) {
    vector<string> archivos;
    // Cargar archivos con extension
    return archivos;
}