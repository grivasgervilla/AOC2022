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

void obtener_mitades_cadena(const string &original, string &primera_mitad, string &segunda_mitad){
    int longitud_mitad = original.length() / 2;

    primera_mitad = original.substr(0, longitud_mitad);
    segunda_mitad = original.substr(longitud_mitad, longitud_mitad);
}

int obtener_puntos_cadena(const string &cadena){
    string primera_mitad, segunda_mitad;

    obtener_mitades_cadena(cadena, primera_mitad, segunda_mitad);

    bool encontrado = false;
    char caracter_repetido;

    for (int pos = 0; pos < primera_mitad.length() && !encontrado; pos++){
        encontrado = segunda_mitad.find(primera_mitad[pos]) != string::npos;

        if (encontrado)
            caracter_repetido = primera_mitad[pos];

    }

    return obtener_puntos_letra(caracter_repetido);
}
int main(){
    string ruta_archivo = "input.txt";
    fstream archivo_entrada;

    archivo_entrada.open(ruta_archivo, ios::in);

    string linea;
    int puntuacion_total = 0;

    while (getline(archivo_entrada, linea))
        puntuacion_total += obtener_puntos_cadena(linea);

    archivo_entrada.close();

    cout << "La puntuacion total obtenida es: " << puntuacion_total << endl;
    return 0;
}