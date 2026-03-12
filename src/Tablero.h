/*
 * Tablero.h
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#ifndef TABLERO_H_
#define TABLERO_H_

#include <string>
#include <vector>

void impresionTablero(const std::vector<std::vector<std::string>> &Tablero);
void posicionX(int &x, int &y, const std::vector<std::vector<std::string>> &Tablero);
void intercambiar(int nX, int nY, std::string letra, std::vector<std::vector<std::string>> &Tablero);

int MovimientoAbajo(const std::vector<std::vector<std::string>> &Tablero, int fila, int columna, std::string letra);
int MovimientoArriba(const std::vector<std::vector<std::string>> &Tablero, int fila, int columna, std::string letra);
int MovimientoIzq(const std::vector<std::vector<std::string>> &Tablero, int fila, int columna, std::string letra);
int MovimientoDer(const std::vector<std::vector<std::string>> &Tablero, int fila, int columna, std::string letra);

bool CandidatoX(const std::vector<std::vector<std::string>> &Tablero, int x, int y, std::string letra);
bool CandidatoY(const std::vector<std::vector<std::string>> &Tablero, int x, int y, std::string letra);

#endif
