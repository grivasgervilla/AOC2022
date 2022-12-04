# Día 2 :rock: :page_facing_up: :scissors:

El reto consiste en su primer parte, consiste en, dadas unas partidas de Piedra, Papel y Tijeras, de las cuales nos dan lo jugado por el contrincante, y lo jugado por nosotros, determinar la puntuación total obtenida a lo largo de todas las partidas de la entrada que nos proporcionen.

En concreto, para cada línea del archivo de entrada tenemos, una primera letra que representa lo jugado por el contrincante, un espacio, y otra segunda letra que representa lo jugado por nosotros. Según el siguiente código:

|Letra contrincante|Representa|Letra nuestra|
|---|---|---|
|A|Piedra|X|
|B|Papel|Y|
|C|Tijeras|Z|

Para cada partida recibiremos unos puntos según dos parámetros, que se sumarán:

* El resultado de la partida: ganada, empatada o perdida.
* Lo que hayamos elegido jugar: piedra, papel o tijeras.

En la siguiente tabla resumo estas puntuaciones:

|Resultado de la partida|Ptos.|Elección|Ptos.|
|---|---|---|---|
|Perdida|0|Piedra|1|
|Empatada|3|Papel|2|
|Ganada|6|Tijeras|3|

# Solución a la primera parte

Lo primero que hacemos es crear el esqueleto con el que procesaremos el archivo de entrada, para leerlo línea por línea, ya que cada línea es un dato; la información de una partida. Esto ya lo hemos visto en el reto del Día 1, con lo que no vamos a explicarlo aquí.

````c++
#include <iostream>
#include <fstream>

using namespace std;

int main(){
string ruta_archivo = "input.txt";
fstream archivo_entrada;

archivo_entrada.open(ruta_archivo, ios::in);

string linea;

while (getline(archivo_entrada, linea)){
    //Procesamiento de cada linea.
}

archivo_entrada.close();

return 0;
}
````

Cada línea representa una partida, para la cual obtendremos una puntuación, la cual acumulares en una variable `puntuacion_total`. En este caso necesitamos una variable para ir acumulando la puntuación, ya que de otro modo, no tendríamos una forma de almacenar la puntuación de las partidas leídas hasta el momento.

> Las varibles son cajas en las que guardamos valores que vamos a tener que utilizar en el futuro. En este caso, tenemos que ir guardando la puntuación acumulada hasta el momento para seguir acumulando la puntuación de las partidas que nos queden por leer.
> 
> Además, el uso de variables, **con nombres significativos**, nos ayuda a aumentar la legibilidad de nuestro código, lo que no solo ayudará a otros a entender el código, sino también a nosotros para la posible depuración de errores: un código legible y bien escrito (lo que incluye el correcto uso de las tabulaciones para remarcar los distintos niveles en el código) nos facilitará mucho el trabajo a la hora de entender qué hemos hecho y en qué nos podemos haber equivocado.
>
> No es lo mismo, por ejemplo, mostrar por pantalla a través de un `cout` directamente el resultado de un cálculo complejo, quizás por una fórmula compleja, que almacenar previamente ese resultado en una variable, darle a esta variable un nombre significativo como `fuerza_de_rozamiento`, y luego mostrar esa variable por pantalla con el `cout`. La persona que esté leyendo el código, simplemente por el nombre que le hemos dado a la variable, sabrá que se está calculando la fuerza de rozamiento mediante ese cálculo complejo.

Para aumentar la legibilidad del código vamos a definir una función que, dada una cadena de texto, que será una línea del archivo de entrada, la procesará y devolverá la puntuación total obtenida según el resultado y lo que hayamos jugado nosotros.

Antes de pasar a la función que se encargue de procesar esta partida, veamos cómo queda el código final de nuestra función `main`:

````c++
#include <iostream>
#include <fstream>

using namespace std;

int main(){
    string ruta_archivo = "input.txt";
    fstream archivo_entrada;

    archivo_entrada.open(ruta_archivo, ios::in);

    string linea;
    int puntuacion_total = 0;

    while (getline(archivo_entrada, linea))
        puntuacion_total += procesar_partida(linea);

    archivo_entrada.close();

    cout << "La puntuacion total obtenida es: " << puntuacion_total << endl;

    return 0;
}
````

