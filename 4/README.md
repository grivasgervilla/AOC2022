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

## Función que analiza cada par de rangos