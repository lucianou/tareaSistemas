#include <vector>
#include <iostream>
#include <cctype>
#include <cstring>
#include "numeric.h"

using namespace std;

pair<double, int> promedioSumatoria(vector<int> nums){
    int sumatoria = 0;
    int promedio;
    for(long unsigned int i=0; i < nums.size(); i++)
        sumatoria += nums[i];
    promedio = sumatoria/nums.size();
    cout << "\nPara el vector " ;
    printVector(nums);
    cout << " , la sumatoria de sus números es de " << sumatoria << ", y su promedio es de " << promedio << "\n" << endl;
    return {promedio, sumatoria};
}

//recibe flotante
double calcularF(double num){
    double f = (5*num*num) + (1/num);
    cout << "\nEl resultado de f(" << num << ") es " << f << ".\n" << endl;
    return f;
}

//recibe entero
double calcularF(int num){
    double f = (5*num*num) + (1/num);
    cout << "\nEl resultado de f(" << num << ") es " << f << ".\n" << endl;
    return f;
}

bool esNumerico(string num){
    bool numerico = true;
    long unsigned int i = 0;
    while(i < num.length() && numerico){
        if(!isdigit(num[i]) && num[i]!='.') numerico = false;
        i++;
    }
    return numerico;
}

bool esEntero(string num){
    bool entero = true;
    long unsigned int i = 0;
    while(i < num.length() && entero){
        if(num[i]!='.') entero = false;
        i++;
    }
    return entero;
}

bool esVectorValido(string nums){
    bool valido = true;
    long unsigned int i = 0;
    if(!isdigit(nums[nums.length()-1]) || !isdigit(nums[0])) valido = false; 
    while(i < nums.length() && valido){
        if(!isdigit(nums[i])){
            if(nums[i] != ';') valido = false;
            else if(nums[i+1] == ';') valido = false;
        }
        i++;
    }
    return valido;
}

vector<int> stringToVector(string nums){
    vector<int> numeros;
    vector<string> numStrings;
    long unsigned int pos = 0;
    while(pos <= nums.size()){
        pos = nums.find(";");
        numStrings.push_back(nums.substr(0,pos));
        nums.erase(0,pos+1);
        }
    for(long unsigned int i = 0; i < numStrings.size() ; i++){
        numeros.push_back(stoi(numStrings[i]));
    }
    return numeros;
}

void printVector(vector<int> numeros){
    cout << "< ";
    for(int i=0; i< numeros.size(); i++){
        if(i!=numeros.size()-1) 
            cout << numeros[i] << " , ";
        else 
            cout << numeros[i] << " >";
    }
}