El código para resolver el problema quedaría así, siguiendo el esquema que ya hemos usado muchas veces para calcular la suma de varios valores. En esta ocasión en lugar de sumar los elementos de un vector, o los valores introducidos por un usuario hasta que introduzca un `-1`, estamos sumando la puntuación de cada partida.

Si en el caso de sumar los valores introducidos por un usuario teníamos un bucle `while` donde la condición de parada era algo como `valor_introducido != -1`, ahora la condición es que no hayamos llegado al final del archivo. Y si antes íbamos acumulando el `valor_introducido` en una variable, ahora hacemos lo mismo, pero acumulando las puntuaciones que obtenemos al procesar cada partida mediante la función `procesar_partida`, que nos devolverá un valor entero que será la puntuación de la partida procesada.

Y aquí nos vamos a deter un momento, y es entender cómo funcionan las funciones, o cómo podemos pensar en ellas. En esencia las funciones son elementos que reciben una entrada y devuelven una salida. De modo que allí donde se usan solo tenemos que preocuparnos de pasarles los argumentos correctos, y usar el valor que nos devuelven como nos interese: ya sea introduciendo ese valor en una variable, mostrándolo por pantalla o, como es el caso, acumulándolo en una variable. Pero lo que devuelven no es algo especial, es simplemente un dato del tipo que especifiquemos en la cabecera de la función. Si indicamos que la función devuelve un entero, podremos manejar el valor devuelto por la función como manejaríamos cualquier entero: lo podemos mostrar por pantalla, sumarlo con otro entero, multiplicarlo por dos...

Si antes teníamos una variable, por ejemplo `int valor_importante`, y lo usábamos por el código por ejemplo al hacer `cout << valor_importante << endl;`, ahora el valor devuelto por la función estará representado por esa llamada a la función, por ejemplo, `cout << calcular_valor_importante(argumentos) << endl;`.

En esencia podemos pensar en las funciones como las máquinas industriales, en las que, por un lado, entran los ingredientes como el cacao o las avellanas, los argumentos, y al final de la máquina van saliendo botes de una crema de cacao de la que no diremos la marca, puesto que no patrocinan estos tutoriales. Y nosotros no sabemos que ha pasado por dentro de la máquina, sabemos qué ha entrado y qué ha salido, pero no qué se hace dentro de la máquina para producir ese resultado a partir de esa entrada.

Por ello, el código `main` queda tan limpio. Hemos pasado la tarea de hacer el cálculo de la puntuación a una función externa, y en el `main` nos limitamos a usar dicha función.

