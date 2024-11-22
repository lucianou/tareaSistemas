#include "planificador.h"

void planificador(const string& procesosPathStr, int cantidadCores, const string& resultadosPathStr) {
    
    // Verificar la existencia del archivo de procesos
    ifstream file(procesosPathStr);
    if (!file.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo de procesos en " << procesosPathStr << endl;
        return;
    }

    string line;
    int coreId = 0;
     
        // Procesar cada línea del archivo de procesos
    while (getline(file, line)) {
        // Formatear el mensaje para cada línea del archivo de procesos
        string mensaje = "(" + to_string(coreId) + ":" + line + ")";  
        
        if (validarFormatoMensaje(mensaje)) {
            cout << "Mensaje válido, enviando a DISTRIBUIDOR: " << mensaje << endl;
            string command = "../../src/distribuidor/main " + mensaje;

            // Verificar si el programa "distribuidor" existe en la ruta actual
            if (access("./src/distribuidor/main", X_OK) == -1) {
                cerr << "ERROR: No se encontró el ejecutable 'distribuidor' en la ruta actual o no tiene permisos de ejecución.\n";
                return;
            }

            // Ejecutar el comando del distribuidor
            int result = system(command.c_str());
            if (result != 0) {
                cerr << "ERROR: Falló la ejecución del comando '" << command << "'.\n";
            }
        } else {
            cerr << "ERROR: Formato de mensaje no válido. Mensaje: " << mensaje << endl;
        }
        
        // Alternar entre los cores disponibles
        coreId = (coreId + 1) % cantidadCores;
    }

    file.close();

    // Guardar los resultados en el archivo especificado
    ofstream resultadosFile(resultadosPathStr);
    if (!resultadosFile.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo de resultados en " << resultadosPathStr << endl;
        return;
    }
    resultadosFile << "Resultados del planificador\n"; // Aquí puedes escribir los resultados deseados
    resultadosFile.close();

    cout << "Planificación completada. Resultados guardados en: " << resultadosPathStr << "\n";
    cout << "Presione una tecla para continuar..." << endl;
    cin.get();
}


bool validarFormatoMensaje(const string& mensaje) { // Validación básica: el mensaje debe tener paréntesis, dos puntos, punto y coma, y coma
    return mensaje[0] == '(' && mensaje.find(":") != string::npos &&
           mensaje.find(";") != string::npos && mensaje.find(",") != string::npos &&
           mensaje.back() == ')';
}

void loadEnv(const string &envPath = "./.env") {
    ifstream file(envPath);
    if (!file) {
        cerr << "ERROR: No se pudo abrir el archivo de configuración .env." << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        auto delimiterPos = line.find("=");
        if (delimiterPos != string::npos) {
            string key = line.substr(0, delimiterPos);
            string value = line.substr(delimiterPos + 1);
            setenv(key.c_str(), value.c_str(), 1);  // Setea variables de entorno
        }
    }
    file.close();
}
