#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int TOP = 3;

void actualizar_ranking(int ranking[], int calorias_actuales) {
    int pos_en_ranking = -1;

    for (int pos = 0; pos < TOP; ++pos)
        if (calorias_actuales > ranking[pos] && (pos_en_ranking == -1 || ranking[pos_en_ranking] > ranking[pos]))
            pos_en_ranking = pos;

    if (pos_en_ranking != -1)
        ranking[pos_en_ranking] = calorias_actuales;
}

int main() {
    // Ponemos la ruta del archivo, relativa a la localizacion del *.cpp con la solucion.
    string ruta_archivo_entrada = "input.txt";
    fstream archivo_entrada;

    int calorias_actuales = 0;

    int ranking[TOP] = {0, 0, 0}; // Vector en el que almacenamos el top 3 de calorias totales.

    // Abrimos el archivo para leerlo.
    archivo_entrada.open(ruta_archivo_entrada, ios::in);

    // Leemos el archivo linea por linea.
    if (archivo_entrada.is_open()) {
        string linea;

        while (getline(archivo_entrada, linea)) {
            if (linea != "") {
                calorias_actuales += stoi(linea);
            } else {
                actualizar_ranking(ranking, calorias_actuales);
                calorias_actuales = 0;
            }
        }

        actualizar_ranking(ranking, calorias_actuales);
        archivo_entrada.close();

        int total = 0;

        for (int pos = 0; pos < TOP; ++pos)
            total += ranking[pos];

        cout << "Las calorias totales de los " << TOP << " elfos que llevan mas calorias es " << total << endl;
    } else {
        cout << "Error al abrir el archivo." << endl;
    }

    return 0;
}
