# Día 5 :battery:

# Solución a la primera parte

Este ejercicio resulta complejo sobre todo al procesar el fichero de texto con el que nos dan la entrada para nuestro problema. El problema consistes en que tengamos varias pilas de paquetes, cada uno de los cuales se identifican por una letra. Así, en cada una de estas pilas tendremos varios paquetes apilados. Y tendremos que hacer una serie de movimientos de paquetes de una pila a otra. Y tras completar todos estos movimientos, tendremos que indicar la letra de cada uno de los paquetes que queda encima del todo en cada una de las pilas.

Así, en el fichero de entrada para este problema encontramos dos partes:

1. La configuración inicial de las pilas de paquetes, que es algo complicada de procesar por como está formateado el texto.
2. Los movimientos que tenemos que hacer. Para cada movimiento tendremos la estructura `move n from p to q` que nos indica que movamos `n` paquetes de la pila `p` a la pila `q`; donde cada pila de paquetes se identifica con un número.

Entonces lo primero que haremos será **declarar a mano en el código** un vector de `string`, donde cada `string` representa una de las pilas de la entrada; así nos evitaremos tener que procesar esta parte del texto, que por el formato que tiene sería una tarea muy complicada.

Para ello, y por como vamos a procesar a posteriori estas cadenas, cada cadena contendrá los caracteres de cada pila de arriba a abajo; desde el caracter del paquete que está más arriba en esa pila de paquetes, hasta que está en la base de la pila.

````c++
string pilas[NUM_PILAS] = {...};
````

Ahora, aunque el ejercicio lo podríamos resolver simplemente manejando las cadenas de texto, para practicar el uso de punteros vamos a construir una estructura a partir de estas cadenas de texto, donde cada cadena de texto, cada pila de paquetes, va a ser representada por una **lista enlazada**.

## La estructura de lista enlazada

Una lista enlazada la podemos pensar como un vector, pero en lugar de tener todas las celdas de ese vector juntas en la memoria, la tenemos dispersas; cada una en una posición de la memoria independiente. Entonces, para poder pasar de una celda a la siguiente necesitamos almacenar en esa celda, *no solo el valor de la celda*, sino también algo que nos indique dónde se encuentra la siguiente celda a visitar, la que iría detrás de esa celda en la que estamos. Y para ello, para representar dónde se encuentra almacenado otro objeto lo que usamos es **un puntero**.

En la siguiente imagen encontramos una representación gráfica de la diferencia entre un vector y una lista enlazada que almacenan los mismos datos en memoria:

