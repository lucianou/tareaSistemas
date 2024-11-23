#include "distribuidor.h"

void procesarMensaje(const string& mensaje) {
    // Abre el archivo de salida en modo append (agregar al final)
    ofstream archivo_salida("assets/resultados.txt", ios::app);
    if (!archivo_salida.is_open()) {
        cerr << "Error al abrir el archivo de salida." << endl;
        return;
    }

    // Crear el comando para ejecutar el proceso core
    string comando = "./src/core/main \"" + mensaje + "\"";

    // Ejecutar el proceso core usando popen() para capturar la salida
    FILE* fp = popen(comando.c_str(), "r");
    if (fp == nullptr) {
        cerr << "Error al ejecutar el proceso core" << endl;
        archivo_salida.close();
        return;
    }

    // Leer la salida del proceso core y escribirla en el archivo de salida
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
        archivo_salida << buffer;
    }

    fclose(fp);  // Cerrar el pipe

    // Cerrar el archivo de salida
    archivo_salida.close();

    cout << "Resultado procesado y guardado en 'resultados.txt'" << endl;
}
