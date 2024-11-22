#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <map>
#include <queue>
#include <string>
#include <ctime>

using namespace std;

extern map<string, string> cacheMap;  // Declaración externa
extern queue<string> cacheQueue;      // Declaración externa

void iniciarCache(int memory_size, int PORT);
void manejarConexion(int new_socket, int memory_size);
string consultarMotorDeBusqueda(const string &query);

#endif
