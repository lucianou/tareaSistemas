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
    bool procesado = false;
/*
    if (argc > 1) {  // Comprobar si se ha pasado un argumento
        for(int i=1; i<argc; i++){
        string inputString = argv[i];
        cout << "String recibido: " << inputString << std::endl;
        }
    } else {
        cerr << "No se pasó ningún argumento al programa." << std::endl;
    }
*/

    while (true) {
        cout << "------- [Programa contador de palabras] -------\n";
        cout << "   0 : Salir\n";
        cout << "   1 : Contador de palabras \n";
        cout << "   2 : Contador de palabras con threads\n";
        cout << "   3 : Crea índice invertido." << endl;
        cout << "-----------------------------------------------\n";
        cout << "INGRESE OPCIÓN: ";
        cin >> opcion;
        cout << "\n";
        cout << "-----------------------------------------------\n\n";

        if (opcion == 1) {
            menuCWL();
        } else if (opcion == 2) {
            procesado = menuCWT(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
        } else if (opcion == 3) {
            if(procesado) cout << "hola" << endl;
            else cerr << "ERROR: No se han procesado archivos aún. Procese archivos para usar esta opción.\n";
        } else if (opcion == 0) {
            return 0;
        } else {
            cerr << "Opción no válida. Intente nuevamente.\n";
        }
    }
    
    cout << "----------------- [Saliendo...] --------------------\n";
    return 1;
}   