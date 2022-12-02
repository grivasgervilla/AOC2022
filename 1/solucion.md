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

>El trabajo con ficheros no es un objetivo de esta asignatura, con lo que no necesitas conocer esto de cara a los exámenes. Se proporciona el código para la lectura del fichero de entrada para el reto ya que, de otro modo, sería muy engorroso intentar resolver los retos del Advent of Code.

Una de las característica del Advent of Code es que para cada usuario se genera una entrada del problema distinta, unos datos con los que debemos operar para obtener la solución que nos piden, introducirla en la plataforma, y así pasar el reto. El problema que nos encontramos es que estas entrada de datos son muy grandes, tienen muchos valores. Por lo tanto no podemos declarar en el código un vector `int grupo[]` para cada grupo de datos y copiar los datos de la entrada a mano. Sí que podríamos, con mucha paciencia, pero perderíamos muchísimo tiempo. Por ello, a modo de ayuda en el fichero [skeleton.cpp](https://github.com/Griger/AOC2022/blob/main/1/skeleton.cpp) os doy una estructura base con la que vais a poder leer el fichero línea a línea, código el cual voy a explicar a continuación.

Lo primero que hacemos es incluir la libería `fstream`, con esta librería tendremos la utilidad necesaria para debinir flujos de entrada y salida a partir de ficheros, con lo que podremos escribir y leer desde ficheros. Nosotros estamos acostumbrados a leer de y escribir en la salida estándar, con `cin` y `cout`; donde la salida estandar suele ser la consola en la que estemos ejecutando nuestro programa. Pues bien, ahora vamos a usar un `fstream` para leer (y si fuese necesario escribir) de un fichero, en lugar de la salida estándar.

```c++
#include <fstream>
```

Y ahora pasamos a leer el código línea a línea, a modo de ejemplo completo, algo más allá del fichero [skeleton.cpp](https://github.com/Griger/AOC2022/blob/main/1/skeleton.cpp), vamos a suponer que queremos ir mostrando por pantalla cada una de las líneas leídas de nuestro código. Entonces la forma de trabajar con ficheros en este código es:

1. Abrimos el fichero para su lectura.
2. Hacemos un bucle con el que iremos leyendo línea a línea el fichero, usando la función `getline` que ya conocéis. Cuando no queden más líneas por leer del fichero, `getline` pondrá el `fstream` (el flujo que hemos creado a partir del fichero de entrada y del que iremos leyendo) en un estado que hará que la comprobación del `while` sea `false`, y por tanto salgamos del bucle al leer la última línea.
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
4. Si quiesiéramos, como será nuestro caso, usar la línea leída como un entero, entonces podremos usar la función `stoi`. La cual convierte un string en el entero correspondiente.

