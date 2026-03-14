#ifndef MANEJOFICHEROS_H_
#define MANEJOFICHEROS_H_

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>  // Requiere C++17 para manejo del sistema de archivos
#include <regex>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;  // Alias para simplificar el uso de filesystem

/**
 * @brief Escanea la carpeta "FicherosEntrada" y extrae los números de los archivos
 *        que coinciden con el patrón "HORAPUNTA<numero>.txt".
 *
 * Esta función recorre todos los archivos de la carpeta predefinida y, para aquellos
 * cuyo nombre cumple el patrón, guarda un par (número, ruta completa) en el vector
 * global `ficheros` (definido en ManejoFicheros.cpp). Se utiliza una expresión regular
 * para extraer el número del nombre del archivo.
 *
 * @note La función no recibe parámetros ni devuelve valor, sino que modifica una
 *       variable global. Debe llamarse después de verificar que la carpeta existe.
 */
void extraccionNumero();

/**
 * @brief Lee un fichero de texto con el tablero y llena la estructura proporcionada.
 *
 * El fichero debe contener 6 líneas, cada una con 6 valores separados por comas.
 * Se eliminan espacios en blanco y retornos de carro al inicio y final de cada celda.
 * El tablero se pasa por referencia para ser modificado directamente.
 *
 * @param Tablero Referencia al vector 6x6 de strings donde se almacenará el tablero.
 * @param nom_fich Nombre (ruta) del fichero a leer.
 */
void llenarTablero(vector<vector<string>> &Tablero, string nom_fich);

/**
 * @brief Gestiona la selección interactiva del fichero de tablero por parte del usuario.
 *
 * Esta función realiza los siguientes pasos:
 * 1. Comprueba si la carpeta "FicherosEntrada" existe.
 * 2. Llama a extraccionNumero() para obtener la lista de ficheros disponibles.
 * 3. Ordena la lista por número y la muestra al usuario.
 * 4. Solicita al usuario que introduzca el número del fichero deseado.
 * 5. Busca el fichero correspondiente y, si existe, llama a llenarTablero() para cargarlo.
 *    Si el número no es válido, carga el primer fichero por defecto.
 *
 * @param Tablero Referencia al vector 6x6 de strings que se llenará con el tablero elegido.
 * @return true si ocurrió algún error (carpeta no existe, no hay ficheros, etc.),
 *         false si todo fue correcto y el tablero se cargó satisfactoriamente.
 */
bool eleccionJuego(vector<vector<string>> &Tablero);

#endif /* MANEJOFICHEROS_H_ */
