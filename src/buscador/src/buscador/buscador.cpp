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
void enviarMensaje(const string& destino, const string& mensaje, int clientSocket) {
    cout << "Enviando mensaje a " << destino << ": " << mensaje << endl;
    send(clientSocket, mensaje.c_str(), mensaje.length(), 0);

}

string enMinusculas(string frase){
    string fraseMin = "";
    for(char c: frase){
        fraseMin += tolower(c);
    }
    return fraseMin;
}




