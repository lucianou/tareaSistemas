#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>

using namespace std;

vector<string> makeArrayThreads(string arrayThreads) {
    vector<string> threads;
    string threadString = "";
    for (int i = 0; i < arrayThreads.length(); i++) {
        if (arrayThreads[i] != ',')
            threadString += arrayThreads[i];
        else {
            threads.push_back(threadString);
            threadString = "";
        }
    }
    if (!threadString.empty()) {
        threads.push_back(threadString);
    }
    return threads;
}

bool verificaRep(int rep) {
    return rep >= 2;
}

void escribeTiempos(string pathArchivo, string threads, std::chrono::duration<double, std::milli> duracion, bool append = true) {
    ofstream archivo;
    
    if (append) {
        archivo.open(pathArchivo, std::ios::app); // Añadir al final
    } else {
        archivo.open(pathArchivo, std::ios::out); // Limpiar el archivo
        return;
    }

    if (archivo.is_open()) {
        archivo << threads << ", " << duracion.count() << " ms" << endl;
        archivo.close();
    } else {
        cerr << "Error al abrir el archivo para escribir.\n";
    }
}

int main(int argc, char* argv[]) {
    /*
    if (argc > 1) { 
        for (int i = 1; i < argc; i++) {
            string inputString = argv[i];
            cout << "String recibido: " << inputString << endl;
        }
    } else {
        cerr << "No se pasó ningún argumento al programa." << endl;
        return 0;
    }
    */

    vector<string> threads = makeArrayThreads(argv[4]);
    int rep = 0;
    if (verificaRep(stoi(argv[7]))) {
        rep = stoi(argv[7]);
    } else {
        cerr << "ERROR: variable de entorno REPETICIONES debe ser un número entero mayor o igual a 2." << endl;
        return 0;
    }

    escribeTiempos(string(argv[8]), "", std::chrono::milliseconds(0), false); 

    for (string thread : threads) {
        auto inicio = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < rep; i++) {
            string commandCountWord = "./src/programCountWord/main " + string(argv[1]) + " " + string(argv[2]) + " " + string(argv[3]) + " " + thread + " " + string(argv[5]) + " " + string(argv[6]) + " 1";
            int result = system(commandCountWord.c_str());
        }
        auto fin = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duracion = fin - inicio;
        escribeTiempos(string(argv[8]), thread, duracion); 
    }

    return 0;
}
