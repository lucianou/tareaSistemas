#include "readFile.h"

// Función para contar la frecuencia de cada palabra en un archivo
map<string, int> contarPalabras(const string& archivo) {
    ifstream file(archivo);                 
    map<string, int> conteoPalabras;      
    string palabra;                         

    if (!file.is_open()) {                  // Comprobar si el archivo se abrió correctamente
        cerr << "No se pudo abrir el archivo.\n";
        return conteoPalabras;              // Devolver el mapa vacío
    }

    while (file >> palabra) {                                                   // Leer cada palabra del archivo
        transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);  // Convertir la palabra a minúsculas
        conteoPalabras[palabra]++;  
    }
    file.close(); 
    return conteoPalabras; 
}
