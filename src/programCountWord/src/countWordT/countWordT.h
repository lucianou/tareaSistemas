#ifndef COUNTWORDT_H
#define COUNTWORDT_H

#include <iostream>
#include <vector>
#include <thread>
#include <string>

using namespace std;

void menuCWT();                                                                 // funcion menu de countWordThread
void countWordThreads(const vector<string>& files, int cantThreads);            // funcion para contar palabras con threads
vector<string> cargarArchivos(const string& directorio, const string& extension);

#endif 