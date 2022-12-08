#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int PUNTOS_A_MINUSCULA = 1;
const int PUNTOS_A_MAYUSCULA = 27;

int obtener_puntos_letra(char letra){
    int puntos;

    if ('a' <= letra && letra <= 'z')
        puntos = PUNTOS_A_MINUSCULA + (letra - 'a');
    else if ('A' <= letra && letra <= 'Z')
        puntos = PUNTOS_A_MAYUSCULA + (letra - 'A');

    return puntos;
}

int obtener_puntos_grupo(const string &primera, const string &segunda, const string &tercera){
    bool encontrado = false;
    char caracter_repetido;

    for (int pos = 0; pos < primera.length() && !encontrado; pos++){
        encontrado = segunda.find(primera[pos]) != string::npos && tercera.find(primera[pos]) != string::npos;

        if (encontrado)
            caracter_repetido = primera[pos];

    }

    return obtener_puntos_letra(caracter_repetido);
}

int main(){
    string ruta_archivo = "input.txt";
    fstream archivo_entrada;

    archivo_entrada.open(ruta_archivo, ios::in);

    string primera, segunda, tercera;
    int puntuacion_total = 0;

    while (getline(archivo_entrada, primera)) {
        getline(archivo_entrada, segunda);
        getline(archivo_entrada, tercera);
        puntuacion_total += obtener_puntos_grupo(primera, segunda, tercera);
    }

    archivo_entrada.close();

    cout << "La puntuacion total obtenida es: " << puntuacion_total << endl;
    return 0;
}