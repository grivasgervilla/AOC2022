#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    /*
     * Vamos a tener el archivo con la entrada del problema
     * en el mismo directorio donde tengamos el .cpp con la solucion
     * y donde generaremos el ejecutable correspondiente.
     */
    string ruta_archivo_entrada = ""; //Poner el nombre del archivo con la entrada.
    fstream archivo_entrada;

    archivo_entrada.open(ruta_archivo_entrada, ios::in);

    if (archivo_entrada.is_open()){
        // El siguiente codigo lee el archivo linea por linea hasta llegar al final.
        string linea;

        while (getline(archivo_entrada, linea)){
            // En cada vuelta de este bucle la variable linea contendra la linea del archivo que se haya leido.
            // Si queremos usar esta linea como un entero podemos usar la funcion stoi(linea), que convierte un string en un entero.

            // Hacemos lo que necesitemos con esa linea.
            // Tengamos en cuenta que las lineas en blanco nos indican que pasamos a los datos de un nuevo elfo.
        }

    } else {
        cout << "Error al abrir el archivo" << endl;
    }
}