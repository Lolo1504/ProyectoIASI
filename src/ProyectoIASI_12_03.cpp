#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "ManejoFicheros.h"
#include "Tablero.h"
#include "Heuristica.h"
#include "HillClimbing.h"
#include "AStar.h"
#include "BestFirst.h"

using namespace std;

int main() {
    cout << "=== PROYECTO HORA PUNTA ===" << endl;

    vector<vector<string>> Tablero(6, vector<string>(6));

    if (!eleccionJuego(Tablero)) {
        cout << "\nTablero inicial:" << endl;
        impresionTablero(Tablero);

        cout << "¿Qué desea hacer?" << endl;
        cout << "1 - Ejecutar escalada de máxima pendiente (hill climbing)" << endl;
        cout << "2 - Ejecutar A*" << endl;
        cout << "3 - Ejecutar Primero Mejor (Best First)" << endl;
        cout << "Opción: ";
        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            auto start = chrono::high_resolution_clock::now();
            vector<string> secuencia;
            int nodosGenerados = 0;
            bool exito = hillClimbing(Tablero, secuencia, nodosGenerados);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;

            if (exito) {
                cout << "\n¡Solución encontrada por escalada!" << endl;
                cout << "Secuencia de movimientos: ";
                for (size_t i = 0; i < secuencia.size(); i++) {
                    if (i > 0) cout << ", ";
                    cout << secuencia[i];
                }
                cout << endl;
            } else {
                cout << "\nNo se encontró solución (máximo local)." << endl;
                if (!secuencia.empty()) {
                    cout << "Movimientos realizados: ";
                    for (size_t i = 0; i < secuencia.size(); i++) {
                        if (i > 0) cout << ", ";
                        cout << secuencia[i];
                    }
                    cout << endl;
                }
            }
            cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << endl;
            cout << "Nodos generados: " << nodosGenerados << endl;
        }
        else if (opcion == 2) {
            vector<string> secuencia;
            int nodosGenerados = 0;
            double tiempo = 0.0;
            bool exito = aStar(Tablero, secuencia, nodosGenerados, tiempo);

            if (exito) {
                cout << "\n¡Solución encontrada por A*!" << endl;
                cout << "Secuencia de movimientos: ";
                for (size_t i = 0; i < secuencia.size(); i++) {
                    if (i > 0) cout << ", ";
                    cout << secuencia[i];
                }
                cout << endl;
            } else {
                cout << "\nNo se encontró solución con A*." << endl;
            }
            cout << "Tiempo de ejecución: " << tiempo << " segundos" << endl;
            cout << "Nodos generados: " << nodosGenerados << endl;
        }
        else if (opcion == 3) {
            vector<string> secuencia;
            int nodosGenerados = 0;
            double tiempo = 0.0;
            bool exito = bestFirst(Tablero, secuencia, nodosGenerados, tiempo);

            if (exito) {
                cout << "\n¡Solución encontrada por Primero Mejor (Best First)!" << endl;
                cout << "Secuencia de movimientos: ";
                for (size_t i = 0; i < secuencia.size(); i++) {
                    if (i > 0) cout << ", ";
                    cout << secuencia[i];
                }
                cout << endl;
            } else {
                cout << "\nNo se encontró solución con Best First." << endl;
            }
            cout << "Tiempo de ejecución: " << tiempo << " segundos" << endl;
            cout << "Nodos generados: " << nodosGenerados << endl;
        }
        else {
            cout << "Opción no válida." << endl;
        }
    } else {
        cout << "Cerrando Aplicación. Manejo de Ficheros fallido." << endl;
    }
    return 0;
}
