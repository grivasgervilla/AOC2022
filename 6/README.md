# Día 6 :stopwatch:

# Solución a la primera parte

Este reto es más sencillo que los que hemos vistos en días anteriores:

Se nos da una cadena de texto bastante larga. Hemos de localizar en esa cadena la primera subcadena de una longitud de 4 caracteres que tenga todos sus caracteres distintos.

Y la solución al problema será la posición del último carácter de esa subcadena.

Para resolver esto hemos definido dos funciones:

* Una función que se encarga de, dada una cadena, comprobar si es una cadena de 4 caracteres con todos sus caracteres distintos.
* Y la segunda que se encarga de, dada una cadena, encontrar la primera subcadena que cumple esa condición y devolver la posición del último caracter de la misma.

## Comprobando que la subcadena es correcta

````c++
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
````

1. En este método usamos la función `find` que nos devuelve la primera posición de una cadena en la que aparece un carácter determinado. Y en caso de no encontrarla nos devuelve la constante `string::npos`.
2. Si la cadena no tiene la longitud indicada ya sabemos directamente que no es buena.
3. En otro caso pasamos a comprobar si todos los caracteres son distintos. Para ello basta ver si un carácter se encuentra alguna otra vez en la cadena a partir de su posición (basta con mirar a partir de la posición en la que está, puesto que si apareciese antes de su posición, ya hubiésemos detectado la repitición con ese caracter previo).
4. Para carácter no está basta con comprobar que lo que nos ha devuelto el `find` es el `string::npos`.
5. Observa que al método `find` le podemos pasar tanto el carácter a buscar, como la posición *a partir de la cual* buscar.

## Buscando la primera subcadena correcta

````c++
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
````

1. Vamos recorriendo la cadena.
2. Y consideramos la subcadena de 4 caracteres que empieza en el carácter en el que nos encontramos.
3. Comprobamos para cada subcadena si es la correcta.
4. En cuanto la encontramos paramos el bucle `for` como siempre que estamos buscando un elemento con una cierta propiedad.
5. La posición del último carácter será la del comienzo de esa subcadena correcta más la longitud de la cadena.
6. Nota que el método `substr` si pedimos una subcadena demasiado larga para la cadena que tenemos, lo que hace es devolver la subcadena que comienza donde indiquemos y que termina al final de la cadena original. Por esto no nos tenemos que preocupar porque en los últimos tres caracteres de la cadena original queramos encontrar la subcadena de 4 caracteres que comienza en uno de ellos, porque simplemente obtendremos una cadena de tres, dos y un carácter, respectivamente.

# Solución a la segunda parte

Para solucionar la segunda parte del reto seguimos una solución similar. En esta ocasión lo que nos pide es encontrar la posición del último carácter de la primera subcadena de 14 caracteres que tiene todos sus caracteres distintos.

Por tanto, leyendo el enunciado, habiendo comprendido la solución que hemos dado a la primera parte, es clara la pequeña modificación que le tenemos que hacer a nuestro código. Ya que ahora simplemente buscamos cadenas de 14 caracteres, en lugar de cadenas de 4.

````c++
const int TAM_MARCADOR = 14;
````

> Aquí vemos una ventaja de usar constante en lugar de valores mágicos. En otro caso hubiésemos tenido que cambiar en nuestro código todos los puntos donde usemos el valor 4, por el valor 14. Aquí basta con cambiar el valor de una variable.