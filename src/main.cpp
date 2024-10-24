#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <string>
#include "numeric.h"
#include "text.h"
#include "auth.h"
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void mostrarMenu(string user, string rol, string frase, vector<int> nums, int num, double dnum, vector<Usuario>& users, vector<string>& entorno) {
    int funcion = -1;
    pid_t pid = getpid();  // Obtener el PID del proceso padre

    while (funcion != 0) {
        cout << "\nSISTEMA @@@@ (PID = " << pid << ")" << endl;
        cout << "Nombre de Usuario: " << user << endl;
        cout << "Rol: " << rol << "\n" << endl;
        cout << "###################################\n";
        cout << "respuesta de la ejecución:\n";

        if (funcion == 1) {
            palindromo(frase);
        } else if (funcion == 2) {
            contarVocales(frase);
        } else if (funcion == 3) {
            contarLetras(frase);
        } else if (funcion == 4) {
            promedioSumatoria(nums);
        } else if (funcion == 5) {
            if (num != 0) {
                calcularF(num);
            } else if (dnum != 0) {
                calcularF(dnum);
            } else {
                cout << "\nEl número 0 no forma parte del dominio de la función. Operación no válida.\n\n";
            }
        } else if (funcion == 6) {
            string command = "./src/programCountWord/main " + entorno[1] + " "+ entorno[2] + " "+ entorno[3] + " "+ entorno[4] + " " + entorno[5] + " "+ entorno[6] + " " + entorno[7];
            int result = system(command.c_str());
        } else if (funcion == 7 && rol == "Admin") {
            ingresarUsuario(users, entorno[0]);
        } else if (funcion == 8 && rol == "Admin") {
            listarUsuarios(users);
        } else if (funcion == 9 && rol == "Admin") {
            eliminarUsuarios(users, entorno[0]);
        } else {
            cout << "----------------" << endl;
        }

        cout << "###################################\n\n";

        // Mostrar menú
        cout << "-------------- [Menú de opciones] -------------\n";
        cout << "    0 : Salir\n";
        cout << "    1 : Detección de palíndromo\n";
        cout << "    2 : Contar vocales\n";
        cout << "    3 : Cantidad de letras por texto\n";
        cout << "    4 : Promedio y sumatoria de un vector\n";
        cout << "    5 : Calcular f(x) = 5x*x + (1/x)\n";
        cout << "    6 : Contar Palabras\n";
        if (rol == "Admin") {
            cout << "    7 : Ingresar Usuarios\n";
            cout << "    8 : Listar Usuarios\n";
            cout << "    9 : Eliminar Usuarios\n";
        }
        cout << "------------------------------------------------\n";

        // Solicitar opción
        cout << "INGRESE OPCIÓN: ";
        cin >> funcion;
        while (cin.fail() || funcion < 0 || (rol != "Admin" && funcion > 6) || (rol == "Admin" && funcion > 9)) {
            cerr << "ERROR: Ingrese un número válido: ";
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> funcion;
        }
    }
}

int main(int argc, char *argv[]) {
    int opcion;
    string frase;
    vector<int> numeros;
    int num;
    double dnum;

    vector<string> entorno = leerEnv(".env");
    vector<Usuario> users = leerUsuarios(entorno[0]);
    if (users.empty()) return 1;
    string username;
    string pass;

    if (argc != 11) {
        cerr << "Error: Ingrese todos los parámetros necesarios. La entrada debería ser ./trabajo1 -u nombre -p contraseña -t frase -v vector -n numero\n";
        return 0;
    }

    while ((opcion = getopt(argc, argv, "u:p:t:v:n:")) != -1) {
        switch (opcion) {
            case 'u':
                if (!usernameValido(optarg)) {
                    return 1;
                }
                username = optarg;
                break;
            case 'p':
                if (!passValida(optarg)) {
                    return 1;
                }
                pass = optarg;
                break;
            case 't':
                if (optarg == nullptr || optarg[0] == '-') {
                    cerr << "Error: Ingrese una frase válida no nula para -t.\n";
                    return 1;
                }
                frase = optarg;
                break;
            case 'v':
                if (optarg == nullptr || optarg[0] == '-' || !esVectorValido(optarg)) {
                    cerr << "Error: Ingrese un vector válido para -v, de la forma 5;4;2.\n";
                    return 1;
                }
                numeros = stringToVector(optarg);
                break;
            case 'n':
                if (optarg == nullptr || optarg[0] == '-' || !esNumerico(optarg)) {
                    cerr << "Error: Ingrese un número válido para -n. Puede ser entero o flotante (de la forma 1.5).\n";
                    return 1;
                }
                if (esEntero(optarg)) num = stoi(optarg);
                else dnum = stod(optarg);
                break;
            case '?':  // Manejar opciones inválidas
                cerr << "Opción no reconocida: -" << char(optopt) << endl;
                return 1;
            default:
                return 1;
        }
    }

    int userIndex = usuarioValido(users, username, pass);
    if (userIndex == -1) {
        cerr << "Error: Los datos de usuario son incorrectos.\n";
        return 1;
    }

    mostrarMenu(username, users[userIndex].rol, frase, numeros, num, dnum, users, entorno);
    cout << "----------------- [Saliendo...] ----------------" << endl;
    return 1;
}