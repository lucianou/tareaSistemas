#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <string>
#include <fstream>
#include <sstream>
#include "planificador.h"

using namespace std;

int main(int argc, char *argv[]) {
    loadEnv("../../.env");
    cout << "-------- [Planificador de operaciones] --------\n\n";
    planificador();
    cout << "-----------------------------------------------\n\n";
    return 0;
}
