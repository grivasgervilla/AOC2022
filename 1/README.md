# El problema

Aunque el enunciado lo cuenta de otra forma, para simplificarlo vamos a enunciarlo como sigue:

Tenemos un fichero con una lista de grupos de números **positivos**, cada grupo está separado del siguiente por una línea en blanco. De modo que, por ejemplo, para el siguiente fichero tendríamos dos grupos el $\lbrace 43, 125, 80 \rbrace$ y el $\lbrace 10, 89 \rbrace$:

```
43
125
80

10
89
```

La primera parte del problema consiste en encontrar el grupo para el que la suma de sus elementos es mayor, y devolver esa suma. La segunda parte del problema es muy similar, solo que tenemos que encontrar los *tres* mayores grupos con respecto a la suma de sus elementos, y devolver la suma conjunta de los tres grupos.

Vamos a ver cómo resolvemos estos dos ejercicios.

# Lectura de un fichero de datos en C++

>El trabajo con ficheros no es un objetivo de esta asignatura, con lo que no necesitas conocer esto de cara a los exámenes. Se proporciona el código para la lectura del fichero de entrada para el reto, ya que, de otro modo, sería muy engorroso intentar resolver los retos del Advent of Code.

Una de las características del Advent of Code es que para cada usuario se genera una entrada del problema distinta, unos datos con los que debemos operar para obtener la solución que nos piden, introducirla en la plataforma, y así pasar el reto. El problema que nos encontramos es que estas entrada de datos son muy grandes, tienen muchos valores. Por lo tanto no podemos declarar en el código un vector `int grupo[]` para cada grupo de datos y copiar los datos de la entrada a mano. Sí que podríamos, con mucha paciencia, pero perderíamos muchísimo tiempo. Por ello, a modo de ayuda en el fichero [skeleton.cpp](https://github.com/Griger/AOC2022/blob/main/1/skeleton.cpp) os doy una estructura base con la que vais a poder leer el fichero línea a línea, código el cual voy a explicar a continuación.

Lo primero que hacemos es incluir la librería `fstream`, con esta librería tendremos la utilidad necesaria para definir flujos de entrada y salida a partir de ficheros, con lo que podremos escribir y leer desde ficheros. Nosotros estamos acostumbrados a leer de y escribir en la salida estándar, con `cin` y `cout`; donde la salida estándar suele ser la consola en la que estemos ejecutando nuestro programa. Pues bien, ahora vamos a usar un `fstream` para leer (y si fuese necesario escribir) de un fichero, en lugar de la salida estándar.

```c++
#include <fstream>
```

Y ahora pasamos a leer el código línea a línea, a modo de ejemplo completo, algo más allá del fichero [skeleton.cpp](https://github.com/Griger/AOC2022/blob/main/1/skeleton.cpp), vamos a suponer que queremos ir mostrando por pantalla cada una de las líneas leídas de nuestro código. Entonces la forma de trabajar con ficheros en este código es:

1. Abrimos el fichero para su lectura.
2. Hacemos un bucle con el que iremos leyendo línea a línea el fichero, usando la función `getline` que ya conocéis. Cuando no queden más líneas por leer del fichero, `getline` pondrá el `fstream` (el flujo que hemos creado a partir del fichero de entrada y del que iremos leyendo) en un estado que hará que la comprobación del `while` sea `false` y, por tanto, salgamos del bucle al leer la última línea.
3. Cerramos el fichero.

```c++
string ruta_archivo_entrada = "input.txt";
fstream archivo_entrada;

archivo_entrada.open(ruta_archivo_entrada, ios::in);

if (archivo_entrada.is_open()){
  string linea;
  
  while (getline(archivo_entrada, linea))
    cout << linea << endl;
}

archivo_entrada.close();
```

## Consideraciones sobre el código anterior

1. El archivo que queramos leer, que en este caso hemos supuesto que se llama `input.txt`, estará en el mismo directorio en el que vayamos a generar nuestro ejecutable, ya que la ruta del archivo de entrada se pasa relativa al ejecutable. Entonces simplemente tenemos que tener nuestro archivo de entrada `.txt` en la misma carpeta donde tenemos el `.cpp` con la solución.
2. El `if` del código anterior nos sirve para comprobar si el archivo se ha abierto correctamente, ya que quizás nos hayamos podido equivocar e indicar una ruta de archivo errónea, en cuyo caso no ejecutaríamos el bucle.
3. En el bucle `while`, por cada vuelta, guardamos en la variable `linea` la línea del fichero que acabamos de leer, y en la siguiente vuelta se leerá la siguiente. El bucle parará cuando no queden más líneas por leer.
4. Si quisiéramos, como será nuestro caso, usar la línea leída como un entero, entonces podremos usar la función `stoi`. La cual convierte un string en el entero correspondiente.

# Solución de la primera parte

Ya hemos visto en clase cómo encontrar el máximo de un vector de valores:

1. Creamos una variable donde almacenaremos el máximo. Inicializándolo a un valor que sea menor o igual que cualquier otro valor que podamos encontrarnos en el vector: $0$ en el caso de trabajar con valores enteros positivos, como es el caso de este problema, o la constante `INT_MIN`, que es el valor *más pequeño posible* que podemos introducir en una variable de tipo `int`. También lo podemos inicializar a `v[0]`; el primer elemento del vector.
2. Ahora pasaríamos a recorrer el vector desde el principio hasta el final, y para cada valor, en caso de que sea mayor que el máximo actual que tenemos, actualizaríamos el valor del máximo a ese nuevo valor, ya que es el valor más grande *que hemos encontrado hasta el momento*.
3. Al final del bucle, por tanto, la variable en la que vamos almacenando el máximo quedará con el valor mayor que hayamos encontrado en nuestro recorrido del vector, es decir, el máximo del vector como nosotros queríamos.

>Recuerda que la primera posición de un vector es la posición `0`, no la `1`. C++ comienza a numerar las posiciones de un vector, al igual que las posiciones de un `string` en 0. Por lo tanto, la última posición de un vector de tamaño $5$, será la `4`, y no la `5`, ya que comenzamos a contar en $0$, y no en $1$.
>
>Así, en general, para un vector de tamaño `tam` tendremos las posiciones desde la `0` hasta la `tam-1`. Es por esto que normalmente en los bucles `for` con los que recorremos los vectores, inicializamos el índice como `int pos = 0`, y paramos antes de llegar a `tam`, `pos < tam`, que sería equivalente a poner `pos <= tam - 1`.

Con la idea en mente de cómo encontrar el máximo de un vector, vamos a buscar, de entre todos los grupos del fichero de entrada, cuál es aquel que tiene la suma de sus elementos mayor. En particular, no nos interesa saber qué grupo es, solo conocer la suma de sus elementos, que será la variable que vayamos almacenando para, si encontramos una suma mayor, actualizar su valor, igual que actualizábamos el valor máximo cuando encontrábamos un elemento más grande en el vector. De aquí ya obtenemos algo: **necesitamos una variable `calorias_maximas` que almacene la suma más grande de calorías que hemos encontrado hasta el momento**.

>Las variables son como cajas 📦 en las que almacenamos valores que vamos a querer utilizar más adelante en nuestro código. Cuando detectemos que un cierto valor que calculemos, o que tengamos porque lo hemos pedido al usuario, o leído de un fichero, lo vamos a necesitar más adelante, entonces lo almacenaremos en una variable del tipo adecuado. Para poder acceder de nuevo a ese valor, y no tener que volver a calcularlo o pedirlo de nuevo al usuario.
>
>Del mismo modo, las variables nos pueden servir para mejorar la legibilidad de nuestro código:
>
>Imagina que tenemos un código que dada la masa de un objeto calcula su peso, con la fórmula $P = m * g$, siendo $g$ la fuerza de la gravedad. Nosotros podríamos tener un código que calculase el peso como `peso = masa * 9.81;`, pero aquí el `9.81` sería un *número mágico*, un número que no se sabe quién qué es (este es un ejemplo muy simple, y podemos deducir qué es ese valor, pero en códigos más complejos sería más difícil dilucidar qué es ese valor). Sería mejor declarar una variable, que la podemos hacer incluso constante, `const float g = 9.81;`, y ya usarla en nuestro código como `peso = masa * g;`, que es mucho más legible, incluso es exactamente como estamos acostumbrados a leer la fórmula de la gravedad, con lo que nuestro código sería más intuitivo y fácil de leer.

Por lo tanto, ahora mismo tenemos el siguiente código (voy a ir generando el código a medida que explico el razonamiento que sigo para escribirlo, aunque evidentemente aquí me salto parte del ensayo-error que implica en muchas ocasiones escribir un programa, pero en general quiero plasmar el razonamiento que he seguido para escribir el código de la solución):

```c++
#include <iostream>

using namespace std;

int main(){
    int calorias_maximas = 0;

    cout << "Las calorias maximas que lleva un elfo son: " calorias_maximas << endl;

    return 0;
}
```

> Como puedes ver, cuando declaro la variable `calorias_maximas` le asignamos el valor `0`, ya que, al igual que hacíamos para el máximo de un vector, necesitamos que la variable donde almacenamos las calorías máximas encontradas hasta el momento tenga un valor de partida lo más pequeño posible para que la lógica de nuestro programa funcione. En este caso como estamos trabajando con enteros positivos, la suma mínima que podemos encontrar es $0$.
> 
> Si no inicializásemos esta variable, correríamos el riesgo de que tuviese un valor aleatorio, un *valor basura*, con lo que nos arriesgamos a que nuestro programa no funcione correctamente.

Ahora que ya tenemos la variable donde vamos a almacenar la suma de calorías máxima que hemos encontrado hasta ese momento, vamos a pasar a leer los datos del fichero. Este código ya lo hemos explicado en la sección anterior.

```c++
#include <iostream>
#include <string>
#include <fstream>

int main(){
    string ruta_archivo_entrada = "input.txt";
    fstream archivo_entrada;
    
    archivo_entrada.open(ruta_archivo_entrada, ios::in);

    int calorias_maximas = 0;

    if (archivo_entrada.is_open()) {
        string linea;

        while (getline(archivo_entrada, linea)) {
            
        }

        cout << "Las calorias maximas que lleva un elfo son: " << calorias_maximas << endl;
        archivo_entrada.close();
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
    
    return 0;
}
```

Así ya tenemos un bucle que va leyendo el archivo línea por línea, y para cada una de esas líneas tendremos que procesarla y hacer con ella lo que necesitemos. En particular:

1. Si es una cadena vacía, sabemos que eso significa que se ha acabado un grupo de calorías.
2. Si no es vacía será una cantidad de calorías nueva, que tendremos que agregar a la suma que tengamos actualmente.

Entonces, como podemos ver tenemos dos opciones, que la cadena sea vacía o que no lo sea, **y para cada una de estas opciones las acciones que tendremos que realizar serán distintas**. Por tanto, aquí usaré un condicional, que hará una cosa u otra dependiendo de si la cadena leía esté vacía o no.

```c++
#include <iostream>
#include <string>
#include <fstream>

int main(){
    string ruta_archivo_entrada = "input.txt";
    fstream archivo_entrada;
    
    archivo_entrada.open(ruta_archivo_entrada, ios::in);

    int calorias_maximas = 0;

    if (archivo_entrada.is_open()) {
        string linea;

        while (getline(archivo_entrada, linea)) {
            if (linea != ""){
                
            } else {
                
            }         
        }

        cout << "Las calorias maximas que lleva un elfo son: " << calorias_maximas << endl;
        archivo_entrada.close();
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
    
    return 0;
}
```

Pensemos ahora en la lógica de nuestro programa: Mientras que estemos encontrando líneas no vacías, sabemos que cada una de esas líneas es una cantidad de calorías que pertenecen al mismo grupo de calorías y, por tanto, tenemos que sumarlas juntas, puesto que queremos saber el grupo de calorías que es más grande en total. Y una vez encontremos una línea en blanco sabremos que hemos acabado ese grupo, y tendremos que comparar la suma de sus calorías, con la suma de calorías máxima encontrada hasta el momento.

Por lo tanto, **necesitamos una segunda variable** donde ir acumulando la suma de calorías del grupo actual, `calorias_grupo_actual`. Variable que luego utilizaremos para compararla con la que almacena el máximo y, si procede, actualizar su valor.


1. Inicializamos a cero la variable `calorias_grupo_actual`, ya que vamos a ir acumulando ahí las calorías del grupo que estemos analizando y, por tanto, no queremos que contenga un *valor basura*.
2. Para cada línea no vacía que encontremos, sabemos que una cantidad de calorías más del grupo actual, con lo que acumulamos su valor para el grupo actual, haciendo uso de la función `stoi` para convertirla en entero.
3. Si la línea que encontramos es vacía habremos llegado al final del grupo actual, con lo que pasaremos a actualizar, si procede, la cantidad de calorías máximas de un grupo. Y además tendremos que re-inicializar a cero la variable donde pasaremos a acumular las calorías del siguiente grupo, la tenemos que volver a poner a cero para que la suma sea correcta. Observa que esto último lo hacemos **fuera del `if`**, tenemos que poner de nuevo esa variable a cero, actualicemos el máximo o no.
4. Por último tenemos que tener en cuenta algo que es una particularidad de la entrada que nos dan desde el Advent of Code. Y es que después del último grupo no hay una línea en blanco. Por lo tanto, para el último grupo no se entra en el `else` del bucle, y no se actualizaría el máximo si es necesario para ese grupo. Por ello, hacemos esto después del bucle `while` para asegurarnos de que hacemos las operaciones necesarias para cada grupo también para el grupo final.

```c++
#include <iostream>
#include <string>
#include <fstream>

int main(){
    string ruta_archivo_entrada = "input.txt";
    fstream archivo_entrada;
    
    archivo_entrada.open(ruta_archivo_entrada, ios::in);

    int calorias_maximas = 0, calorias_grupo_actual = 0;

    if (archivo_entrada.is_open()) {
        string linea;

        while (getline(archivo_entrada, linea)) {
            if (linea != ""){
                calorias_grupo_actual += stoi(linea);
            } else {
                if (calorias_grupo_actual > calorias_maximas)
                    calorias_maximas = calorias_grupo_actual;
                calorias_actuales = 0;
            }         
        }
        
        if (calorias_grupo_actual > calorias_maximas)
            calorias_maximas = calorias_grupo_actual;

        cout << "Las calorias maximas que lleva un elfo son: " << calorias_maximas << endl;
        archivo_entrada.close();
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
    
    return 0;
}
```

# Solución de la segunda parte

En esta segunda parte del problema, en lugar de obtener el grupo con más calorías, y devolver la suma de estas. Lo que tenemos que hacer es obtener **los tres grupos** con más calorías, y calcular la suma de sus calorías en total.

Por tanto, la lógica del problema es la misma, salvo la actualización del máximo. Así, en aquellos puntos donde antes actualizábamos el máximo, que eran en los puntos donde acabábamos de leer un grupo, ahora tendremos que actualizar un ranking de tres grupos. Quedándonos al final con las tres sumas de calorías mayores de entre todos los grupos. Ese ranking son al final tres datos enteros, y que almacenaremos en un vector `int ranking[3]`, el cual iremos actualizando para cada suma de calorías nuevas que obtengamos, igual que hacíamos antes con el mínimo.

Para facilitar la adaptación de la solución anterior al nuevo problema, **y no repetir código**, vamos a crear una función que se encargue de actualizar el ranking cada vez que sea necesario. De modo que en aquellos puntos donde antes actualizábamos el máximo con un `if`, ahora lo que haremos será la función encargada de actualizar el máximo. Veamos primero cómo quedaría el código anterior con esta modificación, y luego pasaremos a ver en profundidad la función.

```c++
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int TOP = 3;

int main() {
    string ruta_archivo_entrada = "input.txt";
    fstream archivo_entrada;

    int calorias_grupo_actual = 0;

    int ranking[TOP] = {0, 0, 0};

    archivo_entrada.open(ruta_archivo_entrada, ios::in);

    if (archivo_entrada.is_open()) {
        string linea;

        while (getline(archivo_entrada, linea)) {
            if (linea != "") {
                calorias_grupo_actual += stoi(linea);
            } else {
                actualizar_ranking(ranking, calorias_grupo_actual);
                calorias_grupo_actual = 0;
            }
        }

        actualizar_ranking(ranking, calorias_grupo_actual);
        archivo_entrada.close();

        int total = 0;

        for (int pos = 0; pos < TOP; ++pos)
            total += ranking[pos];

        cout << "Las calorias totales de los " << TOP << " elfos que llevan mas calorias es " << total << endl;
    } else {
        cout << "Error al abrir el archivo." << endl;
    }

    return 0;
}
```

Observa que el código anterior es muy parecido al de la solución de la primera parte del reto. Además de sustituir la actualización del máximo, por las llamadas a la función, lo único que hemos añadido es sumar los tres elementos finales del ranking para obtener el resultado deseado.

Señalar también que en lugar de usar directamente el valor `3`, que sabemos que es el tamaño del vector en el que almacenaremos el ranking, hemos declarado una constante `const int TOP = 3`, para evitar nuevamente los *números mágicos* y aumentar la legibilidad de nuestro código.

## La función para actualizar el ranking

Para actualizar el ranking hemos definido una función que recibe:

1. El ranking a actualizar, es decir, el vector que queremos modificar.
2. La suma de calorías del grupo actual, que tenemos que introducir en el ranking si procede.

Entonces la cabecera de la función será:

````c++
void actualizar_ranking(int ranking[], int calorias_grupo_actual)
````

No necesitamos que la función devuelva nada, ya que lo único que queremos que haga es que modifique el vector `ranking` que le pasamos como parámetro; por esto la declaramos como una función `void`.

> Ten en cuenta que los vectores en C++ **se pasan siempre por referencia**, es decir, no necesitamos añadir nosotros el `&` para indicar esto.
> 
> Al pasarse por referencia tenemos asegurado que las modificaciones que hagamos en el vector `ranking` que pasamos como parámetro quedará modificado como deseemos.
> 
> Esto también conlleva un riesgo :warning:, y es que habrá casos en los que pasemos un vector, pero no queramos modificarlo, sino solo consultarlo. Por lo tanto, hemos de tener cuidado con **no modificar el vector pasado como parámetro** dentro del código de la función.

Ahora veamos cómo actualizar el ranking:

- En el ranking habrá siempre tres valores, que al principio serán todos $0$.
- Introduciremos un nuevo valor en el ranking si es *mayor que alguno de los valores en el ranking*.
- Puede que un valor sea mayor que varios valores en el ranking, en cuyo caso cambiaremos su valor por el más pequeño de ellos, ya que en el ranking queremos que queden los tres valores mayores. Piensa en que el ranking actual es $\lbrace 30, 20, 10 \rbrace$. Y que ahora queremos ver si el valor $40$ ha de entrar en el ranking. Como es mayor que el $30$ podemos pensar que entonces simplemente tenemos que pasar al ranking $\lbrace 40, 20, 10 \rbrace$, pero esto no sería correcto, ya que el ranking real debería ser $\lbrace 40, 30, 20 \rbrace$, donde hemos sustituido el valor $10$ que, de entre todos los valores menores que $40$, es el menor.

Teniendo esto en cuenta, el algoritmo para actualizar el ranking sería:

1. Buscaremos la posición del vector en la que introducir el nuevo valor si procede (el vector no estará ordenado, para ahorrarnos el paso de ordenar un vector que puede ser más complejo). Inicialmente, la posición donde insertar el nuevo valor será `-1`. Un valor inválido, y en caso de no encontrar ningún valor en el ranking, menor que el nuevo valor, quedará con el valor `-1`, lo que nos servirá como indicativo de que no hay que insertar el nuevo valor en el ranking.
2. Recorremos el ranking. Para cada valor en el ranking, que sea menor que el nuevo valor entonces pueden ocurrir dos cosas:
   - Que la posición sea `-1` y, por tanto, aún no hayamos encontrado ningún otro candidato en el ranking a ser sustituido, es decir, no hemos encontrado ningún otro valor en el ranking que sea menor que el nuevo valor. Entonces la posición pasa a ser la de ese valor del ranking, y **ya no es `-1`**.
   - Que la posición no sea `-1`, lo que significa que ya habíamos encontrado un posible candidato a ser sustituido. En ese caso tendremos que comprobar si el nuevo candidato del ranking es menor que el anterior candidato, y entonces la posición pasaría a ser la de este nuevo candidato.

Con esto en mente el cuerpo de la función pasaría a ser el siguiente:

````c++
void actualizar_ranking(int ranking[], int calorias_grupo_actual) {
    int pos_en_ranking = -1;

    for (int pos = 0; pos < TOP; ++pos)
        if (calorias_grupo_actual > ranking[pos] && (pos_en_ranking == -1 || ranking[pos_en_ranking] > ranking[pos]))
            pos_en_ranking = pos;

    if (pos_en_ranking != -1)
        ranking[pos_en_ranking] = calorias_grupo_actual;
}
````

Sobre el código anterior solo queda hacer un apunte, y es sobre la condición del `if`. Como podemos ver, accedemos a `ranking[pos_en_ranking]`. Pero, ¿qué sucede si `pos_en_ranking` vale `-1`? Podríamos pensar que el programa acabará de forma abrupta debido a un error, pero, en cambio, esto no ocurre. ¿Por qué? Por como evalúa C++ las expresiones booleanas. Y es que tenemos la condición `pos_en_ranking == -1 || ranking[pos_en_ranking] > ranking[pos]`, entonces, como lo primero que comprobamos es si `pos_en_ranking` es `-1`, si esto es cierto, que es el caso que puede dar problemas, ya sabemos que toda esa condición es verdadera, puesto que verdadero o lo que sea, es verdadero. Por tanto, C++ no evalúa la segunda parte del o, y no surge el problema comentado. De todos modos, si esto nos resulta lioso, siempre podemos descomponer la condición que hemos usado en el `if` por varios condicionales anidados.

# Otra solución para la parte 1: para repasar la memoria dinámica y otros conceptos

En el fichero [1.cpp](https://github.com/Griger/AOC2022/blob/main/1/1.cpp) os proponemos una solución algo más compleja que la que hemos planteado anteriormente para la parte 1 de este reto. Es mejor hacer las soluciones cuanto más simples mejor. En cambio, hemos decidido elaborar otro tipo de solución en la que se vea involucrada la memoria dinámica, a modo de ejemplo ilustrativo.

Siguiendo un poco más la semántica que da el enunciado original vamos a declarar un `struct Elfo`, en el que para cada elfo almacenaremos:

- Su identificador, como un entero.
- Las calorías que lleva, como un `int *`, de modo que podamos reservar espacio para tantas cifras como registros de calorías haya en la entrada del problema para ese elfo. Habrá elfos que tengan solo dos datos, y elfos que tengan 100.
- El número total de entradas de calorías que se tienen para ese elfo: como para cada elfo tendremos una cantidad distinta tenemos que saber cuántos valores hemos de recorrer para cada uno. No es como reservar un número fijo de posiciones para todos los elfos. Entonces necesitaremos esta variable para luego, por ejemplo, parar en los bucles donde recorramos sus entradas de calorías.

````c++
struct Elfo {
    int id;
    int numero_entradas;
    int *calorias;
};
````

Vamos a declarar también una función que, dados los datos de un elfo, nos devuelta el total de calorías que lleva ese elfo, que será un valor entero. Para ello, como no necesitamos modificar los datos del elfo dentro de la función, pero nos queremos ahorar la copia de pasarlo por valor, pasaremos el objeto `Elfo` por referencia y constante:

````c++
int total_calorias(const Elfo &elfo)
````

El código de esta función es muy sencillo, ya que únicamente necesitamos sumar todas las entrada de calorías que tengamos para ese elfo, para ellos nos ayudaremos del campo `numero_entradas`, para saber cuántos datos recorrer en el bucle `for` que usamos:

````c++
int total_calorias(const Elfo &elfo) {
    int suma_calorias = 0;

    for (int pos = 0; pos < elfo.numero_entradas; ++pos) {
        suma_calorias += elfo.calorias[pos];
    }

    return suma_calorias;
}
````

> Aquí podemos ver cómo para recorrer los distintos datos de la memoria reservada por el campo `int *calorias`, lo hacemos como lo hacemos para cualquier vector, usando los corchetes. Como sabemos `calorias` apunta a la primera posición de memoria reservada, y ya, con **aritmética de punteros**, el operador `[]`, se encarga de acceder al dato concreto que necesitemos.

Ahora ya nos queda en el programa principal reservar memoria para toda la información que necesitamos, y rellenar dicha memoria. La reserva de memoria la tenemos que hacer en dos pasos:

1. En primer lugar, vamos a declarar una variable para almacenar los datos de todos los `Elfos`, nuevamente lo vamos a hacer con memoria dinámica, ya que nos sabemos cuántos elfos habrá en nuestra entrada. Con lo que declaramos una variable `Elfo *elfos`, con la que reservaremos memoria más adelante.
2. Una vez tengamos la memoria reservada para guardas los datos de cada elfo, tendremos que reservar, para cada elfo la memoria necesaria para almacenar sus calorías, que habrá que reservar espacio para tantos `int`, como entradas de calorías para cada elfo en particular haya en la entrada de nuestro programa.
3. Una vez hagamos esto, rellenaremos estas últimas porciones de memoria reservadas con los datos correspondientes para cada elfo.

> Nos podríamos preguntar cómo sabes cuánta memoria tenemos que reservar para almacenar todos los elfos, en el primer paso anterior, si no sabemos cuánta memoria va a necesitar cada elfo para almacenar sus calorías.
> 
> Esto es muy sencillo, y es que cuando reservamos memoria para los elfos, no reservamos memoria para almacenar sus datos de calorías, reservamos memoria solo para almacenar un puntero a `int`, que apuntará a la porción de memoria que reservemos a posteriori para las calorías de cada elfo. Por tanto, en la porción de memoria reservada para `elfos`, **no tenemos almacenada también la información de las calorías de cada elfo**, tenemos únicamente reservada la dirección de memoria a partir de la cual encontramos esa información para cada elfo, y C++ sí que sabe cuánto ocupa esa información, en concreto en este caso ocupará lo que pese un puntero a `int`, que será el mismo peso para todos los elfos.
> 
> Las porciones de memoria reservadas para las calorías de cada elfo estarán dispersas por memoria (como se representa en la siguiente imagen), y en la variable `elfos`, para cada posición (para cada elfo), se almacenará únicamente el puntero a esa porción de memoria, representados por las flechas en la imagen.
> 
> ![representación de la memoria dinámica para los elfos](https://github.com/Griger/AOC2022/blob/main/1/img/memoria-dinamica.png)

Para hacer estas reservas de memoria, y luego introducir los datos en sus respectivas posiciones, tendremos que leer el fichero tres veces. Por el modo que tiene C++ de leer los ficheros, podemos pensar que tenemos un cursor, que es como cuando las personas que están comenzando a aprender a leer usan un dedo para indicar por dónde van leyendo. Entonces, en C++ cuando llegamos al final del fichero, ese dedo se queda justo al final de la página, y si queremos volver al comienzo tenemos que colocar de nuevo ese dedo al comienzo de forma explícita. Para ello, en el código empleamos las siguientes dos líneas, las cuales aparecerán varias veces en el código, cada vez que queramos volver a leer el fichero de entrada desde el principio.

````c++
archivo_entrada.clear();
archivo_entrada.seekg(0, ios::beg);
````

A continuación voy a describir el resto del código novedoso con respecto a la solución que hemos comentado anteriormente, sin detenerme por ejemplo en explicar de nuevo el código para leer el archivo línea por línea. Así, lo primero que hacemos es declarar la variable que apunta a la región de memoria donde almacenaremos la información de los elfos.

## Reservando memoria: 2 niveles de memoria

````c++
Elfo* elfos;
````

Y después, contaremos cuántas líneas en blanco hay en el documento para saber cuántos elfos existentes (sumando uno más, ya que recordemos que al final del último grupo de entradas no encontramos una línea en blanco).

````c++
while (getline(archivo_entrada, linea)) {
            if (linea == "") numero_elfos++;
        }

numero_elfos++;
````

Una vez que tenemos el número de elfos que existen podemos reservar la memoria que necesitamos para almacenar la información de cada elfo:

````c++
elfos = new Elfo[numero_elfos];
````

Así ahora la variable `elfos` apunta al comienzo de una región de memoria que hemos reservado y que tiene espacio para tantos elfos como hayamos contado en `numero_elfos`. Ahora, para cada elfo, he de hacer que su campo `calorias` sea un puntero que apunte a una región de memoria con tamaño suficiente para almacenar tantas entradas de caloría, tantos `int`, como haya para él en el fichero:

1. Al igual que cuando sumábamos las calorías de cada grupo, contaremos líneas no vacías, que será el número de líneas que pertenezcan al elfo actual.
2. Cuando lleguemos a una línea en blanco sabremos que hemos llegado al final de la información de ese elfo, y pasaremos a reservar para él tanta memoria como sea necesaria. Así como a actualizar el valor de su campo `numero_entradas_inventario`.

````c++
while (getline(archivo_entrada, linea)) {
   if (linea != "") {
       numero_entradas_inventario++;
   } else {
       elfos[contador_elfos].numero_entradas = numero_entradas_inventario;
       elfos[contador_elfos].calorias = new int[numero_entradas_inventario];
       numero_entradas_inventario = 0;
       contador_elfos++;
   }
}
````
El siguiente bucle en el que para cada elfo rellenamos sus datos de calorías no vamos a explicarlo en profundidad, ya que creemos que tiene un funcionamiento claro una vez visto todo lo anterior.

Entonces, ya tenemos toda la información que necesitamos para los elfos, solucionar el problema es tan sencillo como cualquier problema para encontrar el máximo valor en un vector. Ya hemos visto, cuando hemos explicado el código de la función `total_calorias` que cuando tenemos un puntero apuntando a una región de memoria que contiene $n$ objetos de un cierto tipo, podemos usar la aritmética de punteros para con el operador `[]` acceder a cada uno de esos elementos de manera ordenada. Entonces el código con el que buscamos la máxima suma de calorías es el que siempre usamos para buscar el máximo elemento de un vector. La única diferencia es que ahora, en lugar de comparar directamente el valor `v[i]` con el máximo actual, lo que comparamos es el valor devuelto por la función `total_calorias` para cada elfo.

Y una vez tenemos ese máximo lo único que nos queda es liberar la memoria. Que igual que antes hemos reservado en dos pasos, ahora también la tendremos que liberar en dos pasos, *de dentro hacia fuera*.

## Liberando memoria: 2 niveles de memoria

Si nos fijamos en el esquema de memoria reservada que hemos mostrado antes, vemos que tenemos una primera memoria reservada para los elfos, **dentro de la cual tenemos los punteros que referencia a las otras regiones de memoria que hemos reservado**, en las cuales almacenamos las calorías de cada elfo.

Entonces, si liberásemo primero la memoria destinada a almacenar la información de cada elfo perderíamos esos punteros, por tanto, perderíamos las únicas referencias que tenemos al resto de regiones de memoria que hemos reservado, y no las podríamos liberar.

Así que para hacerlo correctamente tenemos que primero liberar la memoria asignada a cada elfo para almacenar sus calorías. Y una vez tenemos estas regiones liberadas y, por tanto, no nos hacen falta los punteros, pasamos a liberar la región de memoria donde almacenamos la información de los elfos.

````c++
for (int pos = 0; pos < numero_elfos; ++pos) {
    delete[] elfos[pos].calorias;
}

delete[] elfos;
````

> Recuerda que cuando hemos reservado memoria para varios objetos que se almacenan de forma contigua, reservando memoria con los corchetes, para liberarla también has de usar los corchetes.