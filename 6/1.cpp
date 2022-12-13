#include <iostream>
#include <fstream>

using namespace std;

const int TAM_MARCADOR = 4;

bool todos_distintos(string subcadena){
    bool todos_son_distintos = true;

    if (subcadena.length() == TAM_MARCADOR){
        for (int pos = 0; pos < TAM_MARCADOR; ++pos) {
            if (subcadena.find(subcadena[pos], pos + 1) != string::npos)
                todos_son_distintos = false;
        }
    }

    return todos_son_distintos;
}

int localizar_marcador(const string &cadena){
   int posicion_caracter_fin_marcador = -1;
   bool encontrado = false;

    for (int pos = 0; pos < cadena.length() && !encontrado; ++pos) {
        encontrado = todos_distintos(cadena.substr(pos, TAM_MARCADOR));

        if (encontrado)
            posicion_caracter_fin_marcador = pos + TAM_MARCADOR;
    }

    return posicion_caracter_fin_marcador;
}

int main(){
    string ruta_archivo = "input.txt";
    fstream archivo_entrada;

    archivo_entrada.open(ruta_archivo, ios::in);

    string linea;
    getline(archivo_entrada, linea);

    cout << localizar_marcador(linea) << endl;
}