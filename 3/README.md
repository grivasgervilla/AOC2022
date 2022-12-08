# Día 3 :package:

# Solución a la primera parte

El reto de la primera parte consiste en un conjunto de cadenas de texto. Para cada una de ellas:

1. Obtenemos las dos mitades de esa cadena.
2. Vemos cuál es **la única** letra que se encuentra en ambas cadenas.
3. Para cada letra existen una puntuación:
   * Para las minúsculas de la *a* a la *z*, la puntuación va de *1* a *26*.
   * Para las mayúsculas de la *A* a la *Z*, la puntuación va de *27* a *52*.

Tenemos que obtener la puntuación total de las letras repetidas en todas las cadenas de la entrada.

## Diseñando la solución

Como hemos visto en el [Día 2](https://github.com/Griger/AOC2022/tree/main/2), descomponer el problema en subproblemas por medio de funciones nos facilita el planteamiento del problema y su resolución. En este caso vamos a descomponer el problema en tres partes:

1. Una función que se encargue de, dada una letra, devolver la puntuación asociada a esa letra.
2. Una función que, dada una cadena de texto, devuelva dos cadenas que serán las dos mitades de la cadena dada. **Veremos el uso del paso por referencia en las funciones para devolver más de un valor**.
3. Finalmente, la función encargada de, dada una cadena, devolvernos la puntuación asociada a la cadena.

### Una función que nos dé la puntuación asociada a cada letra

Para obtener la puntuación asociada a una letra, nos beneficiaremos del orden de los caracteres en la [tabla ASCII](https://elcodigoascii.com.ar/), y es que las letras minúsculas aparecen juntas en la tabla, y lo mismo ocurre para las mayúsculas.

````c++
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
````

1. Es claro que nuestra función recibe un `char`, la letra, y devuelve su puntuación en forma de un dato de tipo `int`.
2. Observa el uso de las dos constantes para establecer los puntos que le damos a la a minúscula y mayúscula. El uso de constantes disminuye el uso de *valores mágicos* en el código, lo que aumenta su legibilidad y, por tanto, reduce la propensión a errores, y hace el código más fácilmente depurable.

> Usa constantes para definir distintos valores que uses en tu código, como la puntuación asociada a una letra. De este modo, en lugar de poner el *valor mágico*, que no se sabrá de qué viene, veremos el nombre de una variable que, si lo hemos elegido bien, nos dará información sobre qué representa el valor almacenado en ella.

3. Mira el patrón de condiciones para comprobar que un valor está dentro de un cierto rango $[a,b]$, `a <= valor && valor <= b`. Piensa también cuál sería el patrón para un intervalo o rango de valores abierto, o para comprobar que un valor *no* está en un cierto rango. Este tipo de condiciones son muy recurrentes en el código.
4. Tenemos que distinguir entre letras mayúsculas y minúsculas ya que aparecen en dos grupos distintos dentro de la tabla ASCII, que no están juntos, por ello usamos sentencias condicionales, *para establecer dos caminos distintos en nuestro código*.
5. Observa cómo funcionan las operaciones entre dos variables de tipo `char`: al restar dos caracteres lo que obtenemos es la diferencia entre los números que se corresponden con su posición en la tabla ASCII. Por ello, para, por ejemplo, obtener la puntuación de una minúscula lo que hacemos es sumarla a la puntuación asociada a la primera letra minúscula (la a) la distancia entre esa letra minúscula y la a.

### Una función que nos devuelva las dos mitades de una cadena

En C++, para una función en el `return` podemos devolver un único valor: la puntuación asociada a una letra, la suma de los dos argumentos... Pero hay ocasiones en las que queremos devolver dos valores o más. Entonces tenemos dos opciones:

1. Definir un `struct` que tenga los campos adecuados para englobar todos los datos que queremos devolver, y entonces en la función pertinente devolver un dato de tipo ese `struct` que hemos definido, y construir el `struct` que deseemos.
2. Devolver estos valores en variables que pasamos a la función **por referencia**, que va a ser la solución por la que optemos en esta ocasión.

Nosotros queremos una función a la que le pasemos una cadena de texto y nos devuelva sus dos mitades. Como con una función **podemos devolver un solo valor**, lo que podemos hacer es pasar dos variables **por referencia**, donde almacenaremos estos dos valores que queremos devolver; las dos mitades.

Así lo que pasaremos a la función será:

- La cadena que queremos partir que la pasaremos como un valor constante y por referencia, ya que queremos evitar su copia, y también evitar que podamos modificar la cadena original en el cuerpo de la función.
- Otros dos valores por referencia **no constantes** que utilizaremos para almacenar en ellos las dos mitades que queremos devolver.

Entonces, lo que tendremos que hacer allí donde invoquemos la función será declarar dos variables en las que almacenaremos la información que queremos devolver, y pasarlas en la llamada a la función como los dos valores por referencia no constantes. De modo que lo que hagamos con estos valores dentro de la función, las modificaciones que les hagamos, se verá reflejado allí donde hayamos invocado la función.

> Cuando pasamos una variable por referencia a una función (de modo que sea un parámetro no constante), las modificaciones que hagamos a esa variable dentro de la función, se harán efectivamente sobre esa variable, y podremos ver los efectos allí donde hemos invocado la función pasándole esa variable.
> 
> Este efecto se debe a que, tanto la variable que hemos declarado allí donde invocamos a la función, como el argumento de la función correspondiente en esa llamada, apuntan a la misma posición de memoria. Por lo tanto, los cambios hechos en la función en dicha posición de memoria, se verán allí donde hemos invocado la función, en la variable que apunta precisamente a esa misma posición de memoria, y que hemos pasado como argumento a la función. Como se muestra en el siguiente esquema:
> 
> ![esquema paso por referencia](https://github.com/Griger/AOC2022/blob/main/3/img/referencia.png)

````c++
void obtener_mitades_cadena(const string &original, string &primera_mitad, string &segunda_mitad){
    int longitud_mitad = original.length() / 2;

    primera_mitad = original.substr(0, longitud_mitad);
    segunda_mitad = original.substr(longitud_mitad, longitud_mitad);
}
````

El código de la función es muy sencillo:

1. Obtenemos cuántos caracteres tendrá cada mitad de la cadena, asumiendo que la cadena original tendrá una longitud par.
2. Usamos la función `substr` de la STL que nos devuelve una subcadena. A esta función le pasamos a partir de qué posición de la cadena original queremos comenzar la subcadena, y cuántos caracteres a partir de él (*incluido*) queremos extraer.
3. Ambas mitades las almacenamos en las dos variables que pasamos por referencia no constante a la función.

### Una función que nos devuelva la puntuación asociada a una cadena determinada

Una vez que tenemos una función que nos devuelve las dos mitades de una cadena, y otra que, dada una letra, nos devuelve su puntuación, es muy fácil construir el código de la función que, dada una cadena (una línea del archivo de entrada), nos dé la puntuación de esa cadena.

El algoritmo se podría diseñar como sigue:

1. Dividimos la cadena en dos mitades.
2. Recorremos la primera mitad y vemos qué caracter de esa primera mitad está también presente en la segunda mitad, empleando para ello la función `find` de la que disponen los `string` en C++. Como sabemos que entre las dos mitades hay **un único caracter repetido**, cuando encontremos un caracter que esté en ambas mitades habremos acabado.
3. La puntuación de la cadena será la asociada al caracter repetido que hemos encontrado en las dos mitades.

````c++
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
````

> Observa que, la función `string::find`, en caso de no encontrar el caracter deseado nos devuelve una constante ya definida que es la `string::npos`, valor que usamos para poner el booleano `encontrado` a verdadero o falso, según haya encontrado el caracter buscado en la cadena.
> 
> Observa también cómo se invoca esta función, es un método que tiene cada cadena que declaremos en el código, entonces la invocamos como `cadena_donde_queremos_buscar.find(caracter_a_buscar)`.

Además de eso, algunas cosas en la que nos tenemos que fijar en el código:

1. El uso del patrón ya conocido para buscar un elemento en un vector o en una cadena, con el uso de la variable booleana `encontrado`.
2. La primera posición de una cadena es la 0, y la última será su longitud menos 1, ya que la última posición real está compuesta por el caracter de final de cadena que no nos interesa, por eso el menor estricto.

El código de la función `main` para acumular la puntuación de cada una de las cadenas leídas es trivial vistas las soluciones de los días anteriores.

# Solución a la segunda parte

El ejercicio propuesto para la segunda parte de este reto, una vez hemos comprendido la solución anterior, es trivial. El ejercicio consiste en considerar las cadenas de texto de la entrada en grupos de 3 y asignar una puntuación a cada uno de esos grupos.

La puntuación vendrá dada por los puntos asignados a aquel caracter que aparezca en las tres cadenas. Por lo tanto, aquí podemos reutilizar la función `obtener_puntos_letra`, no necesitaremos la función que divide una cadena en dos, y tendremos que cambiar la función que nos da la puntuación de una cadena, por una función que nos dé la puntuación para un grupo de tres cadenas.

Además, haremos unos pequeños ajustes en el código de la función `main`, para leer tres cadenas en cada iteración del bucle.

````c++
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
````

Observa que el código de la función para obtener la puntuación de un grupo es muy parecido al que teníamos antes para obtener la puntuación de una cadena, solo que ahora buscamos cada caracter de la primera cadena del grupo en las otras dos, y será el carracter correcto si está tanto en la segunda cadena como en la tercera; de ahí la condición doble que tenemos para establecer el valor de `encontrado`.

````c++
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
````

Y lo único que cambia ahora en el `main` para leer la entrada, es que leemos las líneas de tres en tres, invocando la función `getline` tres veces en cada vuelta del bucle, y almacenando lo leído en tres `string` distintas, el código base para hacer esto está disponible en el archivo [skeleton.cpp](https://github.com/Griger/AOC2022/blob/main/3/skeleton.cpp).