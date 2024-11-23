#include "planificador.h"

void planificador(const string& procesosPathStr, int cantidadCores, const string& resultadosPathStr) {
    // Verificar la existencia del archivo de procesos
    ifstream file(procesosPathStr);
    if (!file.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo de procesos en " << procesosPathStr << endl;
        return;
    }

    // Abrir el archivo de resultados en modo "agregar"
    ofstream resultadosFile(resultadosPathStr, ios::app);
    if (!resultadosFile.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo de resultados en " << resultadosPathStr << endl;
        return;
    }

    string line;
    int coreId = 0;

    while (getline(file, line)) {
        // Mostrar la línea antes de validarla para depuración
        cout << "Procesando línea: " << line << endl;

        if (!validarFormatoMensaje(line)) {
            cerr << "ERROR: Línea mal formada: " << line << endl;
            continue; // Ignorar línea y seguir con la siguiente
        }

        // Formatear el mensaje
        string mensaje = "(" + to_string(coreId) + ":" + line + ")";
        cout << "Mensaje válido, enviando a DISTRIBUIDOR: " << mensaje << endl;

        // Preparar el comando para ejecutar el distribuidor
        string command = "./src/distribuidor/main '" + mensaje + "' >> assets/resultados.txt";
        cout << "Ejecutando comando: " << command << endl;

        if (access("./src/distribuidor/main", X_OK) == -1) {
            cerr << "ERROR: No se encontró el ejecutable 'main' (distribuidor).\n";
            break;
        }
    
        int result = system(command.c_str());
        if (result == 0) {
            // No es necesario leer el archivo 'resultados.txt' ya que la salida ya está allí
            cout << "Resultado del distribuidor guardado en assets/resultados.txt" << endl;
        } else {
            cerr << "ERROR: Falló la ejecución del distribuidor.\n";
        }

        coreId = (coreId + 1) % cantidadCores;
    }

    file.close();
    resultadosFile.close();

    cout << "Planificación completada. Resultados guardados en: " << resultadosPathStr << "\n";
    cout << "Presione una tecla para continuar..." << endl;
    cin.get();
}

bool validarFormatoMensaje(const string& mensaje) {    // Validación mejorada: La línea debe seguir el formato: <ID>;<operación>;<valores>

    // Verificar si la línea tiene al menos tres partes separadas por punto y coma
    size_t firstSemicolon = mensaje.find(';');
    if (firstSemicolon == string::npos) return false; // No se encontró el primer ';'
    
    size_t secondSemicolon = mensaje.find(';', firstSemicolon + 1);
    if (secondSemicolon == string::npos) return false; // No se encontró el segundo ';'

    // Comprobar si la última parte tiene algún valor después del segundo ';'
    string valuesPart = mensaje.substr(secondSemicolon + 1);
    if (valuesPart.empty()) return false; // La parte de valores no puede estar vacía

    // Validar que los valores estén separados por coma
    if (valuesPart.find(',') == string::npos) return false; // Los valores deben estar separados por ','

    return true; // La línea es válida si pasa todas las comprobaciones
}
