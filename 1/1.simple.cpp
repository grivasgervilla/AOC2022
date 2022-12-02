#include <iostream>
#include <string>
#include <fstream>

using  namespace std;

int main() {
    // Ponemos la ruta del archivo, relativa a la localizacion del *.cpp con la solucion.
    string ruta_archivo_entrada = "input.txt";
    fstream archivo_entrada;

    int calorias_maximas = 0, calorias_grupo_actual = 0;

    // Abrimos el archivo para leerlo.
    archivo_entrada.open(ruta_archivo_entrada, ios::in);

    // Leemos el archivo linea por linea.
    if (archivo_entrada.is_open()) {
        string linea;

        while (getline(archivo_entrada, linea)) {
            if (linea != ""){
                calorias_grupo_actual += stoi(linea);
            }
            else{
                if (calorias_grupo_actual > calorias_maximas)
                    calorias_maximas = calorias_grupo_actual;
                calorias_grupo_actual = 0;
            }
        }

        if (calorias_grupo_actual > calorias_maximas)
            calorias_maximas = calorias_grupo_actual;

        cout << "Las calorias maximas que lleva un elfo son: " << calorias_maximas << endl;
        archivo_entrada.close();
    } else {
        cout << "Error al abrir el archivo." << endl;
    }

    return 0;
}