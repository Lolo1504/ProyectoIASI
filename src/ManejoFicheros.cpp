/*
 * ManejoFicheros.cpp
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#include "ManejoFicheros.h"


string carpeta = "FicherosEntrada";
vector<pair<int, string>> ficheros;  // (número, nombre_completo)


void extraccionNumero(){
	// Expresión regular para extraer el número de "HORAPUNTAXX.txt"
	regex patron(R"(HORAPUNTA(\d+)\.txt)", regex::icase);

	for (const auto& entry : fs::directory_iterator(carpeta)) {
	    if (entry.is_regular_file()) {
	        string nombre = entry.path().filename().string();
	        smatch match;
	        if (regex_match(nombre, match, patron)) {
	            int num = stoi(match[1].str());
	            ficheros.push_back({num, entry.path().string()});
	        }
	    }
	}
}

void llenarTablero(vector<vector<string>> &Tablero, string nom_fich) {
    ifstream fichero(nom_fich);
    if (!fichero.is_open()) {
        cout << "No se pudo abrir el fichero" << endl;
        return;
    }
    string linea;
    int fila = 0;
    while (getline(fichero, linea) && fila < 6) {
        // Eliminar retorno de carro (si existe en Windows)
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();
        stringstream ss(linea);
        string celda;
        int col = 0;
        while (getline(ss, celda, ',') && col < 6) {
            // Eliminar espacios y saltos de línea al inicio y final
            size_t start = celda.find_first_not_of(" \t\r\n");
            if (start != string::npos)
                celda = celda.substr(start);
            size_t end = celda.find_last_not_of(" \t\r\n");
            if (end != string::npos)
                celda = celda.substr(0, end + 1);
            Tablero[fila][col] = celda;
            col++;
        }
        fila++;
    }
    fichero.close();
}

bool eleccionJuego(vector<vector<string>> &Tablero){
	if (!fs::exists(carpeta) || !fs::is_directory(carpeta)) {
	    cout << "Error: No se encuentra la carpeta '" << carpeta << "'." << endl;
	    return 1;
	}

	extraccionNumero();

	sort(ficheros.begin(), ficheros.end());

	if (ficheros.empty()) {
	    cout << "No se encontraron ficheros del tipo HORAPUNTA*.txt en la carpeta." << endl;
	    return 1;
	}

	// Mostrar opciones
	cout << "Ficheros disponibles:" << endl;
	for (const auto& f : ficheros) {
	    cout << "  " << f.first << " -> " << f.second << endl;
	}

	// Pedir selección
	int ind;
	cout << "Seleccione el número del fichero que desea cargar: ";
	cin >> ind;

	// Buscar el fichero con ese número
	string nom_fich;
	bool encontrado = false;
	for (const auto& f : ficheros) {
	    if (f.first == ind) {
	        nom_fich = f.second;
	        encontrado = true;
	        break;
	    }
	}

	if (!encontrado) {
	    cout << "Número no válido. Se cargará el primer fichero por defecto." << endl;
	    nom_fich = ficheros[0].second;
	}

	llenarTablero(Tablero, nom_fich);

	return 0;
}
