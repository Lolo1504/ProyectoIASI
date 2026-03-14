/*
 * ManejoFicheros.cpp
 *
 *  Created on: 12 mar 2026
 *      Author: jorge
 */

#include "ManejoFicheros.h"

// Carpeta donde se buscan los archivos de tablero (debe existir en el mismo directorio que el ejecutable)
string carpeta = "FicherosEntrada";

// Vector global que almacena pares (número del fichero, ruta completa)
// Se llena con extraccionNumero() y se usa en eleccionJuego()
vector<pair<int, string>> ficheros;  // (número, nombre_completo)

/**
 * @brief Escanea la carpeta "FicherosEntrada" y extrae los números de los archivos
 *        que coinciden con el patrón "HORAPUNTA<numero>.txt".
 *
 * Utiliza expresiones regulares para identificar los archivos válidos y guarda
 * en el vector global 'ficheros' el par (número, ruta). La comparación es
 * insensible a mayúsculas/minúsculas (regex::icase).
 */
void extraccionNumero(){
    // Expresión regular: "HORAPUNTA" seguido de uno o más dígitos (\d+), luego ".txt"
    // El grupo de captura (\d+) permite extraer el número.
    regex patron(R"(HORAPUNTA(\d+)\.txt)", regex::icase);

    // Recorrer todos los elementos de la carpeta usando filesystem::directory_iterator
    for (const auto& entry : fs::directory_iterator(carpeta)) {
        // Solo nos interesan archivos regulares (no directorios, symlinks, etc.)
        if (entry.is_regular_file()) {
            // Obtener el nombre del archivo (ej. "HORAPUNTA3.txt")
            string nombre = entry.path().filename().string();
            smatch match;  // Para almacenar los resultados de la expresión regular
            // Comprobar si el nombre completo coincide con el patrón
            if (regex_match(nombre, match, patron)) {
                // match[1] contiene el primer grupo de captura (los dígitos)
                int num = stoi(match[1].str());
                // Guardar el número y la ruta completa en el vector global
                ficheros.push_back({num, entry.path().string()});
            }
        }
    }
}

/**
 * @brief Lee un fichero de texto con el tablero y llena la estructura proporcionada.
 *
 * El fichero debe contener 6 líneas, cada una con 6 valores separados por comas.
 * Se eliminan espacios en blanco y retornos de carro al inicio y final de cada celda.
 * El tablero se pasa por referencia para ser modificado directamente.
 *
 * @param Tablero Referencia al vector 6x6 de strings que se llenará.
 * @param nom_fich Nombre (ruta) del fichero a leer.
 */
void llenarTablero(vector<vector<string>> &Tablero, string nom_fich) {
    // Abrir el fichero en modo lectura
    ifstream fichero(nom_fich);
    if (!fichero.is_open()) {
        cout << "No se pudo abrir el fichero" << endl;
        return;
    }

    string linea;
    int fila = 0;
    // Leer línea por línea hasta completar 6 filas o fin de archivo
    while (getline(fichero, linea) && fila < 6) {
        // Eliminar retorno de carro (si existe en archivos de Windows)
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();

        // Usar stringstream para dividir la línea por comas
        stringstream ss(linea);
        string celda;
        int col = 0;
        // Leer cada celda separada por coma hasta completar 6 columnas
        while (getline(ss, celda, ',') && col < 6) {
            // Eliminar espacios y saltos de línea al inicio de la cadena
            size_t start = celda.find_first_not_of(" \t\r\n");
            if (start != string::npos)
                celda = celda.substr(start);
            // Eliminar espacios y saltos de línea al final de la cadena
            size_t end = celda.find_last_not_of(" \t\r\n");
            if (end != string::npos)
                celda = celda.substr(0, end + 1);

            // Asignar la celda limpia al tablero
            Tablero[fila][col] = celda;
            col++;
        }
        fila++;
    }
    fichero.close();  // Cerrar el archivo
}

/**
 * @brief Gestiona la selección interactiva del fichero de tablero por parte del usuario.
 *
 * Realiza los siguientes pasos:
 * 1. Verifica que la carpeta "FicherosEntrada" exista.
 * 2. Llama a extraccionNumero() para obtener la lista de ficheros disponibles.
 * 3. Ordena la lista por número y la muestra al usuario.
 * 4. Solicita al usuario que introduzca el número del fichero deseado.
 * 5. Busca el fichero correspondiente y, si existe, llama a llenarTablero().
 *    Si el número no es válido, carga el primer fichero por defecto.
 *
 * @param Tablero Referencia al vector 6x6 de strings que se llenará con el tablero elegido.
 * @return true si ocurrió algún error (carpeta no existe, no hay ficheros, etc.),
 *         false si todo fue correcto y el tablero se cargó satisfactoriamente.
 */
bool eleccionJuego(vector<vector<string>> &Tablero){
    // 1. Comprobar que la carpeta existe y es un directorio
    if (!fs::exists(carpeta) || !fs::is_directory(carpeta)) {
        cout << "Error: No se encuentra la carpeta '" << carpeta << "'." << endl;
        return 1;   // Devuelve true (error)
    }

    // 2. Extraer los números de los ficheros (llena el vector global 'ficheros')
    extraccionNumero();

    // 3. Ordenar los ficheros por número para mostrarlos de forma ordenada
    sort(ficheros.begin(), ficheros.end());

    // 4. Si no se encontró ningún fichero, mostrar error
    if (ficheros.empty()) {
        cout << "No se encontraron ficheros del tipo HORAPUNTA*.txt en la carpeta." << endl;
        return 1;
    }

    // 5. Mostrar las opciones disponibles al usuario
    cout << "Ficheros disponibles:" << endl;
    for (const auto& f : ficheros) {
        cout << "  " << f.first << " -> " << f.second << endl;
    }

    // 6. Pedir al usuario que seleccione un número
    int ind;
    cout << "Seleccione el número del fichero que desea cargar: ";
    cin >> ind;

    // 7. Buscar el fichero con el número indicado
    string nom_fich;
    bool encontrado = false;
    for (const auto& f : ficheros) {
        if (f.first == ind) {
            nom_fich = f.second;
            encontrado = true;
            break;
        }
    }

    // 8. Si no se encuentra, cargar el primer fichero por defecto (el de menor número)
    if (!encontrado) {
        cout << "Número no válido. Se cargará el primer fichero por defecto." << endl;
        nom_fich = ficheros[0].second;
    }

    // 9. Llamar a la función que lee el fichero y llena el tablero
    llenarTablero(Tablero, nom_fich);

    return 0;   // Devuelve false (éxito) para que main pueda hacer if(!eleccionJuego(...))
}
