#ifndef MANEJOFICHEROS_H_
#define MANEJOFICHEROS_H_


#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <regex>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;


//...
void extraccionNumero();
//...
void llenarTablero(vector<vector<string>> &Tablero, string nom_fich);
//...
bool eleccionJuego(vector<vector<string>> &Tablero);

#endif
