#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>  // Necesario para std::remove_if
#include <sstream>
#include "auth.h"
#include "text.h"
#include <cstring>

using namespace std;

vector<string> leerEnv(const string& filename) {
    ifstream file(filename);
    string line;
    vector<string> entorno;

    while (getline(file, line)) {
        auto delimiterPos = line.find('=');
        string key = line.substr(0, delimiterPos);
        string value = line.substr(delimiterPos + 1);
        value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());
        entorno.push_back(value);
    }
    return entorno;
}

vector<Usuario> leerUsuarios(const string& nombreArchivo) {
    vector<Usuario> usuarios;

    string archivoName = nombreArchivo;
    ifstream archivo(archivoName);
    string linea;
    int indice = 1;
    int posPC;
    string par;

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return usuarios;
    }

    while (getline(archivo, linea)) {
        istringstream ss(linea);
        Usuario usuario;
        string temp;
        
        // Leer nombre de usuario
        getline(ss, usuario.user, ';');
        // Eliminar posibles espacios en blanco
        usuario.user.erase(0, usuario.user.find_first_not_of(" "));
        usuario.user.erase(usuario.user.find_last_not_of(" ") + 1);

        // Leer contraseña
        getline(ss, usuario.pass, ';');
        usuario.pass.erase(0, usuario.pass.find_first_not_of(" "));
        usuario.pass.erase(usuario.pass.find_last_not_of(" ") + 1);

        // Leer rol
        getline(ss, usuario.rol, ';');
        usuario.rol.erase(0, usuario.rol.find_first_not_of(" "));
        usuario.rol.erase(usuario.rol.find_last_not_of(" ") + 1);
        
        if(usuario.rol != "Admin" && usuario.rol != "Usuario Genérico") {
            cerr << "ERROR: falla en el formato de datos.txt, rol no válido." << endl;
            return vector<Usuario>();
        }
        // Agregar el usuario a la lista
        usuarios.push_back(usuario);
        indice++;
    }

    archivo.close();
    return usuarios;
}

bool usernameValido(string user){
    if (user.empty() || user[0] == '-'){
        cerr << "Error: Ingrese un username válido para -u. Este no puede ser nulo.\n";
        return false;
        }
    else if(user.length() < 3){
        cerr << "Error: Ingrese un username válido para -u. Este debe contener al menos 3 caracteres.\n";
        return false;
        }
    else if(!esAlfabeto(user)){
        cerr << "Error: Ingrese un username válido para -u. Este solo debe contener letras.\n";
        return false;
        }
    return true;
}

bool passValida(string pass){
    if (pass.empty() || pass[0] == '-'){
        cerr << "Error: Ingrese una contraseña válida para -p. Esta no puede ser nula.\n";
        return false;
    }
    else if(pass.length() < 6){
        cerr << "Error: Ingrese una contraseña válida para -p. Esta debe contener al menos 6 caracteres.\n";
        return false;
    }
    else if(!esAlfanumerico(pass)){
        cerr << "Error: Ingrese una contraseña válida para -p. Esta solo puede contener letras y numeros.\n";
        return false;
    }
    return true;
}

int usuarioValido(vector<Usuario> users, string usuario, string pass){
    for(int i = 0; i < users.size(); i++){
        if(usuario == users[i].user && pass == users[i].pass) return i;
    }

    return -1;
}

