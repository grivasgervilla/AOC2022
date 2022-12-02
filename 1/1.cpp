#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Elfo {
    int id;
    int numero_entradas;
    int *calorias;
};

int total_calorias(const Elfo &elfo) {
    int suma_calorias = 0;

    for (int pos = 0; pos < elfo.numero_entradas; ++pos) {
        suma_calorias += elfo.calorias[pos];
    }

    return suma_calorias;
}

int main() {
    // Ponemos la ruta del archivo, relativa a la localizacion del *.cpp con la solucion.
    string ruta_archivo_entrada = "input_test.txt";
    fstream archivo_entrada;

    Elfo* elfos;
    int numero_elfos = 0;

    // Abrimos el archivo para leerlo.
    archivo_entrada.open(ruta_archivo_entrada, ios::in);

    // Leemos el archivo linea por linea.
    if (archivo_entrada.is_open()) {
        string linea;

        while (getline(archivo_entrada, linea)) {
            if (linea == "") numero_elfos++;
        }

        numero_elfos++;

        elfos = new Elfo[numero_elfos];

        int contador_elfos = 0;
        int numero_entradas_inventario = 0;

        archivo_entrada.clear();
        archivo_entrada.seekg(0, ios::beg);

        while (getline(archivo_entrada, linea)) {
            if (linea != "") {
                numero_entradas_inventario++;
            } else {
                elfos[contador_elfos].numero_entradas = numero_entradas_inventario;
                elfos[contador_elfos].calorias = new int[numero_entradas_inventario];
                numero_entradas_inventario = 0;
                contador_elfos++;
            }
        }

        elfos[contador_elfos].numero_entradas = numero_entradas_inventario;
        elfos[contador_elfos].calorias = new int[numero_entradas_inventario];

        contador_elfos = 0;
        int contador_entradas_inventario = 0;

        archivo_entrada.clear();
        archivo_entrada.seekg(0, ios::beg);

        while (getline(archivo_entrada, linea)) {
            elfos[contador_elfos].id = contador_elfos;
            if (linea != "") {
                elfos[contador_elfos].calorias[contador_entradas_inventario] = stoi(linea);
                contador_entradas_inventario++;
            } else {
                contador_entradas_inventario = 0;
                contador_elfos++;
            }
        }

        archivo_entrada.close(); //Cerramos el archivo una vez hemos completado la lectura.

        // Vamos a ver cuantas calorias lleva el elfo que lleva mas calorias con el.
        int calorias_max = 0, total_calorias_elfo;

        for (int pos = 0; pos < numero_elfos; ++pos) {
            total_calorias_elfo = total_calorias(elfos[pos]);

            if (total_calorias_elfo > calorias_max){
                calorias_max = total_calorias_elfo;
            }
        }

        cout << "El numero maximo de calorias que lleva un elfo es: " << calorias_max << endl;

        // Liberamos la memoria
        for (int pos = 0; pos < numero_elfos; ++pos) {
            delete[] elfos[pos].calorias;
        }

        delete[] elfos;
    } else
        cout << "Error al abrir el archivo." << endl;

    return 0;
}