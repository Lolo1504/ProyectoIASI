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
void intercambiar(int nX,int nY,string letra,vector<vector<string>> &Tablero)
    {
        int x,y;
        posicionX(x,y,Tablero);
        Tablero[x][y]=letra;
        Tablero[nX][nY]="X";
    }
int MovimientoAbajo(vector<vector<string>> Tablero,int x,int y,string letra)
    {
        
        if(x+1<6&&Tablero[x+1][y]==letra)
            { 
                return  MovimientoAbajo(Tablero,x+1,y,letra);
            }
        else
            return x;
    }
int MovimientoArriba(vector<vector<string>> Tablero,int x,int y,string letra)
    {
        
        if(x-1>0&&Tablero[x-1][y]==letra)
            { 
                return  MovimientoArriba(Tablero,x-1,y,letra);
            }
        else
            return x;
    }
int MovimientoIzq(vector<vector<string>> Tablero,int x,int y,string letra)
    {
        if(y-1>0&&Tablero[x][y-1]==letra)
            { 
                return  MovimientoIzq(Tablero,x,y-1,letra);
            }
        else
            return y;
    }
    int MovimientoDer(vector<vector<string>> Tablero,int x,int y,string letra)
    {
        if(y+1<6&&Tablero[x][y+1]==letra)
            { 
                return  MovimientoDer(Tablero,x,y+1,letra);
            }
        else
            return y;
    }
bool CandidatoX(vector<vector<string>> Tablero,int x,int y,string letra)
    {
        if(y-1>0 && Tablero[x][y-1]!=letra)
        {
            if(y+1<6 && Tablero[x][y+1]!=letra)
                return true;
        }
        return false;
    }
    bool CandidatoY(vector<vector<string>> Tablero,int x,int y,string letra)
    {
        if(x-1>0 && Tablero[x-1][y]!=letra)
        {
            if(x+1<6 && Tablero[x+1][y]!=letra)
                return true;
        }
        return false;
    }
void Movimiento(vector<vector<string>> &Tablero)
    {   
        int x,y;
        string letra;
        posicionX(x,y,Tablero);
        if(x+1<6)
            {
           
                letra=Tablero[x+1][y];
              if(CandidatoX(Tablero,x+1,y,letra))
              {
                cout<<"movimiento del coche "<<letra<<endl;
                intercambiar(MovimientoAbajo(Tablero,x+1,y,letra),y,letra,Tablero);
                impresionTablero(Tablero);
                posicionX(x,y,Tablero);
                return;
              }
        }
        if(x-1>0)
            {
                letra=Tablero[x-1][y];
              if(CandidatoX(Tablero,x-1,y,letra))
              {
                cout<<"movimiento del coche "<<letra<<endl;
                intercambiar(MovimientoArriba(Tablero,x-1,y,letra),y,letra,Tablero);
                impresionTablero(Tablero);
                posicionX(x,y,Tablero);
                return;
              }   
            }
          if(y-1>0)
            {
                letra=Tablero[x][y-1];
              if(CandidatoY(Tablero,x,y-1,letra))
              {
                cout<<"movimiento del coche "<<letra<<endl;
                intercambiar(x,MovimientoIzq(Tablero,x,y-1,letra),letra,Tablero);
                impresionTablero(Tablero);
                posicionX(x,y,Tablero);
                return;
              }   
            }
        if(y+1<6)
            {
                  letra=Tablero[x][y+1];
              if(CandidatoY(Tablero,x,y+1,letra))
              {
                cout<<"movimiento del coche "<<letra<<endl;
                intercambiar(x,MovimientoDer(Tablero,x,y+1,letra),letra,Tablero);
                impresionTablero(Tablero);
                posicionX(x,y,Tablero);
                return;
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