![representación gráfica de la diferencia entre un vector y una lista enlazada](https://github.com/Griger/AOC2022/blob/main/5/img/listanelazada-vs-vector.png)

Entonces, cada celda de esta lista enlazada la representaremos por un `struct` que tendrá dentro el valor de la celda (en nuestro caso el carácter del paquete correspondiente) y un puntero apuntando a la siguiente celda en la lista (en nuestro caso al paquete que hay justo debajo del paquete representado por la celda actual).

````c++
struct Celda{
    char letra;
    Celda* paquete_debajo;
};
````

Una vez tenemos este `struct` podemos pasar a traducir cada una de las cadenas anteriores en una lista enlazada, para ello almacenaremos en un vector de `Celda*` una referencia a la primera celda de cada una de las listas enlazadas que representan cada una de las pilas de paquetes que tenemos. Es claro que teniendo acceso a la primera celda de una lista ya sabemos cómo tenemos que recorrerla siguiendo simplemente los punteros; como se muestra en la siguiente imagen:

![recorrido lista enlazada](https://github.com/Griger/AOC2022/blob/main/5/img/lista-enlazada.png)

## Construyendo la lista enlazada

Lo que haremos ahora es recorrer cada una de las cadenas, y para cada carácter de esa letra construir una celda que contenga el carácter leído, y un puntero que apunte al siguiente paquete. Para ello, con cada puntero reservaremos memoria para la `Celda` a la que apunta con el operador `new`.

Para ello declaramos una función que construye, dada una cadena, la lista enlazada correspondiente. Esta función recibe dos parámetros:

* El puntero que acabará apuntando a la primera celda de la pila que vamos a construir.
* La cadena que contiene la información de esa pila.

````c++
void formar_pila(Celda* &celda_inicial, string cadena_pila){
    Celda* celda_actual = new Celda {cadena_pila[0], nullptr};
    celda_inicial = celda_actual;

    for (int pos = 1; pos < cadena_pila.length() - 1; ++pos)
        celda_actual = celda_actual->paquete_debajo = new Celda {cadena_pila[pos], nullptr};
}
````

De este código tienes que fijarte en los siguientes detalles:

1. El uso de la constante `nullptr` que define C++ para declarar punteros nulos. Cuando definimos un puntero, en este caso el campo `paquete_debajo` del `struct Celda`, y no le hemos dado aún valor, en lugar de asignarle el `0`, es mejor práctica asignarle el valor `nullptr`, que nos indica que es un puntero nulo; un puntero que no apunta a nada. Aunque lo podrías hacer con el `0` sin problemas.
2. Como pasamos **por referencia** el puntero que apunta a la primera celda de la lista que estamos construyendo. Así, donde invoquemos a la función le pasaremos el puntero que queremos que quede apuntando a esa `Celda`, y como lo pasamos por referencia **aquellas modificaciones que le hagamos a ese parámetro dentro de la función se verán reflejadas allí donde la hayamos invocado**.
3. Observa la sintaxis para reservar memoria con el operador `new` y a la par darle valor a esa memoria reservada, poniendo entre llaves los valores a introducir.
4. Para ahorrar línea de código hemos puesto dos operaciones de asignación encadenadas dentro del bucle `for`, esto funciona bien ya que se hará de derecha a izquierda. Entonces lo que está ocurriendo es:
   1. Reservamos memoria para la siguiente celda, almacenando en ella el carácter correspondiente.
   2. Asignamos la dirección de esa nueva memoria reservada al campo `paquete_debajo` de la celda en la que estamos actualmente, **que como es un puntero a `Celda` para acceder a ese campo usamos el operador `->`.
   3. Finalmente, la `celda_actual`, el `Celda*` que apunta a la celda en la que nos encontramos en cada momento, pasa a apuntar precisamente a la `Celda` que acabamos de crear.

Y ahora, ya lo que nos queda es invocar esta función para crear cada una de las pilas de paquetes a partir de sus cadenas. Y almacenaremos las posiciones iniciales de cada pila en un vector de `Celda*`.

````c++
Celda* pilas[NUM_PILAS];

for (int pila = 0; pila < NUM_PILAS; ++pila)
    formar_pila(pilas[pila], cadenas_pilas[pila]);
````

Cada celda del vector `pilas` es un `Celda*`, el cual pasamos a la función `formar_pila` por referencia, para que construya la nueva lista enlazada y almacene en él la dirección de memoria correspondiente a la primera `Celda` de esa lista.

Así, para mostrar, una vez construida, el contenido de por ejemplo la primera pila de paquetes, lo podríamos hacer con el siguiente código:

````c++
Celda* puntero = pilas[0];

do{
    cout << puntero->letra << endl;
    puntero = puntero->paquete_debajo;
} while (puntero != nullptr);
````

> Recuerda que cuando tenemos un puntero a un dato de tipo `struct`, el acceso a los campos del objeto apuntado se realiza mediante el operador `->`.

## Procesando y realizando los movimientos de los paquetes

El fichero de entrada al programa tiene dos partes:

* La primera donde se nos da la configuración inicial de las pilas de paquetes, que como hemos dicho anteriormente no vamos a procesar y hemos copiado directamente en el código.
* Una segunda parte donde se nos indica cada uno de los movimientos a realizar. Esta parte sí la vamos a procesar, ya que son muchas líneas de texto que sería inviable copiar a mano una por una en el código.

Entonces lo que hacemos es quedarnos en el fichero de entrada con solo las líneas correspondientes a esos movimientos. Cada una de estas líneas tiene el siguiente formato: `move n from p to q`, donde `n`, `p` y `q` son números enteros, que **no vamos a suponer que sean de una única cifra**.

Entonces lo que vamos a hacer es definir una función que, cada una cadena de movimiento, nos devuelva esos tres números, que, respectivamente, nos indican:

1. El número de paquetes a mover.
2. La pila desde la cual se mueven.
3. La pila a la cual se mueven.

````c++
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
````

Este es un código básico en el que vamos buscando las subcadenas clave dentro de cada línea de texto, y usando la posición donde empiezan esas cadenas y la longitud que tienen, extraemos las subcadenas correspondientes a cada uno de los números y las convertimos a entero con la función `stoi`.

1. Observa cómo para devolver tres valores lo hacemos pasando por referencia aquellas variables donde almacenaremos esos tres valores devueltos.
2. Comprenden bien el código para ver cómo se han usado las funciones `find` y `substr` para localizar las subcadenas clave.
3. Nota el uso de constantes para evitar valores mágicos en el código.
4. Observa que pasamos la cadena como una referencia para evitar su copiado, pero constante para prevenir posibles modificaciones no deseadas dentro de la función. Si la intentásemos modificar dentro de la función el compilador nos daría un error, indicándonos que estamos intentando modificar un parámetro constante.
5. Le restamos uno a los identificadores de las pilas, ya que se numeran empezando en uno y, en cambio, las posiciones de los vectores comienzan a numerarse en 0.

> Cuando le pasemos a una función un parámetro por referencia, si no deseamos modificar ese parámetro dentro de la función, le añadiremos el modificador `const`. Esto nos evitará errores, ya que si nos equivocamos y dentro de la función modificamos el valor de ese parámetro, el compilador nos dará un error, indicándonos que ese parámetro que deseamos modificar es constante.

## Realizar el movimiento

Para cada movimiento procesado tenemos que mover ese número de paquetes de la pila indicada a la otra pila que se indica. Para ello definimos la siguiente función a la que le pasamos los punteros a los paquetes superiores de las dos pilas indicadas, y el número de paquetes indicado.

Para hacer correctamente el movimiento tenemos que entender cómo funcionan las pilas, en este caso las pilas de paquetes. Y es que cuando movamos varios paquetes de una pila a otra tenemos que pensar en que lo hacemos de uno en uno: cogiendo el paquete del tope de la pila y poniéndolo en el tope de la otra pila, luego pasando a coger el siguiente paquete de la pila (que será ahora el que esté en la cima de esa pila), y poniéndolo en el tope de la otra pila, y así sucesivamente. De modo que, el primer paquete que pasemos de una pila a la otra quedará debajo de los otros paquetes que movemos.

En la siguiente imagen se esquematiza los cambios de punteros que hay que realizar para cambiar un paquete de una pila a otra. Los punteros discontinuos son los que modifican su valor al que indican los punteros en color azul.

![esquema de movimiento de paquetes](https://github.com/Griger/AOC2022/blob/main/5/img/movimiento.png)

````c++
void realizar_movimiento(Celda* &desde, Celda* &a, int numero_paquetes){
    Celda* puntero_auxiliar;
    for (int paquete = 0; paquete < numero_paquetes; ++paquete) {
        puntero_auxiliar = a;
        a = desde;
        desde = desde->paquete_debajo;
        a->paquete_debajo = puntero_auxiliar;        
    }
}
````
1. Observa que pasamos los dos punteros apuntando al comienzo de las dos pilas de paquetes implicadas en el movimiento.
2. Que los pasamos por referencia para que se modifiquen dentro de la función y esos cambios se vean reflejados donde llamemos a la función.
3. Nota el uso del `puntero_auxiliar` para realizar el intercambio de punteros, puesto que si no lo usásemos alguno de los tres valores involucrados en el intercambio se perdería al «machacarlo» en alguno de los tres intercambios que necesitamos hacer.

> Cuando estemos realizando intercambios del valor de variables, necesitaremos una variable auxiliar en la que guardar alguno de los valores intercambiados para recuperarlo en algún momento del intercambio, ya que de otro modo alguno de los datos se perderá.

Una vez se han procesado y realizado todos los moviemientos, solo nos queda mostrar el resultado.

````c++
 while (getline(archivo_entrada, linea)) {
     procesar_movimiento(linea, numero_paquetes, desde, a);
     realizar_movimiento(pilas[desde], pilas[a], numero_paquetes);
 }

 for (int pila = 0; pila < NUM_PILAS; ++pila)
     cout << pilas[pila]->letra;
````

## Liberando la memoria de forma recursiva

Por último vamos a ver cómo liberar la memoria que hemos reservado para cada lista enlazada.

En este caso tenemos que liberar la memoria reservada para cada una de las `Celda` de forma individual, ya que no hemos reservado memoria para todas las celdas de una pila en un solo bloque con el operador `new []`, sino que hemos ido reservando memoria y creando cada una de las celdas de forma iterativa.

Para liberar la memoria de todas las celdas de una determinada pila podríamos seguir el siguiente esquema partiendo de la `Celda` inicial de esa pila, que recordemos tenemos almacenada en el vector de `Celda* pilas`:

1. Almacenar en un puntero auxiliar la dirección de memoria de la siguiente celda a liberar, es decir el campo `paquete_debajo` de la celda en la que nos encontremos.
2. Eliminar la memoria asignada a la celda actual con el operador `delete`.
3. Pasar a la siguiente celda a liberar con el puntero auxiliar, siempre que este no sea `nullptr`, lo que significaría que hemos llegado al final de esa pila.

Sin embargo, y con el objetivo de practicar, vamos a liberar esta memoria de forma recursiva, siguiendo un esquema distinto. Tendremos una función a la que le pasamos un puntero apuntando a la `Celda` cuya memoria queremos liberar, y dentro de esta función seguiremos el siguiente enfoque recursivo:

1. Si el campo `paquete_debajo` no es nulo y, por tanto, hay una celda «más abajo», invocamos a la misma función para esa celda apuntada.
2. Una vez hayamos vuelto de esa nueva llamada a la función, y entonces hayamos liberado la memoria de la celda apuntada, pasamos a liberar la de la celda actual.

Entonces, en esta recursión el caso base sería aquel en el que la celda actual no apunta a ninguna otra celda, y no se ha de volver a llamar a la función. En este caso habríamos llegado al final de la pila, no se harían más llamadas recursivas a la función, «y volveríamos hacia atrás» liberando la memoria de aquellas celdas que hemos ido dejando por el camino de recursión.

````c++
void liberar_memoria(Celda* celda){
   if (celda->paquete_debajo != nullptr)
       liberar_memoria(celda->paquete_debajo);
   
   delete celda;
}
````

Ya solo queda, al finalizar nuestro programa, invocar a esta función para cada una de las pilas:

````c++
for (int pila = 0; pila < NUM_PILAS; ++pila)
   liberar_memoria(pilas[pila]);
````