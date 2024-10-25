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
    if(string(argv[7]) == "1"){
        return menuCWT(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
    }
    else{
        while (true) {
            cout << "------- [Programa contador de palabras] -------\n";
            cout << "   PID : " << getpid() << "\n\n";
            cout << "   0 : Salir\n";
            cout << "   1 : Contador de palabras \n";
            cout << "   2 : Contador de palabras con threads\n";
            cout << "-----------------------------------------------\n";
            cout << "INGRESE OPCIÓN: ";
            cin >> opcion;
            cout << "-----------------------------------------------\n\n";

            if (opcion == 1) {
                menuCWL();
            } else if (opcion == 2) {
                procesado = menuCWT(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], "0");
            } else if (opcion == 0) {
                if(procesado) return 1;
                else return 0;
            } else {
                cerr << "Opción no válida. Intente nuevamente.\n";
            }
        }
        
        cout << "----------------- [Saliendo...] --------------------\n";
        return 1;
    }
}   