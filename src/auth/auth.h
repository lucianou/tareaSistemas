#ifndef AUTH_H
#define AUTH_H
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cctype>
#include <thread>
#include <cstring>
#include "text.h"

using namespace std;
struct Usuario {
    string user;
    string pass;
    string rol;
};

vector<string> leerEnv(const string& filename);
vector<Usuario> leerUsuarios(const string& nombreArchivo);
bool usernameValido(string user);
bool passValida(string pass);
int usuarioValido(vector<Usuario> users, string usuario, string pass);
void ingresarUsuario(vector<Usuario>& users, string path);
void listarUsuarios(vector<Usuario> users);
void eliminarUsuarios(vector<Usuario>& users, string path);
int contarLineas(const string& nombreArchivo);
void ejecutarProceso(const string& comando);

#endif