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
