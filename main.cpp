#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

// ------------------------------------------------------------
// Funciones de lectura y manipulación del tablero (intactas)
// ------------------------------------------------------------

void llenarTablero(vector<vector<string>> &Tablero, string nom_fich) {
    ifstream fichero;
    string caracter;
    fichero.open(nom_fich);
    if (fichero.fail()) {
        cout << "No se pudo abrir el fichero" << endl;
    } else {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                getline(fichero, caracter, ',');
                Tablero[i][j] = caracter;
            }
        }
        fichero.close();
    }
}

void impresionTablero(const vector<vector<string>> &Tablero) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            cout << Tablero[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void posicionX(int &x, int &y, const vector<vector<string>> &Tablero) {
    bool encontrado = false;
    for (int i = 0; i < 6 && !encontrado; i++) {
        for (int j = 0; j < 6 && !encontrado; j++) {
            if (Tablero[i][j] == "X") {
                x = i;
                y = j;
                encontrado = true;
            }
        }
    }
}

void intercambiar(int nX, int nY, string letra, vector<vector<string>> &Tablero) {
    int x, y;
    posicionX(x, y, Tablero);
    Tablero[x][y] = letra;
    Tablero[nX][nY] = "X";
}

int MovimientoAbajo(const vector<vector<string>> &Tablero, int fila, int columna, string letra) {
    if (fila + 1 < 6 && Tablero[fila + 1][columna] == letra) {
        return MovimientoAbajo(Tablero, fila + 1, columna, letra);
    } else {
        return fila;
    }
}

int MovimientoArriba(const vector<vector<string>> &Tablero, int fila, int columna, string letra) {
    if (fila - 1 >= 0 && Tablero[fila - 1][columna] == letra) {
        return MovimientoArriba(Tablero, fila - 1, columna, letra);
    } else {
        return fila;
    }
}

int MovimientoIzq(const vector<vector<string>> &Tablero, int fila, int columna, string letra) {
    if (columna - 1 >= 0 && Tablero[fila][columna - 1] == letra) {
        return MovimientoIzq(Tablero, fila, columna - 1, letra);
    } else {
        return columna;
    }
}

int MovimientoDer(const vector<vector<string>> &Tablero, int fila, int columna, string letra) {
    if (columna + 1 < 6 && Tablero[fila][columna + 1] == letra) {
        return MovimientoDer(Tablero, fila, columna + 1, letra);
    } else {
        return columna;
    }
}

bool CandidatoX(const vector<vector<string>> &Tablero, int x, int y, string letra) {
    bool vertical = true;
    if ((y - 1 >= 0 && Tablero[x][y - 1] == letra) ||
        (y + 1 < 6 && Tablero[x][y + 1] == letra)) {
        vertical = false;
    }
    return vertical;
}

bool CandidatoY(const vector<vector<string>> &Tablero, int x, int y, string letra) {
    bool horizontal = true;
    if ((x - 1 >= 0 && Tablero[x - 1][y] == letra) ||
        (x + 1 < 6 && Tablero[x + 1][y] == letra)) {
        horizontal = false;
    }
    return horizontal;
}

// ------------------------------------------------------------
// HEURÍSTICA
// ------------------------------------------------------------
int heuristic(const vector<vector<string>> &Tablero) {
    int zX = -1, zY = -1;
    int xX = -1, xY = -1;
    
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (Tablero[i][j] == "Z") {
                zX = i;
                zY = j;
            } else if (Tablero[i][j] == "X") {
                xX = i;
                xY = j;
            }
        }
    }
    
    int distArriba = zX;
    int distAbajo = 5 - zX;
    int distIzq = zY;
    int distDer = 5 - zY;
    int distanciaZBorde = min(min(distArriba, distAbajo), min(distIzq, distDer));
    int distanciaZX = abs(zX - xX) + abs(zY - xY);
    
    return distanciaZBorde + distanciaZX;
}

