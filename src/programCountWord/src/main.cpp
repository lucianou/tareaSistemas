#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <string>
#include "countWordT.h"
#include "countWord.h"
#include "readFile.h"

using namespace std;

int main(int argc, char *argv[]) {
    int opcion;

    if (argc > 1) {  // Comprobar si se ha pasado un argumento
        string inputString = argv[1];
        cout << "String recibido: " << inputString << std::endl;
    } else {
        cerr << "No se pasó ningún argumento al programa." << std::endl;
    }


    while (true) {
        cout << "------- [Programa contador de palabras] -------\n\n";
        cout << "(0) Salir\n";
        cout << "(1) Contador de palabras \n";
        cout << "(2) Contador de palabras con threads\n";
        cout << "Seleccione la opción:";
        cin >> opcion;
        cout << "\n";
        cout << "-----------------------------------------------\n\n";

        if (opcion == 1) {
            menuCWL();
        } else if (opcion == 2) {
            menuCWT();
        } else if (opcion == 0) {
            return 0;
        } else {
            cerr << "Opción no válida. Intente nuevamente.\n";
        }
    }
    
    cout << "----------------- [Saliendo...] --------------------\n";
    return 1;
}   