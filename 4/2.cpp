#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const char COMA = ',';
const char GUION = '-';

struct Par{
    int primero_ext_inferior, primero_ext_superior;
    int segundo_ext_inferior, segundo_ext_superior;
};

Par obtener_informacion_rangos(string linea){
    Par informacion;

    int pos_primer_guion, pos_coma, pos_segundo_guion;

    pos_primer_guion = linea.find(GUION);
    pos_coma = linea.find(COMA);
    pos_segundo_guion = linea.find(GUION, pos_coma);

    informacion.primero_ext_inferior = stoi(linea.substr(0, pos_primer_guion));
    informacion.primero_ext_superior = stoi(linea.substr(pos_primer_guion + 1, pos_coma - pos_primer_guion - 1));
    informacion.segundo_ext_inferior = stoi(linea.substr(pos_coma + 1, pos_segundo_guion - pos_coma - 1));
    informacion.segundo_ext_superior = stoi(linea.substr(pos_segundo_guion + 1, linea.length()));

    return informacion;
}

bool comprobar_solapamiento(const Par &par){
    bool solapan = (par.primero_ext_inferior <= par.segundo_ext_inferior && par.segundo_ext_inferior <= par.primero_ext_superior) ||
            (par.segundo_ext_inferior <= par.primero_ext_inferior && par.primero_ext_inferior <= par.segundo_ext_superior);

    return solapan;
}

int main(){
    string ruta_archivo = "input.txt";
    fstream archivo_entrada;

    archivo_entrada.open(ruta_archivo, ios::in);

    string linea;
    int total_rangos_incluidos = 0;

    Par informacion_linea;

    while (getline(archivo_entrada, linea)){
        informacion_linea = obtener_informacion_rangos(linea);

        if (comprobar_solapamiento(informacion_linea))
            total_rangos_incluidos++;
    }

    cout << "El total de pares de rangos que solapan es: " << total_rangos_incluidos << endl;


    archivo_entrada.close();

    return 0;
}