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

# Lectura de un fichero de datos en `C++`

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
3. Si la línea que encontramos es vacía habremos llegado al final del grupo actual, con lo que pasaremos a actualizar, si procede, la cantidad de calorías máximas de un grupo. Y además tendremos que re-inicializar a cero la variable donde pasaremos a acumular las calorías del siguiente grupo, la tenemos que volver a poner a cero para que la suma sea correcta.
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
