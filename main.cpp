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
void posicionX(int &x,int &y,vector <vector<string>> Tablero){
    for(int i=0;i<6;i++)
        {
            for(int j=0;j<6;j++)
                {
                    if(Tablero[i][j]=="X")
                        {
                            x=i;
                            y=j;
                            return;
                        }
                }
        }
}
void posicionZ(int &Zx,int &Zy, vector<vector<string>> Tablero)
    {
        for(int i=0;i<6;i++)
            {
                for(int j=0;j<6;j++)
                    {
                        if(Tablero[i][j]=="Z")
                        {
                            Zx=i;
                            Zy=j;
                            return;
                        }
                    }
            }

    }


void impresionTablero(vector <vector<string>> Tablero){
    for(int i =0;i<6;i++) {
        for(int j=0;j<6;j++) {
            cout<< Tablero[i][j];
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
 
    return 0;
}