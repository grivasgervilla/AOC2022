#include <iostream>
#include <fstream>

using namespace std;

const int NUM_PILAS = 9;

struct Celda{
    char letra;
    Celda* paquete_debajo;
};

void formar_pila(Celda* &celda_inicial, string cadena_pila){
    Celda* celda_actual = new Celda {cadena_pila[0], nullptr};
    celda_inicial = celda_actual;

    for (int pos = 1; pos < cadena_pila.length(); ++pos)
        celda_actual = celda_actual->paquete_debajo = new Celda{cadena_pila[pos], nullptr};
}

void procesar_movimiento(const string &linea, int &numero_paquetes, int &desde, int &a){
    const string CADENA_MOVE = "move ";
    const string CADENA_FROM = " from ";
    const string CADENA_TO = " to ";

    int pos_move = linea.find(CADENA_MOVE);
    int pos_inicial_numero_paquetes = pos_move + CADENA_MOVE.length();

    int pos_from = linea.find(CADENA_FROM);
    int pos_inicial_desde = pos_from + CADENA_FROM.length();

    int pos_to = linea.find(CADENA_TO);
    int pos_inicial_a = pos_to + CADENA_TO.length();

    numero_paquetes = stoi(linea.substr(pos_inicial_numero_paquetes, pos_from - pos_inicial_numero_paquetes));
    desde = stoi(linea.substr(pos_inicial_desde, pos_to - pos_inicial_desde)) - 1;
    a = stoi(linea.substr(pos_inicial_a)) - 1;
}

void realizar_movimiento(Celda* &desde, Celda* &a, int numero_paquetes){
    Celda* puntero_auxiliar;
    Celda* ultimo_paquete_a_mover = desde;

    for (int paquete = 0; paquete < numero_paquetes - 1; ++paquete)
       ultimo_paquete_a_mover = ultimo_paquete_a_mover->paquete_debajo;

    puntero_auxiliar = a;
    a = desde;
    desde = ultimo_paquete_a_mover->paquete_debajo;
    ultimo_paquete_a_mover->paquete_debajo = puntero_auxiliar;
}

void liberar_memoria(Celda* celda){
    if (celda->paquete_debajo != nullptr)
        liberar_memoria(celda->paquete_debajo);

    delete celda;
}

int main(){
    string cadenas_pilas[NUM_PILAS] = {"QHCTNSVB", "GBDW", "BQSTRWF", "NDJZSWGL", "FVDPM", "JWF", "VJBQNL", "NSQJCRTG", "MDWCQSJ"};
    Celda* pilas[NUM_PILAS];

    for (int pila = 0; pila < NUM_PILAS; ++pila)
        formar_pila(pilas[pila], cadenas_pilas[pila]);

    string ruta_archivo = "input.txt";
    fstream archivo_entrada;

    archivo_entrada.open(ruta_archivo, ios::in);

    string linea;
    int numero_paquetes, desde, a;

    while (getline(archivo_entrada, linea)) {
        procesar_movimiento(linea, numero_paquetes, desde, a);
        realizar_movimiento(pilas[desde], pilas[a], numero_paquetes);
    }

    for (int pila = 0; pila < NUM_PILAS; ++pila)
        cout << pilas[pila]->letra;

    for (int pila = 0; pila < NUM_PILAS; ++pila)
        liberar_memoria(pilas[pila]);

}