> Las funciones, para el código donde se utilizan, o donde se *invocan*, son cajas negras, a las que se le pasan unos argumentos, y tras una serie de operaciones de las que no es consciente el código en el que se invoca la función, devuelve un resultado del tipo indicado, que podremos utilizar como cualquier otro dato o variable.
> 
> ![representación esquemática de funciones](https://github.com/Griger/AOC2022/blob/main/2/img/funciones.png)

## La función para procesar una partida

La función para procesar la partida recibirá una línea del archivo, es decir, un `string`, y devolverá un `int` que será la puntuación de la partida. Por tanto, la cabecera de esta función será:

````c++
int procesar_partida (const string &info_partida)
````

Pasamos la línea como constante y por referencia, ya que no necesitamos modificarla.

Bien, esta función va a tener dos partes, que para modularizar más el código, lo cual casi siempre es beneficioso, vamos a realizarlas en dos funciones distintas:

````c++
int bonus_por_eleccion (string eleccion);

int bonus_por_resultado (string eleccion, string eleccion_contrincante);
````

Además, para hacer más legible el código, vamos a encargarnos de traducir las letras que aparecen en la entrada del problema por «piedra», «papel» o «tijeras», para ello vamos a definir una función adicional que reciba el `char` de la entrada del programa y devuelva el `string` correspondiente, según el código que hemos visto al comienzo del programa. 

Y para evitar errores en nuestro código, ya que luego tendremos que ir comparando estas cadenas y ver si son `"piedra"`, `"papel"` o `"tijeras"`. Para evitar tener que escribir estas cadenas del texto en distintos puntos del código, que no dejarían ser *valores mágicos*, y que podemos equivocarnos al escribir en alguna ocasión alguna de las cadenas, y poner por ejemplo `"tiejras"`, lo que podría resultar en un error de compilación, o **lo que es peor** de ejecución (con un comparmiento incorrecto de nuestro programa, que veamos a priori a qué puede deberse), vamos a declarar cadenas de texto constantes, que serán las que luego usemos en nuestro código para hacer las comparaciones, evitando errores.

> Evita usar *valores mágicos* en tu código, son una fuente de errores constante, y además disminuyen la legibilidad de tu código.
> 
> Si hay algún valor, como una cadena de texto o una cifra, que vas a usar a lo largo de tu código, y que no va a ser modificado, declara al comienzo de tu código una variable constante donde almacenes ese valor, y luego usa esa variable allí donde usarías el valor.

````c++
const string PIEDRA = "piedra";
const string PAPEL = "papel";
const string TIJERAS = "tijeras";

string traducir_eleccion (char eleccion){
    string traduccion;

    if (eleccion == 'A' || eleccion == 'X')
        traduccion = PIEDRA;
    else if (eleccion == 'B' || eleccion == 'Y')
        traduccion = PAPEL;
    else
        traduccion = TIJERAS;

    return traduccion;
}
````

Con esta función simplemente vamos a pasar las entradas del problema a unos valores más legibles, de este modo el código del resto de funciones será más legible, puesto que en lugar de operar como `'X'` o `'C'`, que no sabemos qué significa, operaremos con cadenas de texto legibles, y que serán fácilmente relacionadas con el contexto del problema que estamos tratando.

Una vez tenemos este traductor, que como vemos consiste simplemente en una estructura condicional, que se encarga de traducir cada posible caracter de la entrada, en la cadena correspondiente, pasamos a ver el código de la función que se encarga de procesar cada partida:

1. Traducimos la información de cada partida. Sabemos que el primer caracter de la línea es la letra que indica la elección del contricante, y que la tercera (hay un espacio en blanco) es el caracter que representa nuestra elección.
2. Una vez tenemos traducidas las dos elecciones, simplemente devolvemos la suma de los dos bonus de puntuación que calcularemos con sendas funciones, que veremos más adelante.

````c++

int procesar_partida (const string &info_partida) {
    string eleccion_nuestra = traducir_eleccion(info_partida[2]);
    string eleccion_contrincante = traducir_eleccion(info_partida[0]);

    return bonus_por_eleccion(eleccion_nuestra) + bonus_por_resultado(eleccion_nuestra, eleccion_contrincante);
}
````

Observa lo limpio y claro que queda el código de esta función, simplemente realiza la traducción, y luego devuelve la suma de los dos valores devueltos por las dos funciones que se encargan de calcular los dos bonus de puntuación. Si no tuviésemos esas dos funciones auxiliares, tendríamos todo el código necesario para calcular los dos bonus en el cuerpo de esta función, lo que resultaría en un código menos legible y más lioso. Así, **modularizando** nuestro código queda más compartimentado y limpio, facilitando la corrección de errores.

> Trata de descomponer tu problema en distintas partes, y *encapsula* cada una de estas partes en una función que se encargue **solo y exclusivamente** de resolver ese problema. Luego combina esas funciones en el orden apropiado para resolver tu problema.
> 
> Así obtendrás un código más limpio y claro, facilitándote la corrección de posibles errores. Además, el dividr el problema en subproblemas más pequeños, te facilitarán el razonamiento a la hora de diseñar la lógica de tu código para resolver el problema completo.
> 
> ¡Divide y vencerás!

### Calculando el bonus por elección

Como hemos visto en el enunciado, según qué hayamos escogido recibiremos unos puntos u otros. Entonces, en lugar de hacer simplemente un condicional que, dependiendo qué hayamos escogido, devuelva un valor. Lo que vamos a hacer es declarar tres constantes que almacenan los puntos que recibimos por cada una de las elecciones. Esto tiene dos ventajas:

1. El código es más legible, no tenemos *números mágicos* en el código, sino que todo tiene una semántica. No devolvemos con `return 2;`, devolvemos con `return BONUS_PAPEL;`, lo que resulta más legible, y tiene más carga semántica.
2. Si en un momento dado cambian los puntos que recibimos por cada elección, simplemente tendremos que cambiar el valor de esas varialbes en el código, que estarán fácilmente localizables y sabremos qué valor hemos de actualizar. Si lo hiciésemos con *números mágicos* tendríamos que navegar por el código viendo en qué puntos hemos de cambiar ese valor. Y es que en esta ocasión estas constantes las vamos a usar en una sola línea del código, pero quizás en otros programas un mismo valor se use en varios puntos a través del código. Si tuviésemos que cambiar todas y cada una de las apariciones de ese valor por el nuevo valor, no solo sería más lento, sino que sería mucho más propenso a errores, ya que se nos puede pasar cambiar algún valor.

````c++
const int BONUS_PIEDRA = 1;
const int BONUS_PAPEL = 2;
const int BONUS_TIJERAS = 3;

int bonus_por_eleccion (string eleccion){
    int bonus;

    if (eleccion == PIEDRA)
        bonus = BONUS_PIEDRA;
    else if (eleccion == PAPEL)
        bonus = BONUS_PAPEL;
    else
        bonus = BONUS_TIJERAS;
    
    return bonus;
}
````

### Calculando el bonus por resultado

Para calcular el bonus con el resultado vamos a usar una sentencia condicional anidada. Podríamos buscar soluciones más elegantes, pero esto nos servirá para profundizar un poco más en los condicionales, y entender bien cómo funcionan y cómo podemos anidarlos.

En el siguiente esquema se resumen las distintas bifurcaciones que podemos tener dentro de una partida:

![esquema piedra papel y tijera](https://github.com/Griger/AOC2022/blob/main/2/img/piedra-papel-tijera.png)

Ahora vamos a ir viendo, poco a poco cómo podemos traducir esto en forma de código, viendo tanto el diagrama de flujo del programa, como el código resultante. Recuerda que en los diagramas de flujo representamos las condiciones mediante nodos en forma de rombo (:diamonds:), y las instrucciones secuenciales (por ejemplo los bloques de código que se encuentran dentro de cada `if` y de cada `else`) las representamos con nodos en forma de cuadrado (:yellow_square:).

En un primer intento podríamos comprobar el resultado de la partida para cada una de las elecciones que podemos elegir por separado:

````mermaid
flowchart LR
  subgraph PIEDRA
    direction LR
    cond11{Elige piedra} --> empate1[empate]

	cond12{Elige tijeras} --> victoria1[victoria]

	cond13{Elige papel} --> derrota1[derrota]
  end
  cond1{Elijo piedra} --> PIEDRA

  subgraph TIJERAS
    direction LR
    cond21{Elige piedra} --> empate2[derrota]

	cond22{Elige tijeras} --> victoria2[empate]

	cond23{Elige papel} --> derrota2[victoria]
  end
  cond2{Elijo tijeras} --> TIJERAS

  subgraph PAPEL
    direction LR
    cond31{Elige piedra} --> empate3[victoria]

	cond32{Elige tijeras} --> victoria3[derrota]

	cond33{Elige papel} --> derrota3[empate]
  end
  cond3{Elijo papel} --> PAPEL
````

En este caso, vamos a comprobar cada condición por separado, es decir, usaremos `if` aislados. Un `if` funciona del siguiente modo:

1. Comprobamos la condición entre paréntesis.
2. Si el resultado de esa condición es `true` entonces ejecutaremos las instrucciones que haya en el cuerpo del `if` (si no ponemos llaves `{}` C++ interpretará que el cuerpo del `if` está compuesto únicamente por la primera línea que encuentre, por ello, si en un `if` tenemos una única instrucción no necesitamos poner llaves, **aunque sí es recomendable tabular correctamente esa línea de código, para remarcar que está dentro del `if` y que así nuestro código se lea mejor).

Con el esquema que hemos mostrado anteriormente (donde una flecha indica que se da la condición que tenemos en el nodo con forma de rombo), el código quedaría como sigue:

````c++
if (eleccion == PIEDRA){
    if (eleccion_contrincante == PIEDRA)
        bonus = BONUS_EMPATE;
    if (eleccion_contrincante == TIJERAS)
        bonus = BONUS_VICTORIA;
    if (eleccion_contrincante == PAPEL)
        bonus = BONUS_EMPATE;
}

if (eleccion == TIJERAS){
    if (eleccion_contrincante == PIEDRA)
        bonus = BONUS_DERROTA;
    if (eleccion_contrincante == TIJERAS)
        bonus = BONUS_EMPATE;
    if (eleccion_contrincante == PAPEL)
        bonus = BONUS_VICTORIA;
}

if (eleccion == PAPEL){
    if (eleccion_contrincante == PIEDRA)
        bonus = BONUS_VICTORIA;
    if (eleccion_contrincante == TIJERAS)
        bonus = BONUS_DERROTA;
    if (eleccion_contrincante == PAPEL)
        bonus = BONUS_EMPATE;
}
````

> Cada condicional que pongamos en nuestro código, cada `if` crea un camino alternativo compuesto por todas las instrucciones en el cuerpo de ese `if`. Entonces, si la condición del `if` es verdadera, entraremos en ese camino, lo recorreremos, ejecutando las instrucciones que compongan el cuerpo del `if`, y cuando lleguemos al final seguiremos por el camino normal del código, ejecutando el resto de instrucciones que haya después de ese `if`.

Este código es correcto, y funcionará correctamente. Sin embargo, hay comprobaciones que nos podemos ahorrar, ya que si por ejemplo hemos escogido piedra, no habremos escogido ni tijeras ni papel, con lo que las condiciones de los otros dos `if` serán falsas sí o sí. Por lo tanto, estas comprobaciones realmente serán necesarias **solo si la primera es falsa**, para ello tenemos los `else`, caminos alternativos en nuestro código que se ejecutan cuando la condición que evaluamos en un `if` es falsa. Esto se correspondería con el siguiente diagrama de flujo:

````mermaid
flowchart LR
  subgraph PIEDRA
    direction LR
    cond11{Elige piedra} -- Sí --> empate1[empate]
		cond11 -- No --> cond12

		cond12{Elige tijeras} -- Sí --> victoria1[victoria]

		cond12 -- No --> derota1[derrota]
  end
	cond1{Elijo piedra} -- Sí --> PIEDRA
	cond1 -- No --> cond2

  subgraph TIJERAS
    direction LR
    cond21{Elige piedra} -- Sí --> empate2[empate]
		cond21 -- No --> cond22

		cond22{Elige tijeras} -- Sí --> victoria2[victoria]
		cond22 -- No --> derota2[derrota]
  end
	cond2{Elijo tijeras} -- Sí --> TIJERAS

  subgraph PAPEL
    direction LR
    cond31{Elige piedra} -- Sí --> empate3[empate]
		cond31 -- No --> cond32

		cond32{Elige tijeras} -- Sí --> victoria3[victoria]
		cond32 -- No --> derota3[derrota]
  end
	cond2 -- No --> PAPEL
````

Este diagrama de flujo se traduciría en el siguiente código:

````c++
if (eleccion == PIEDRA){
    if (eleccion_contrincante == PIEDRA)
        bonus = BONUS_EMPATE;
    else {
        if (eleccion_contrincante == TIJERAS)
            bonus = BONUS_VICTORIA;
        else
            bonus = BONUS_DERROTA;
    }
} else {
    if (eleccion == TIJERAS) {
        if (eleccion_contrincante == PIEDRA)
            bonus = BONUS_DERROTA;
        else {
            if (eleccion_contrincante == TIJERAS)
                bonus = BONUS_EMPATE;
            else
                bonus = BONUS_VICTORIA;
        }
    }
    else {
        if (eleccion_contrincante == PIEDRA)
            bonus = BONUS_VICTORIA;
        else {
            if (eleccion_contrincante == TIJERAS)
                bonus = BONUS_DERROTA;
            else
                bonus = BONUS_EMPATE;
        }
    }
}
````

Con este código ya evitaremos las comprobaciones que no son necesarias en cuanto una de las anteriores es correcta, sin embargo hay un modo más compacto de escribirlo, y es que como hemos dicho, si no ponemos llave, C++ asumirá que el cuerpo del `if` o del `else` está compuesto por una sola línea de código, la siguiente que se encuentre. Entonces podemos escribir en la misma línea un `else` y el `if` siguiente que queremos comprobar **dentro de ese `else`**. De este modo, C++ interpretará que para ese `else` se ha de ejecutar la siguiente línea, el `if`, y ya entraríamos en las bifurcaciones correspondientes a ese `if`. El funcionamiento es el mismo, solo que lo escribimos de un modo más compacto:

````c++
if (eleccion == PIEDRA){
    if (eleccion_contrincante == PIEDRA)
        bonus = BONUS_EMPATE;
    else if (eleccion_contrincante == TIJERAS)
            bonus = BONUS_VICTORIA;
    else
            bonus = BONUS_DERROTA;
} else if (eleccion == TIJERAS) {
    if (eleccion_contrincante == PIEDRA)
        bonus = BONUS_DERROTA;
    else if (eleccion_contrincante == TIJERAS)
        bonus = BONUS_EMPATE;
    else
        bonus = BONUS_VICTORIA;
} else {
    if (eleccion_contrincante == PIEDRA)
        bonus = BONUS_VICTORIA;
    else if (eleccion_contrincante == TIJERAS)
        bonus = BONUS_DERROTA;
    else
        bonus = BONUS_EMPATE;
}
````

Observa que también cambiamos la tabulación del código para que quede algo más legible. Por ejemplo cuando el usuario elige piedra, y pasamos a comprobar la elección del contrincante, el último `else` no lo ponemos a la misma altura de la palabra `if` anterior (aunque realmente está relacionado directamente con él, ya que ese `else` se ejecutará si el `if` anterior evalúa a falso), si no que lo ponemos a la altura de la palabra `else` anterior. De este modo, aunque la tabulación no afecta para nada en cómo funciona el código, sí que dotamos al código de una mayor carga semántica. Ahora es como si tuviésemos tres caminos paralelos, ejecutando, de izquierda a derecha, solo el primero que evalúa a verdadero:

- Si el contrincante elige piedra tendremos un empate.
- En caso contrario pasamos a ver si ha elegido tijeras, y si es el caso tendremos victoria.
- Y por último, si esta condición tampoco es verdadera pasamos al tercer y último camino, en cuyo caso tendremos derrota.

Con este último código completamos la función `bonus_por_resultado`:

````c++
int bonus_por_resultado (string eleccion, string eleccion_contrincante){
    int bonus;
    
    if (eleccion == PIEDRA){
        if (eleccion_contrincante == PIEDRA)
            bonus = BONUS_EMPATE;
        else if (eleccion_contrincante == TIJERAS)
            bonus = BONUS_VICTORIA;
        else
            bonus = BONUS_DERROTA;
    } else if (eleccion == TIJERAS) {
        if (eleccion_contrincante == PIEDRA)
            bonus = BONUS_DERROTA;
        else if (eleccion_contrincante == TIJERAS)
            bonus = BONUS_EMPATE;
        else
            bonus = BONUS_VICTORIA;
    } else {
        if (eleccion_contrincante == PIEDRA)
            bonus = BONUS_VICTORIA;
        else if (eleccion_contrincante == TIJERAS)
            bonus = BONUS_DERROTA;
        else
            bonus = BONUS_EMPATE;
    }
    
    return bonus;
}
````

> Observa que, aunque en algunos de los condicionales sabemos que tenemos que devolver el bonus por victoria, derrota o empate, en lugar de poner en cada uno de estos condicionales un `return`, lo que hacemos es declarar una variable que ponemos al valor que corresponda devolver, y **al final del código tenemos un único return**.
> 
> Esto nos puede ahorrar ciertos errores, ya que a veces ponemos un `return` porque creemos que la función puede acabar ahí y que nos ahorraremos así pasos. Sin embargo, hay ocasiones en las que no hemos programado bien nuestra función, y cuando falla no sabemos por qué, en ciertos casos porque no nos estamos dando cuenta de dónde está acabando nuestra función, porque tenemos varios `return` en su código, y esto nos hace más complicado controlar el comportamiento de la función.
> 
> Por ejemplo, podemos equivocarnos y poner unos de estos `return` dentro de un `for` interno de dos bucles `for` anidados, cuando realmente solo lo queremos poner en el `for` externo. Quizás, si no tuviésemos ese `return` adicional sería más fácil comprobar en qué nos estamos equivocando.