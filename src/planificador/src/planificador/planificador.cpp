#include "planificador.h"

void planificador() {
    string procesosPath = getenv("PROCESOS") ? getenv("PROCESOS") : "procesos.txt";
    cout << "Ruta de archivo de procesos: " << procesosPath << endl;

    ifstream file(procesosPath);
    if (!file) {
        cerr << "ERROR: No se pudo abrir el archivo de procesos." << endl;
        return;
    }

    int coreId = 0; 
    string line;

    while (getline(file, line)) {
        string mensaje = "(" + to_string(coreId) + ":" + line + ")";  
        
        if (validarFormatoMensaje(mensaje)) {
            cout << "Mensaje válido, enviando a DISTRIBUIDOR: " << mensaje << endl;
            string command = "./distribuidor '" + mensaje + "'";
            system(command.c_str());
        } else {
            cerr << "ERROR: Formato de mensaje no válido. Mensaje: " << mensaje << endl;
        }
        
        coreId = (coreId + 1) % 2;  // Alternar entre los COREs disponibles
    }

    file.close();
    cout << "Ruta de archivo de resultados: resultados.txt" << endl;
    cout << "Presione una tecla para continuar..." << endl;
    cin.get();     
}

bool validarFormatoMensaje(const string& mensaje) { // Validación básica: el mensaje debe tener paréntesis, dos puntos, punto y coma, y coma
    return mensaje[0] == '(' && mensaje.find(":") != string::npos &&
           mensaje.find(";") != string::npos && mensaje.find(",") != string::npos &&
           mensaje.back() == ')';
}

void loadEnv(const string& filename) {
    ifstream file(filename);
    if (!file) {
        file.open("../.env");  // Otra posible ruta
    }
    if (!file) {
        cerr << "ERROR: No se pudo abrir el archivo de configuración .env." << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        // Ignorar líneas en blanco o comentarios
        if (line.empty() || line[0] == '#') continue;

        // Buscar el delimitador '='
        size_t delimiterPos = line.find('=');
        if (delimiterPos != string::npos) {
            string key = line.substr(0, delimiterPos);
            string value = line.substr(delimiterPos + 1);

            // Establecer la variable de entorno
            setenv(key.c_str(), value.c_str(), 1); // '1' para sobrescribir si ya existe
        }
    }
}
