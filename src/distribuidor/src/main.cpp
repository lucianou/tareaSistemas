#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <string>
#include "distribuidor.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 1) {
       string mensaje = argv[1];
        cout << "Distribuyendo mensaje: " << mensaje << endl;
    } else {
        cerr << "No se recibió mensaje." << endl;
    }

    return 0;
}
