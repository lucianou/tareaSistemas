#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <string>
#include "numeric.h"
#include "text.h"

using namespace std;

void mostrarMenu(string user, string pass, string frase, vector<int> nums, int num, double dnum) {
	int funcion=0;

    cout << "\n\nBienvenido/a, " << user << "!!\n" << endl;

    while(funcion != 6){
        cout << "-------------- [Menú de opciones] -------------\n\n";
        cout << "	1 : Detección de palíndromo\n";
        cout << "	2 : Contar vocales\n";
        cout << "	3 : Cantidad de letras por texto\n";
        cout << "	4 : Promedio y sumatoria de un vector\n";
        cout << "	5 : Calcular f(x) = 5x*x + (1/x)\n";
        cout << "	6 : Salir\n\n";
        cout << "----------------------------------------\n\n";

        cout << "Ingrese función a realizar (1-6): ";
        cin >> funcion;
        while(cin.fail() || funcion <=0 || funcion>6 ){
            if(funcion <=0 || funcion>6)
                cout << "Error: Ingrese un número válido entre 1 y 6: ";
            cin.clear();   
            cin.ignore(1000, '\n'); 
            cin >> funcion;
        }

        if(funcion == 1) palindromo(frase);
        else if(funcion == 2) contarVocales(frase);
        else if(funcion == 3) contarLetras(frase);
        else if(funcion == 4) promedioSumatoria(nums);
        else if(funcion == 5 && num != 0) calcularF(num);
        else if(funcion == 5 && dnum != 0) calcularF(dnum);
        else if(funcion == 5) cout << "\nEl número 0 no forma parte del dominio de la función. Operación no válida.\n\n";

        
        cin.ignore(); 
        cout << "Presione Enter para continuar..." << endl;
        cin.get();
        cout << '\n';
    }

    return;

}

pair<string, string> loadEnv(const string& filename) {
    ifstream file(filename);
    string line;
    string user, pass;

    while (getline(file, line)) {
        auto delimiterPos = line.find('=');
        string key = line.substr(0, delimiterPos);
        string value = line.substr(delimiterPos + 1);

        if (key == "USERNAME") {
            user = limpiaCadena(value);  
        } else if (key == "PASSWORD") {
            pass = limpiaCadena(value);  
        }
    }

    return make_pair(user, pass);
}

int main(int argc, char *argv[]) {
    int opcion;
	string frase;
    vector<int> numeros;
    int num;
    double dnum;

    pair<string, string> env = loadEnv(".env");
    string envUser = env.first;
    string envPass = env.second;

    
    if (argc != 11) {
        cerr << "Error: Ingrese todos los parámetros necesarios. La entrada debería ser ./trabajo1 -u nombre -p contraseña -t frase -v vector -n numero\n";
        return 0;
    }


    while ((opcion = getopt(argc, argv, "u:p:t:v:n:")) != -1) {
        switch (opcion) {
            case 'u':
				if (optarg == nullptr || optarg[0] == '-')  {
                    cerr << "Error: Ingrese un username válido para -u. Este no puede ser nulo.\n";
                    return 1;
                }
                else if(strlen(optarg) < 3){
                    cerr << "Error: Ingrese un username válido para -u. Este debe contener al menos 3 caracteres.\n";
                    return 1;
                }
                else if(!esAlfabeto(optarg)){
                    cerr << "Error: Ingrese un username válido para -u. Este solo debe contener letras.\n";
                    return 1;
                }
                else if(optarg != envUser) {
                    cerr << "Error: Los datos de usuario son incorrectos.\n";
                    return 1;
                }
                break;
            case 'p':
				if (optarg == nullptr || optarg[0] == '-') {
                    cerr << "Error: Ingrese una contraseña válida para -p. Esta no puede ser nula.\n";
                    return 1;
                }
                else if(strlen(optarg) < 6){
                    cerr << "Error: Ingrese una contraseña válida para -p. Esta debe contener al menos 6 caracteres.\n";
                    return 1;
                }
                else if(!esAlfanumerico(optarg)){
                    cerr << "Error: Ingrese una contraseña válida para -p. Esta solo puede contener letras y numeros.\n";
                    return 1;
                }
                else if(optarg != envPass) {
                    cerr << "Error: Los datos de usuario son incorrectos.\n";
                    return 1;
                }
                break;
            case 't':
				if (optarg == nullptr || optarg[0] == '-') {
                    cerr << "Error: Ingrese una frase válida para -t.\n";
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
                if(esEntero(optarg)) num = stoi(optarg);
                else dnum = stod(optarg);
                break;
            case '?':  // Manejar opciones inválidas
                cerr << "Opción no reconocida: -" << char(optopt) << endl;
                return 1;
            default:
                return 1;
        }
    }

    mostrarMenu(envUser, envPass, frase, numeros, num, dnum);
    cout << "-------------- [Saliendo...] ---------------" << endl;
    return 1;
}
