#ifndef NUMERIC_H
#define NUMERIC_H
#include <vector>
#include <cctype>

using namespace std;

pair<double, int> promedioSumatoria(vector<int> nums);
double calcularF(double num);
double calcularF(int num);
bool esNumerico(string num);
bool esEntero(string num);
bool esVectorValido(string nums);
vector<int> stringToVector(string nums);
void printVector(vector<int> numeros);

#endif