#include <iostream>
#include <fstream>

using namespace std;

const string PIEDRA = "piedra";
const string PAPEL = "papel";
const string TIJERAS = "tijeras";

const string VICTORIA = "victoria";
const string DERROTA = "derrota";
const string EMPATE = "empate";

const int BONUS_PIEDRA = 1;
const int BONUS_PAPEL = 2;
const int BONUS_TIJERAS = 3;

const int BONUS_VICTORIA = 6;
const int BONUS_EMPATE = 3;
const int BONUS_DERROTA = 0;

string traducir_eleccion_contrincante (char eleccion){
    string traduccion;

    if (eleccion == 'A')
        traduccion = PIEDRA;
    else if (eleccion == 'B')
        traduccion = PAPEL;
    else
        traduccion = TIJERAS;

    return traduccion;
}

string traducir_resultado_deseado (char resultado){
    string traduccion;

    if (resultado == 'X')
        traduccion = DERROTA;
    else if (resultado == 'Y')
        traduccion = EMPATE;
    else
        traduccion = VICTORIA;

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

int bonus_por_resultado (string resultado){
    int bonus;

    if (resultado == VICTORIA)
        bonus = BONUS_VICTORIA;
    else if (resultado == DERROTA)
        bonus = BONUS_DERROTA;
    else
        bonus = BONUS_EMPATE;

    return bonus;
}

string elegir_movimiento (string eleccion_contrincante, string resultado_esperado){
    string movimiento;

    if (eleccion_contrincante == PIEDRA){
        if (resultado_esperado == VICTORIA)
            movimiento = PAPEL;
        else if (resultado_esperado == DERROTA)
            movimiento = TIJERAS;
        else
            movimiento = PIEDRA;
    }
    else if (eleccion_contrincante == TIJERAS) {
        if (resultado_esperado == VICTORIA)
            movimiento = PIEDRA;
        else if (resultado_esperado == DERROTA)
            movimiento = PAPEL;
        else
            movimiento = TIJERAS;
    }
    else {
        if (resultado_esperado == VICTORIA)
            movimiento = TIJERAS;
        else if (resultado_esperado == DERROTA)
            movimiento = PIEDRA;
        else
            movimiento = PAPEL;
    }

    return movimiento;
}

int procesar_partida (const string &info_partida) {
    string eleccion_contrincante = traducir_eleccion_contrincante(info_partida[0]);
    string resultado_esperado = traducir_resultado_deseado(info_partida[2]);

    string eleccion_necesaria = elegir_movimiento(eleccion_contrincante, resultado_esperado);

    return bonus_por_eleccion(eleccion_necesaria) + bonus_por_resultado(resultado_esperado);
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
