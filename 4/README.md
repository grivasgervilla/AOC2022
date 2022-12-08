# Día 4 :black_large_square: :black_medium_small_square:

# Solución a la primera parte

El problema consiste en, dados pares de rangos de valores $[a,b]$ y $[c,d]$ contar en cuántos de estos pares, uno de los rangos está contenido en el otro.

Esto es algo sencillo, ya que bastará con comparar los límites de ambos rangos y ver si el primero está contenido en el segundo, o viceversa con un par de condicionales muy simples. ¿Dónde está la complejidad del problema? En procesar las cadenas del archivo de entrada.

Cada uno de estos pares es una línea de texto en el archivo de entrada, la cual sigue el esquema `a-b,c-d`, donde `a`, `b`, `c` y `d` son número enteros positivos. Y la coma y los guiones nos sirven para separar estos datos. Entonces tendremos dos funciones:

1. La encargada de descomponer cada cadena de texto en la información del par de rangos.
2. La que hace la comprobación de si en el par de rangos hay uno contenido en el otro.

## Función que descompone una cadena de entrada

Lo primero que vamos a hacer para facilitarnos el trabajo de devolver **los cuatro valores** que nos dan la información del par de rangos es declarar un `struct` que almacenará esos cuatro valores. Podríamos optar por la opción que usamos en el [Día 3](https://github.com/Griger/AOC2022/tree/main/3) pasando 4 valores por referencia, pero en esta ocasión al tratarse de un conjunto de 4 valores, emplearemos un tipo de dato compuesto que contendrá los cuatro valores.

````c++
struct Par{
    int primero_ext_inferior, primero_ext_superior;
    int segundo_ext_inferior, segundo_ext_superior;
};
````

> Hemos definido el `struct` así porque queda más visual que la información es relativa a dos rangos de valores.
> 
> Pero podríamos optar por declarar cada uno de los campos en una línea individual, o los cuatro campos en la misma línea como `int primero_ext_inferior, primero_ext_superior, segundo_ext_inferior, segundo_ext_superior;`.
> 
> Esto no influye en nada en el comportamiento del código, es una mera cuestión de estilo, que no tiene siquiera por qué ser la mejor.

Ahora vamos a definir la función encargada de obtener la información para un `Par` a partir de una cadena de texto de la entrada. Que como hemos dicho sigue el siguiente esquema, donde aprovechamos para usar la nomenclatura de aquellos valores que emplearemos en el código de la función, y que así este código sea más fácil de comprender:

![esquema cadenas de entrada](https://github.com/Griger/AOC2022/blob/main/4/img/esquema-cadena.png)

Teniendo en cuenta este esquema lo que vamos a hacer es:

1. Encontrar la posición de la coma y los guiones con la función `string::find`.
2. Usando esas posiciones como referencia, extraer con la función `string::substr` las distintas subcadenas que serán los distintos números de nuestro par de rangos, y pasarlas a número entero con la función `stoi`.

````c++
const char COMA = ',';
const char GUION = '-';

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
````

> Observa que la función `find` tiene distintas formas de usarse. Con la primera le pasamos únicamente el caracter que queremos encontrar, y nos devolverá la posición **de la primera ocurrencia** de ese caracter.
> 
> Con la segunda le pasamos tanto el caracter como la posición *a partir de la cual* comenzar a buscar ese caracter. Esto nos sirve para encontrar la segunda ocurrencia del guion en la cadena, diciendole que lo busque a partir de la posición donde se encuentra la coma.
> 
> Si quisiéramos hacer esto sin usar esta segunda versión de la función `find` lo podríamos hacer como `pos_segundo_guion = pos_coma + (linea.substr(pos_coma, linea.length())).find(GUION);`.
> 
> Aquí vemos también una particularidad de la función `substr`, y es que si le pasamos una longitud de subcadena mayor que lo que realmente nos queda de cadena, simplemente llega hasta el final, por eso le podemos pasar simplemente `linea.length()` como tamaño de subcadena, sin preocuparnos de que «nos salgamos» de la cadena.

Como vemos, una vez extraemos lo que necesitamos de la cadena, lo único que hacemos es almacenar estos datos en los campos del `struct` que hemos definido.

## Función que analiza cada par de rangos

En esta función simplemente tenemos que comprobar, dados dos intervalos, si uno está incluído en otro, que esto simplemente lo hacemos con una sentencia booleana.

````c++
bool comprobar_inclusion(const Par &par){
    bool estan_incluidos = (par.primero_ext_inferior <= par.segundo_ext_inferior && par.segundo_ext_superior <= par.primero_ext_superior) ||
            (par.segundo_ext_inferior <= par.primero_ext_inferior && par.primero_ext_superior <= par.segundo_ext_superior);

    return estan_incluidos;
}
````

1. Observa que pasamos el `Par` como un valor constante por referencia, ya que no necesitamos modificarlo.
2. Observa cómo componemos la condición usando los paréntesis: la primera parte antes del `||` comprueba que el segundo rango esté contenido en el primero, y la segunda parte comprueba la otra condición.

Por último observa cómo usamos el valor booleano directamente devuelto por la función `comprobar_inclusion` en la condición del `if` que empleamos para aumentar, si procede, el contador `total_rangos_incluidos`.

````c++
int total_rangos_incluidos = 0;

Par informacion_linea;

while (getline(archivo_entrada, linea)){
    informacion_linea = obtener_informacion_rangos(linea);

    if (comprobar_inclusion(informacion_linea))
        total_rangos_incluidos++;
}
````

> El valor devuelto por una función puede ser utilizado como cualquier otro valor de ese tipo en nuestro código, **sin que necesitemos almacenar ese valor en una variable, para luego usar la variable.
> 
> Aunque en ocasiones el código quedará más legible si hacemos esto último. Pero aquí podemos ver que esto no es necesario.