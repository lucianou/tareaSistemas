#include "buscador.h"

map<string, string> cargarMapaArchivos(const string& ruta) {
    map<string, string> mapa;
    ifstream archivo(ruta);
    string clave, valor;
    if (archivo.is_open()) {
        while (archivo >> clave >> valor) {
            mapa[clave] = valor;
        }
        archivo.close();
    } else {
        cerr << "Error al abrir el archivo de MAPA_ARCHIVOS\n";
    }
    return mapa;
}

// Función para enviar mensajes a CACHE y MOTOR DE BÚSQUEDA
void enviarMensaje(const string& destino, const string& mensaje) {
    cout << "Enviando mensaje a " << destino << ": " << mensaje << endl;
    // Aquí puedes implementar la lógica para enviar el mensaje al proceso correspondiente
}
