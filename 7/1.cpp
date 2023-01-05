#include <iostream>
#include <fstream>

using namespace std;

const int PESO_MAXIMO = 100000;

const char INICIO_COMANDO = '$';
const char ESPACIO = ' ';

const string RAIZ = "/";
const string PADRE = "..";
const string DIR = "dir";

const string COMANDO_CD = "cd";
const string COMANDO_LS = "ls";

const int CD_A_HIJO = 0;
const int CD_A_PADRE = 1;
const int CD_A_RAIZ = 2;
const int LS = 3;
const int DIRECTORIO = 4;
const int FICHERO = 5;


struct Nodo{
  string nombre;
  bool directorio;
  int peso;
  int numero_hijos;
  Nodo* padre;
  Nodo* hijos;
};

int procesar_linea(const string &linea){
  int codigo;

  if (linea[0] == INICIO_COMANDO){
    string comando = linea.substr(2, 2);

    if (comando == COMANDO_CD){
      string directorio = linea.substr(5, linea.length());

      if (directorio == RAIZ)
        codigo = CD_A_RAIZ;
      else if (directorio == PADRE)
        codigo = CD_A_PADRE;
      else
        codigo = CD_A_HIJO;
    }
    else
      codigo = LS;
  }
  else{
    string tres_primeros_caracteres = linea.substr(0, 3);

    if (tres_primeros_caracteres == DIR)
      codigo = DIRECTORIO;
    else
      codigo = FICHERO;
  }

  return codigo;
}

Nodo* obtener_hijo(const Nodo &actual, string linea){
  Nodo* puntero_a_hijo = nullptr;
  string nombre_hijo = linea.substr(5, linea.length());

  bool encontrado = false;

  for(int pos = 0; pos < actual.numero_hijos && !encontrado; pos++){
    if (actual.hijos[pos].nombre == nombre_hijo) {
      puntero_a_hijo = actual.hijos + pos;
      encontrado = true;
    }
  }

  return puntero_a_hijo;
}

bool esta_hijo(const Nodo &nodo, string nombre_hijo){
  bool esta = false;

  for (int pos = 0; pos < nodo.numero_hijos && !esta; pos++)
    if (nodo.hijos[pos].nombre == nombre_hijo)
      esta = true;

  return esta;
}

void aniade_hijo(Nodo &nodo, string nombre_hijo, int peso_hijo, bool directorio){
  Nodo* auxiliar = new Nodo[nodo.numero_hijos + 1];

  if (nodo.hijos != nullptr) {
    for (int pos = 0; pos < nodo.numero_hijos; ++pos) {
      auxiliar[pos] = nodo.hijos[pos];
    }

    delete[] nodo.hijos;
  }

  auxiliar[nodo.numero_hijos] = Nodo {nombre_hijo, directorio, peso_hijo, 0, &nodo, nullptr};

  nodo.hijos = auxiliar;
  nodo.numero_hijos++;
}

void procesa_hijo(Nodo &nodo, string linea, bool directorio){
  if (directorio){
    string nombre_directorio = linea.substr(4, linea.length());
    if (!esta_hijo(nodo, nombre_directorio))
      aniade_hijo(nodo, nombre_directorio, -1, true);
  }
  else{
    int pos_espacio = linea.find(ESPACIO);
    int peso = stoi(linea.substr(0, pos_espacio));
    string nombre_fichero = linea.substr(pos_espacio + 1, linea.length());

    if (!esta_hijo(nodo, nombre_fichero))
      aniade_hijo(nodo, nombre_fichero, peso, false);
  }
}

int calcula_peso(Nodo &nodo){
  int peso = 0;

  if (nodo.directorio){
    for (int pos = 0; pos < nodo.numero_hijos; pos++)
      peso += calcula_peso(nodo.hijos[pos]);

    nodo.peso = peso;
  }
  else
    peso = nodo.peso;

  return peso;
}

void calcula_peso_total(const Nodo &nodo, int &suma){
  if (nodo.directorio){
    if (nodo.peso <= PESO_MAXIMO)
      suma += nodo.peso;

    for (int pos = 0; pos < nodo.numero_hijos; ++pos) {
      calcula_peso_total(nodo.hijos[pos], suma);
    }
  }
}

int main(){
  string ruta_archivo_entrada = "input.txt";
  fstream archivo_entrada;
  Nodo raiz = {"/", true, -1, 0, nullptr, nullptr};

  archivo_entrada.open(ruta_archivo_entrada, ios::in);

  if (archivo_entrada.is_open()) {
    string linea;

    while (getline(archivo_entrada, linea)) {
      int codigo = procesar_linea(linea);
      Nodo* actual;

      switch (codigo) {
      case CD_A_RAIZ:
        actual = &raiz;
        break;
      case CD_A_PADRE:
        actual = actual->padre;
        break;
      case CD_A_HIJO:
        actual = obtener_hijo(*actual, linea);
        break;
      case DIRECTORIO:
        procesa_hijo(*actual, linea, true);
        break;
      case FICHERO:
        procesa_hijo(*actual, linea, false);
        break;
      }
    }
  }

  int suma_total = 0;
  calcula_peso(raiz);
  calcula_peso_total(raiz, suma_total);

  cout << "El peso total de los directorios validos es: " << suma_total << endl;

  return 0;
}
