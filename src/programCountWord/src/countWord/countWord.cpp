#include "countWord.h"
#include "readFile.h"


void menuCWL() {
    string extension, inputPath, outputPath;
    bool extensionSet = false, inputPathSet = false, outputPathSet = false;
    int opcion;

    while (true) {
        cout << "------- [Programa contador de palabras] -------\n\n";
        cout << "pid: " << getpid() << "\n";
        cout << "(0) Salir\n";
        cout << "(1) Extensión de archivos a procesar (ej: txt)\n";
        cout << "(2) Path de carpeta a procesar (ej: /home/lvc/in)\n";
        cout << "(3) Path de carpeta que contendrá la respuesta del proceso (ej: /home/lvc/out)\n";
        cout << "(4) Procesar\n";
        cout << "Seleccione la opción:";
        cin >> opcion;
        cout << "\n";
        cout << "-----------------------------------------------\n\n";

        if (opcion == 1) {
            solicitarExtension(extension);
            extensionSet = !extension.empty();
        } else if (opcion == 2) {
            solicitarPathCarpeta(inputPath);
            inputPathSet = fs::exists(inputPath) && fs::is_directory(inputPath);
        } else if (opcion == 3) {
            solicitarPathSalida(outputPath);
            outputPathSet = fs::exists(outputPath);
        } else if (opcion == 4) {
            if (extensionSet && inputPathSet && outputPathSet) {
                procesarArchivos(extension, inputPath, outputPath);
                cout << "Procesando archivos...\n";
            } else {
                cerr << "Error: Debe ingresar todos los datos necesarios antes de procesar.\n";
            }
        } else if (opcion == 0) {
            return;
        } else {
            cerr << "Opción no válida. Intente nuevamente.\n";
        }
    }
}

// Validaciones
void solicitarExtension(string &extension) {
    cout << "Ingrese la extensión de los archivos a procesar (ej: txt): ";
    cin >> extension;
    if (extension.empty()) 
        cerr << "Error: Debe ingresar una extensión de archivo válida.\n";
}

void solicitarPathCarpeta(string &inputPath) {
    cout << "Ingrese el path de la carpeta a procesar (ej: /home/lvc/in): ";
    cin >> inputPath;
    if (!fs::exists(inputPath) || !fs::is_directory(inputPath))
        cerr << "Error: La carpeta de entrada no existe o no es un directorio.\n";
}

void solicitarPathSalida(string &outputPath) {
    cout << "Ingrese el path de la carpeta que contendrá la respuesta del proceso (ej: /home/lvc/out): ";
    cin >> outputPath;
    if (!fs::exists(outputPath)) {
        cout << "La carpeta de salida no existe. Se creará una nueva carpeta.\n";
        fs::create_directory(outputPath);
    }
}

void procesarArchivos(const string& extension, const string& inputPath, const string& outputPath) {
    for (const auto& entry : fs::directory_iterator(inputPath)) {
        if (entry.is_regular_file() && entry.path().extension() == "." + extension) {
            string archivoEntrada = entry.path().string();
            string archivoSalida = (fs::path(outputPath) / entry.path().stem()).string() + ".txt";
            
            map<string, int> conteoPalabras = contarPalabras(archivoEntrada);

            // Crear archivo de salida
            ofstream fileSalida(archivoSalida);
            if (!fileSalida.is_open()) {
                cerr << "Error: No se pudo crear el archivo de salida " << archivoSalida << ".\n";
                continue;
            }
            
            for (const auto& [palabra, cantidad] : conteoPalabras) {
                fileSalida << palabra << "; " << cantidad << "\n";
            }

            fileSalida.close();
            cout << "Archivo procesado: " << archivoSalida << "\n";
        }
    }
}