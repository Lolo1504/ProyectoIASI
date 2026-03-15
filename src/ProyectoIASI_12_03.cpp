/**
 * @file main.cpp
 * @brief Programa principal del proyecto Hora Punta.
 *
 * Este archivo contiene la función principal que:
 * 1. Solicita al usuario seleccionar un fichero de tablero.
 * 2. Muestra el tablero inicial.
 * 3. Ofrece un menú para elegir entre tres algoritmos de búsqueda heurística:
 *    - Hill Climbing (escalada de máxima pendiente)
 *    - A* (A estrella)
 *    - Best First (primero mejor)
 * 4. Ejecuta el algoritmo seleccionado, muestra la secuencia de movimientos,
 *    el tiempo de ejecución y el número de nodos generados.
 */

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

/**
 * @brief Función principal del programa.
 * @return 0 si la ejecución finaliza correctamente.
 */
int main() {
    // Título del proyecto
    cout << "=== PROYECTO HORA PUNTA ===" << endl;

    // Crear el tablero como una matriz de 6x6 de strings
    vector<vector<string>> Tablero(6, vector<string>(6));

    // Llamar a la función de selección de fichero (definida en ManejoFicheros.cpp)
    // Devuelve false si todo fue bien (el tablero se cargó correctamente)
    if (!eleccionJuego(Tablero)) {
        // Mostrar el tablero inicial cargado
        cout << "\nTablero inicial:" << endl;
        impresionTablero(Tablero);

        // Menú de opciones
        cout << "¿Qué desea hacer?" << endl;
        cout << "1 - Ejecutar escalada de máxima pendiente (hill climbing)" << endl;
        cout << "2 - Ejecutar A*" << endl;
        cout << "3 - Ejecutar Primero Mejor (Best First)" << endl;
        cout << "Opción: ";
        int opcion;
        cin >> opcion;

        // Ejecutar según la opción elegida
        if (opcion == 1) {
            // Hill Climbing
            auto start = chrono::high_resolution_clock::now();   // Inicio medición tiempo
            vector<string> secuencia;                             // Almacenará la secuencia de movimientos
            int nodosGenerados = 0;                               // Contador de nodos generados
            bool exito = hillClimbing(Tablero, secuencia, nodosGenerados); // Llamada al algoritmo
            auto end = chrono::high_resolution_clock::now();     // Fin medición tiempo
            chrono::duration<double> elapsed = end - start;       // Tiempo transcurrido

            // Mostrar resultados
            if (exito) {
                cout << "\n¡Solución encontrada por escalada!" << endl;
                cout << "Secuencia de movimientos: ";
                if(secuencia.empty()) cout<<"Z esta en un borde";
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
            // A*
            vector<string> secuencia;
            int nodosGenerados = 0;
            double tiempo = 0.0;
            bool exito = aStar(Tablero, secuencia, nodosGenerados, tiempo);

            if (exito) {
                cout << "\n¡Solución encontrada por A*!" << endl;
                cout << "Secuencia de movimientos: ";
                if(secuencia.empty()) cout<<"Z esta en un borde";
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
            // Best First
            vector<string> secuencia;
            int nodosGenerados = 0;
            double tiempo = 0.0;
            bool exito = bestFirst(Tablero, secuencia, nodosGenerados, tiempo);

            if (exito) {
                cout << "\n¡Solución encontrada por Primero Mejor!" << endl;
                cout << "Secuencia de movimientos: ";
                if(secuencia.empty()) cout<<"Z esta en un borde";
                for (size_t i = 0; i < secuencia.size(); i++) {
                    if (i > 0) cout << ", ";
                    cout << secuencia[i];
                }
                cout << endl;
            } else {
                cout << "\nNo se encontró solución con Primero Mejor." << endl;
            }
            cout << "Tiempo de ejecución: " << tiempo << " segundos" << endl;
            cout << "Nodos generados: " << nodosGenerados << endl;
        }
        else {
            cout << "Opción no válida." << endl;
        }
    } else {
        // Si eleccionJuego devuelve true, significa que hubo un error al cargar el fichero
        cout << "Cerrando Aplicación. Manejo de Ficheros fallido." << endl;
    }
    return 0;
}
