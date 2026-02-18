#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void llenarTablero(vector <vector<string>> &Tablero,string nom_fich){
 ifstream fichero;
    string caracter;
    fichero.open(nom_fich);
    if(fichero.fail()) {
        cout<< "No se pudo abrir el fichero"<<endl;
    } else {
        for(int i=0;i<6;i++) {
            for(int j=0;j<6;j++) {
                getline(fichero,caracter,',');
                Tablero[i][j]=caracter;
            }
        }
        fichero.close();
    }
}

void impresionTablero(vector <vector<string>> Tablero){
    for(int i =0;i<6;i++) {
        for(int j=0;j<6;j++) {
            cout<< Tablero[i][j];
        }
    }
	cout<< endl << endl;
}


void posicionX(int &x, int &y, const vector<vector<string>>& Tablero) {
    bool encontrado = false;
    
    for(int i = 0; i < 6 && !encontrado; i++) {
        for(int j = 0; j < 6 && !encontrado; j++) {
            if(Tablero[i][j] == "X") {
                x = i;
                y = j;
                encontrado = true;
            }
        }
    }
}
	

void intercambiar(int nX,int nY,string letra,vector<vector<string>> &Tablero) {
        int x,y;
        posicionX(x,y,Tablero);
        Tablero[x][y]=letra;
        Tablero[nX][nY]="X";
}
	
int MovimientoAbajo(const vector<vector<string>>& Tablero, int fila, int columna, string letra) { 
    if(fila + 1 < 6 && Tablero[fila + 1][columna] == letra) { 
        return MovimientoAbajo(Tablero, fila + 1, columna, letra);
    } else {
        return fila;
    }
}
	
int MovimientoArriba(const vector<vector<string>>& Tablero, int fila, int columna, string letra) {
    if(fila - 1 >= 0 && Tablero[fila - 1][columna] == letra) { 
        return MovimientoArriba(Tablero, fila - 1, columna, letra);
    } else {
        return fila;
    }
}
	
int MovimientoIzq(const vector<vector<string>>& Tablero, int fila, int columna, string letra) {
    if(columna - 1 >= 0 && Tablero[fila][columna - 1] == letra) { 
        return MovimientoIzq(Tablero, fila, columna - 1, letra);
    } else {
        return columna;
    }
}
	
int MovimientoDer(const vector<vector<string>>& Tablero, int fila, int columna, string letra) {
    if(columna + 1 < 6 && Tablero[fila][columna + 1] == letra) { 
        return MovimientoDer(Tablero, fila, columna + 1, letra);
    } else {
        return columna;
    }
}

bool CandidatoX(const vector<vector<string>>& Tablero, int x, int y, string letra) {
	bool vertical = true;
    if ((y - 1 >= 0 && Tablero[x][y - 1] == letra) || (y + 1 < 6 && Tablero[x][y + 1] == letra)) {
         vertical = false;
    } 
    return vertical;
}
	
bool CandidatoY(const vector<vector<string>>& Tablero, int x, int y, string letra) {
    bool horizontal = true;
    if ((x - 1 >= 0 && Tablero[x - 1][y] == letra) || (x + 1 < 6 && Tablero[x + 1][y] == letra)) {
        horizontal = false;
    }
    return horizontal;
}
	
void Movimiento(vector<vector<string>> Tablero)
{   
    int x, y;
    string letra;
    posicionX(x, y, Tablero);

    if(x + 1 < 6) {
        letra = Tablero[x + 1][y];
        if(CandidatoX(Tablero, x + 1, y, letra)) {
            vector<vector<string>> Tablero_Copia = Tablero; 
            cout << "Movimiento:  " << letra << endl;
            intercambiar(MovimientoAbajo(Tablero_Copia, x + 1, y, letra), y, letra, Tablero_Copia);
            impresionTablero(Tablero_Copia);
        }
    }

    if(x - 1 >= 0) {
        letra = Tablero[x - 1][y];
        if(CandidatoX(Tablero, x - 1, y, letra)) {
            vector<vector<string>> Tablero_Copia = Tablero; 
            cout << "Movimiento : " << letra << endl;
            intercambiar(MovimientoArriba(Tablero_Copia, x - 1, y, letra), y, letra, Tablero_Copia);
            impresionTablero(Tablero_Copia);
        }   
    }

    if(y - 1 >= 0) {
        letra = Tablero[x][y - 1];
        if(CandidatoY(Tablero, x, y - 1, letra)) {
            vector<vector<string>> Tablero_Copia = Tablero; 
            cout << "Movimiento: " << letra << endl;
            intercambiar(x, MovimientoIzq(Tablero_Copia, x, y - 1, letra), letra, Tablero_Copia);
            impresionTablero(Tablero_Copia);
        }   
    }

    if(y + 1 < 6) {
        letra = Tablero[x][y + 1];
        if(CandidatoY(Tablero, x, y + 1, letra)) {
            vector<vector<string>> Tablero_Copia = Tablero; 
            cout << "Movimiento: " << letra << endl;
            intercambiar(x, MovimientoDer(Tablero_Copia, x, y + 1, letra), letra, Tablero_Copia);
            impresionTablero(Tablero_Copia);
        }   
    }
}
int main () 
{
    cout << "Seleccione fichero del 1-4" << endl;
    string nom_fich;
    int ind = 0;

    cin >> ind;

    switch (ind)
    {
    case 1:
        nom_fich = "FicherosEntrada/HORAPUNTA1.txt";
        break;
    case 2:
        nom_fich = "FicherosEntrada/HORAPUNTA2.txt";
        break;
    case 3:
        nom_fich = "FicherosEntrada/HORAPUNTA3.txt";
        break;
    case 4:
        nom_fich = "FicherosEntrada/HORAPUNTA4.txt";
        break;
    default:
        nom_fich = "FicherosEntrada/HORAPUNTA1.txt";
        break;
    }


    vector <vector<string>> Tablero(6,vector<string>(6));
    llenarTablero(Tablero,nom_fich);
    impresionTablero(Tablero);
        Movimiento(Tablero);
    return 0;
}