// ------------------------------------------------------------
// Escalada de Máxima Pendiente
// ------------------------------------------------------------
void escaladaMaximaPendiente(vector<vector<string>> Tablero) {
    cout << "\n=== INICIANDO ESCALADA DE MAXIMA PENDIENTE ===" << endl;
    
    int current_h = heuristic(Tablero);
    int iteracion = 1;
    bool atascado = false;

    while (!atascado) {
        cout << "\n--- Iteracion " << iteracion << " ---" << endl;
        cout << "Heuristica actual: " << current_h << endl;

        int x, y;
        posicionX(x, y, Tablero);
        string letra;

        int best_h = INT_MAX;
        vector<vector<string>> best_board;
        string best_letra = "";

        // Abajo
        if (x + 1 < 6) {
            letra = Tablero[x + 1][y];
            if (CandidatoX(Tablero, x + 1, y, letra)) {
                vector<vector<string>> copia = Tablero;
                int nuevaFila = MovimientoAbajo(copia, x + 1, y, letra);
                intercambiar(nuevaFila, y, letra, copia);
                int h = heuristic(copia);
                if (h < best_h) { best_h = h; best_board = copia; best_letra = letra; }
            }
        }
        // Arriba
        if (x - 1 >= 0) {
            letra = Tablero[x - 1][y];
            if (CandidatoX(Tablero, x - 1, y, letra)) {
                vector<vector<string>> copia = Tablero;
                int nuevaFila = MovimientoArriba(copia, x - 1, y, letra);
                intercambiar(nuevaFila, y, letra, copia);
                int h = heuristic(copia);
                if (h < best_h) { best_h = h; best_board = copia; best_letra = letra; }
            }
        }
        // Izquierda
        if (y - 1 >= 0) {
            letra = Tablero[x][y - 1];
            if (CandidatoY(Tablero, x, y - 1, letra)) {
                vector<vector<string>> copia = Tablero;
                int nuevaCol = MovimientoIzq(copia, x, y - 1, letra);
                intercambiar(x, nuevaCol, letra, copia);
                int h = heuristic(copia);
                if (h < best_h) { best_h = h; best_board = copia; best_letra = letra; }
            }
        }
        // Derecha
        if (y + 1 < 6) {
            letra = Tablero[x][y + 1];
            if (CandidatoY(Tablero, x, y + 1, letra)) {
                vector<vector<string>> copia = Tablero;
                int nuevaCol = MovimientoDer(copia, x, y + 1, letra);
                intercambiar(x, nuevaCol, letra, copia);
                int h = heuristic(copia);
                if (h < best_h) { best_h = h; best_board = copia; best_letra = letra; }
            }
        }

        // Vemos si es mejor el hijo  que el padre
        if (best_h < current_h) {
            cout << "-> Se mueve vehiculo: " << best_letra << " | Nueva heuristica: " << best_h << endl;
            Tablero = best_board; // Actualizamos el estado actual
            current_h = best_h;
            impresionTablero(Tablero);
            iteracion++;
        } else {
            cout << "\n-> [Maximo Local / Meseta]" << endl;
            cout << "-> Ningun movimiento posible mejora la heuristica actual (" << current_h << ")." << endl;
            atascado = true;
        }
    }
}

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------
int main() {
    cout << "Seleccione fichero del 1-7" << endl;
    string nom_fich;
    int ind = 0;
    cin >> ind;

    switch (ind) {
    case 1: nom_fich = "FicherosEntrada/HORAPUNTA1.txt"; break;
    case 2: nom_fich = "FicherosEntrada/HORAPUNTA2.txt"; break;
    case 3: nom_fich = "FicherosEntrada/HORAPUNTA3.txt"; break;
    case 4: nom_fich = "FicherosEntrada/HORAPUNTA4.txt"; break;
	case 5: nom_fich = "FicherosEntrada/HORAPUNTA5.txt"; break;
	case 6: nom_fich = "FicherosEntrada/HORAPUNTA6.txt"; break;
	case 7: nom_fich = "FicherosEntrada/HORAPUNTA7.txt"; break;
	
    default: nom_fich = "FicherosEntrada/HORAPUNTA1.txt"; break;
    }

    vector<vector<string>> Tablero(6, vector<string>(6));
    llenarTablero(Tablero, nom_fich);

    cout << "Tablero inicial:" << endl;
    impresionTablero(Tablero);

    // Lanzamos el algoritmo
    escaladaMaximaPendiente(Tablero);

    return 0;
}
