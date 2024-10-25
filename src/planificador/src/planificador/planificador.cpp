#include "planificador.h"

void planificador() {
    string procesosPath = getenv("PROCESOS") ? getenv("PROCESOS") : "procesos.txt";

    ifstream file(procesosPath);
    if (!file) {
        cerr << "ERROR: No se pudo abrir el archivo de procesos." << endl;
        return;
    }

    int coreId = 0; 
    string line;

    while (getline(file, line)) {
        string mensaje = "(" + to_string(coreId) + ":" + line + ")";
        cout << "Enviando mensaje a DISTRIBUIDOR: " << mensaje << endl;

        // Enviar el mensaje al DISTRIBUIDOR (Ejemplo usando system)
        string command = "./distribuidor '" + mensaje + "'";
        system(command.c_str());

        // Alternar entre los COREs disponibles
        coreId = (coreId + 1) % 2;
    }

    file.close();
    cout << "Ruta de archivo de resultados: resultados.txt" << endl;
    cout << "Presione una tecla para continuar..." << endl;
    cin.get();     
}