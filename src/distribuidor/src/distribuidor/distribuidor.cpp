#include "distribuidor.h"
void distribuidor(string mensaje) {
    cout << "Distribuyendo mensaje: " << mensaje << endl;


    // Simulamos que se guarda el mensaje en un archivo de resultados.
    ofstream file("assets/resultados.txt", ios::app);
    if (file) {
        file << mensaje << endl;
        cout << "Mensaje guardado en el archivo de resultados." << endl;
    } else {
        cerr << "ERROR: No se pudo abrir el archivo de resultados." << endl;
    }
}