void ingresarUsuario(vector<Usuario>& users, string path){
    ofstream archivo(path, std::ios::app);
    string username;
    string pass;
    Usuario usuario;
    int rol;
    int ingresar = 1;
    
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para escritura." << endl;
        return;
    }

    cout << "---INGRESAR USUARIOS---" << endl;
    while(ingresar==1){ 
        cout << "Ingrese Nombre de usuario (0 para cancelar):  ";
        cin >> username;
        if(username == "0") return;
        while(!usernameValido(username)){
            cin.clear();   
            cout << "Nombre de usuario (0 para cancelar): ";
            cin >> username;
            if(username == "0") return;
        }
        usuario.user = username;
        cout << "Ingrese Contraseña (0 para cancelar): : ";
        cin >> pass;
        if(pass == "0") return;
        while(!passValida(pass)){
            cin.clear();   
            cout << "Contraseña (0 para cancelar): ";
            cin >> pass;
            if(pass == "0") return;
        }
        usuario.pass = pass;
        cout << "Ingrese Rol (1: Admin, 2: Usuario Genérico, 0: Cancelar): ";
        cin >> rol;
        if(rol == 0) return;
        while(rol<1 || rol>2){
            cerr << "ERROR: Rol inválido." << endl;
            cin.clear();   
            cout << "Ingrese Rol (1: Admin, 2: Usuario Genérico, 0: Cancelar): ";
            cin >> rol;
            if(rol == 0) return;
        }
    archivo << endl;
    if(rol == 1){
        archivo <<  username << "; " << pass << "; Admin";
        usuario.rol = "Admin";
    }
    else{
        archivo <<  username << "; " << pass << "; Usuario Genérico";
        usuario.rol = "Usuario Genérico";
    }    
    cout << "Datos escritos en el archivo correctamente.\n" << endl;
    users.push_back(usuario);
    archivo.flush();
    
    cout << "0 : Volver al menú\n1 : Ingresar nuevo usuario\n\nINGRESE OPCIÓN: ";
    cin >> ingresar;
    while(ingresar<0 || ingresar >1){
        cerr << "ERROR: Ingrese opción válida." << endl;
        cin.clear();   
        cout << "INGRESE OPCIÓN: ";
        cin >> ingresar;
        }
    }
    archivo.close();
    return;
}

void listarUsuarios(vector<Usuario> users){
    int i = 1;
    cout << "Listando usuarios..." << endl;
    cout << "Índice - Usuario - Rol " << endl;
    for(Usuario u : users){
        cout << i << "    -    " << u.user << "    -    " << u.rol << endl;
        i++;
    }
}

void eliminarUsuarios(vector<Usuario>& users, string path){
    ifstream archivoOriginal(path);
    ofstream archivoTemporal("assets/temp.txt");
    int usuarioBorrar;

    if (!archivoOriginal.is_open() || !archivoTemporal.is_open()) {
        std::cerr << "No se pudo abrir uno de los archivos." << std::endl;
        return;
    }
    listarUsuarios(users);
    cout << "\nIngrese índice del usuario que desea borrar: ";
    cin >> usuarioBorrar;
    while(usuarioBorrar-1<1 || usuarioBorrar-1>users.size() || users[usuarioBorrar-1].rol == "Admin"){
        cin.clear();   
        if(users[usuarioBorrar-1].rol == "Admin") cerr << "ERROR: No puede borrar usuario del tipo Admin, ingrese un Usuario Genérico: ";
        else if (usuarioBorrar<=0 && usuarioBorrar>users.size()){
            cerr << "ERROR: Ingrese un usuario existente: ";
            cin >> usuarioBorrar;
        } else{
            cerr << "ERROR: Ingrese un índice de usuario existente: ";
            cin >> usuarioBorrar;
        }
    }
    usuarioBorrar--;
    string linea;
    bool encontrado = false;

    while (getline(archivoOriginal, linea)) {
        // Si el elemento no se encuentra en la línea, escribir la línea en el archivo temporal
        if (linea.find(users[usuarioBorrar].user) == string::npos) {
            archivoTemporal << linea << endl;
        } else {
            encontrado = true;
        }
    }
    archivoOriginal.close();
    archivoTemporal.close();
    users.erase(users.begin()+usuarioBorrar);

    // Reemplazar el archivo original con el archivo temporal
    if (remove(path.c_str()) != 0) {
        cerr << "No se pudo eliminar el archivo original." << std::endl;
        return;
    }

    if (rename("assets/temp.txt", path.c_str()) != 0) {
        cerr << "No se pudo renombrar el archivo temporal." << std::endl;
        return;
    }
    if (encontrado) {
        cout << "Usuario eliminado con éxito. " << endl;
    }
}


int contarLineas(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;
    int contador = 0;
    if (!archivo.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo." << endl;
        return -1;
    }
    while (getline(archivo, linea)) {
        ++contador;
    }
    archivo.close();
    return contador;
}
