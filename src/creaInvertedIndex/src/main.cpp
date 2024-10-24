#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

struct PalabraInfo {
    string archivo;
    int veces;
};

map<string, int> leerArchivo(const string& nombreArchivo) {
    map<string, int> palabras;
    ifstream archivo(nombreArchivo);
    string linea;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string palabra;
            int frecuencia;
            if (getline(ss, palabra, ';') && ss >> frecuencia) {
                palabras[palabra] = frecuencia;
            }
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
    }

    return palabras;
}

void generarIndex(const string& pathIndex, const vector<string>& archivos, string extension, string pathSalida) {
    map<string, vector<PalabraInfo>> palabraDatos;

    for (const auto& archivo : archivos) {
        map<string, int> palabras = leerArchivo(archivo);
        for (const auto& [palabra, veces] : palabras) {
            palabraDatos[palabra].push_back({archivo, veces});
        }
    }

    ofstream salida(pathIndex);
    if (salida.is_open()) {
        for (const auto& [palabra, infos] : palabraDatos) {
            salida << palabra << ";";
            for (const auto& info : infos) {
                string nombre = info.archivo;
                nombre = nombre.erase(0, pathSalida.length()+1);
                nombre = nombre.erase(nombre.find("."), extension.length()+1);
                salida << "(" << nombre << "," << info.veces << ");";
            }
            salida << endl;
        }
        salida.close();
    } else {
        cerr << "No se pudo abrir el archivo de salida: " << pathIndex << endl;
    }
}

vector<string> cargarArchivos(const string& directorio, const string& extension) {
    vector<string> archivos;

    if (!fs::exists(directorio) || !fs::is_directory(directorio)) {
        cerr << "Error: El directorio no existe o no es un directorio válido.\n";
        return archivos;
    }

    // Iterar sobre los archivos en el directorio
    for (const auto& entry : fs::directory_iterator(directorio)) {
        if (entry.is_regular_file() && entry.path().extension() == "." + extension) {
            archivos.push_back(entry.path().string());
        }
    }
    /*
    cout << "Archivos cargados con extensión '" << extension << "':\n";
    for (const auto& archivo : archivos) {
        cout << " - " << archivo << '\n';
    }
    */
    return archivos;
}

int main(int argc, char *argv[]) {
    /*if (argc > 1) { 
        for(int i=1; i<argc; i++){
        string inputString = argv[i];
        cout << "String recibido: " << inputString << endl;
        }
    } else {
        cerr << "No se pasó ningún argumento al programa." << endl;
    }
    */
    vector<string> archivos = cargarArchivos(argv[1], "txt");
    
    generarIndex(argv[2], archivos, "txt", argv[1]);

    cout << "Archivo generado correctamente en la ruta: " << argv[2] << endl;

    return 0;
}