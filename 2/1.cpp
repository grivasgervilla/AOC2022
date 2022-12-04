#include <iostream>
#include <fstream>

using namespace std;

const string PIEDRA = "piedra";
const string PAPEL = "papel";
const string TIJERAS = "tijeras";

const int BONUS_PIEDRA = 1;
const int BONUS_PAPEL = 2;
const int BONUS_TIJERAS = 3;

const int BONUS_VICTORIA = 6;
const int BONUS_EMPATE = 3;
const int BONUS_DERROTA = 0;

string traducir_eleccion (char eleccion){
    string traduccion;

    if (eleccion == 'A' || eleccion == 'X')
        traduccion = PIEDRA;
    else if (eleccion == 'B' || eleccion == 'Y')
        traduccion = PAPEL;
    else
        traduccion = TIJERAS;

    return traduccion;
}

int bonus_por_eleccion (string eleccion){
    int bonus;

    if (eleccion == PIEDRA)
        bonus = BONUS_PIEDRA;
    else if (eleccion == PAPEL)
        bonus = BONUS_PAPEL;
    else
        bonus = BONUS_TIJERAS;

    return bonus;
}

int bonus_por_resultado (string eleccion, string eleccion_contrincante){
    int bonus;

    if (eleccion == PIEDRA){
        if (eleccion_contrincante == PIEDRA)
            bonus = BONUS_EMPATE;
        else if (eleccion_contrincante == TIJERAS)
            bonus = BONUS_VICTORIA;
        else
            bonus = BONUS_DERROTA;
    } else if (eleccion == TIJERAS) {
        if (eleccion_contrincante == PIEDRA)
            bonus = BONUS_DERROTA;
        else if (eleccion_contrincante == TIJERAS)
            bonus = BONUS_EMPATE;
        else
            bonus = BONUS_VICTORIA;
    } else {
        if (eleccion_contrincante == PIEDRA)
            bonus = BONUS_VICTORIA;
        else if (eleccion_contrincante == TIJERAS)
            bonus = BONUS_DERROTA;
        else
            bonus = BONUS_EMPATE;
    }

    return bonus;
}

int procesar_partida (const string &info_partida) {
    string eleccion_nuestra = traducir_eleccion(info_partida[2]);
    string eleccion_contrincante = traducir_eleccion(info_partida[0]);

    return bonus_por_eleccion(eleccion_nuestra) + bonus_por_resultado(eleccion_nuestra, eleccion_contrincante);
}

int main(){
    string ruta_archivo = "input.txt";
    fstream archivo_entrada;

    archivo_entrada.open(ruta_archivo, ios::in);

    string linea;
    int puntuacion_total = 0;

    while (getline(archivo_entrada, linea))
        puntuacion_total += procesar_partida(linea);

    archivo_entrada.close();

    cout << "La puntuacion total obtenida es: " << puntuacion_total << endl;

    return 0;
}