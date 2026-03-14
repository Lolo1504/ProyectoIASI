/*
 * Sucesores.cpp
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 *
 *  Este archivo implementa la generación de todos los movimientos válidos (sucesores)
 *  desde un estado dado del tablero. Es utilizado por los algoritmos de búsqueda
 *  (Hill Climbing, A*, Best First) para explorar el espacio de estados.
 */

#include "Sucesores.h"
#include "Tablero.h"
using namespace std;

/**
 * @brief Genera todos los movimientos válidos (sucesores) desde un estado dado del tablero.
 *
 * Dado un tablero, localiza la posición del hueco (representado por "X") y examina
 * las cuatro casillas adyacentes (arriba, abajo, izquierda, derecha). Para cada
 * vehículo adyacente, comprueba si puede moverse hacia el hueco según las reglas:
 * - Los vehículos tienen orientación fija (horizontal o vertical) determinada por
 *   si tienen casillas del mismo tipo a izquierda/derecha (horizontal) o arriba/abajo (vertical).
 * - Un vehículo solo puede moverse en la dirección de su orientación.
 * - Las funciones `CandidatoX` y `CandidatoY` verifican si el vehículo puede moverse
 *   en dirección vertical u horizontal respectivamente.
 * - Las funciones `MovimientoAbajo`, `MovimientoArriba`, `MovimientoIzq`, `MovimientoDer`
 *   determinan hasta dónde se desplaza el vehículo (puede moverse varias casillas
 *   si es un camión/furgoneta) hasta llenar el hueco o encontrar un obstáculo.
 *
 * Para cada movimiento válido, se genera una copia del tablero, se aplica el movimiento
 * (desplazando todo el vehículo a la posición del hueco) y se guarda un par que contiene
 * la letra del vehículo movido y el nuevo tablero resultante.
 *
 * @param Tablero Referencia constante al tablero actual (vector 6x6 de strings).
 * @return std::vector<std::pair<std::string, std::vector<std::vector<std::string>>>>
 *         Vector de pares, donde cada par contiene:
 *         - first: letra del vehículo que se ha movido (std::string).
 *         - second: nuevo tablero después de aplicar el movimiento.
 */
vector<pair<string, vector<vector<string>>>>
generarMovimientos(const vector<vector<string>> &Tablero) {
    // Vector donde almacenaremos todos los sucesores encontrados
    vector<pair<string, vector<vector<string>>>> sucesores;

    // Variables para almacenar la posición actual del hueco (X)
    int x, y;
    posicionX(x, y, Tablero);  // Busca la X y devuelve sus coordenadas en x,y

    string letra;  // Letra del vehículo que podría moverse

    // ------------------------------------------------------------
    // 1. Movimiento hacia ABAJO (el vehículo está encima del hueco)
    // ------------------------------------------------------------
    // Verificamos que la casilla de abajo esté dentro del tablero
    if (x + 1 < 6) {
        // La celda justo debajo del hueco contiene un vehículo (no puede ser X porque solo hay una X)
        letra = Tablero[x + 1][y];
        // Comprobamos si ese vehículo puede moverse en dirección vertical (CandidatoX)
        if (CandidatoX(Tablero, x + 1, y, letra)) {
            // Creamos una copia del tablero para aplicar el movimiento sin modificar el original
            vector<vector<string>> copia = Tablero;
            // Calculamos la fila más lejana hasta donde se puede mover el vehículo hacia abajo
            int nuevaFila = MovimientoAbajo(copia, x + 1, y, letra);
            // Intercambiamos la posición del hueco con la última posición del vehículo
            intercambiar(nuevaFila, y, letra, copia);
            // Añadimos el par (letra, nuevo tablero) a la lista de sucesores
            sucesores.push_back({letra, copia});
        }
    }

    // ------------------------------------------------------------
    // 2. Movimiento hacia ARRIBA (el vehículo está debajo del hueco)
    // ------------------------------------------------------------
    if (x - 1 >= 0) {
        letra = Tablero[x - 1][y];
        if (CandidatoX(Tablero, x - 1, y, letra)) {
            vector<vector<string>> copia = Tablero;
            int nuevaFila = MovimientoArriba(copia, x - 1, y, letra);
            intercambiar(nuevaFila, y, letra, copia);
            sucesores.push_back({letra, copia});
        }
    }

    // ------------------------------------------------------------
    // 3. Movimiento hacia la IZQUIERDA (el vehículo está a la derecha del hueco)
    // ------------------------------------------------------------
    if (y - 1 >= 0) {
        letra = Tablero[x][y - 1];
        if (CandidatoY(Tablero, x, y - 1, letra)) {
            vector<vector<string>> copia = Tablero;
            int nuevaCol = MovimientoIzq(copia, x, y - 1, letra);
            intercambiar(x, nuevaCol, letra, copia);
            sucesores.push_back({letra, copia});
        }
    }

    // ------------------------------------------------------------
    // 4. Movimiento hacia la DERECHA (el vehículo está a la izquierda del hueco)
    // ------------------------------------------------------------
    if (y + 1 < 6) {
        letra = Tablero[x][y + 1];
        if (CandidatoY(Tablero, x, y + 1, letra)) {
            vector<vector<string>> copia = Tablero;
            int nuevaCol = MovimientoDer(copia, x, y + 1, letra);
            intercambiar(x, nuevaCol, letra, copia);
            sucesores.push_back({letra, copia});
        }
    }

    // Devolvemos la lista completa de sucesores (puede estar vacía)
    return sucesores;
}
