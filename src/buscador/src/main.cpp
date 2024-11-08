#include "buscador.h"

int main(int argc, char* argv[]) {
    if (argc < 3) { // Ajusta según el número de argumentos que esperes
        cerr << "ERROR: Parámetros insuficientes en la ejecución de planificador.\n";
        return 1;
    }

    if (!rutaMapa) {
        cerr << "Error: MAPA_ARCHIVOS no está configurado como variable de entorno.\n";
        return 1;
    }

    map<string, string> mapaArchivos = cargarMapaArchivos(rutaMapa);
    string fraseBusqueda;
    cout << "Ingrese la frase de búsqueda: ";
    getline(cin, fraseBusqueda);

    if (fraseBusqueda == "SALIR AHORA") {
        enviarMensaje("CACHE", "cerrar");
        enviarMensaje("MOTOR DE BÚSQUEDA", "cerrar");
        cout << "Cerrando el proceso BUSCADOR.\n";
        return 0;
    }

    cout << "Buscando en CACHE...\n";
    bool encontradoEnCache = false;  
    if (encontradoEnCache) {
        cout << "Resultado encontrado en CACHE: ..." << endl;
    } else {
        cout << "Resultado no encontrado en CACHE. Consultando MOTOR DE BÚSQUEDA...\n";
        enviarMensaje("MOTOR DE BÚSQUEDA", fraseBusqueda);
    }

    return 0;
}