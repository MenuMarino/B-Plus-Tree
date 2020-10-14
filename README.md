# Proyecto 1
Base de Datos 2
Link de la exposición: https://youtu.be/NmioLjTUvss

## Integrantes
* Benjamín Díaz
* Gabriel Spranger
* Rodrigo Céspedes

## Observaciones

* Compilar con C++ 17. y cambiar de branch a ExtendibleHashing (git checkout feature/ExtendibleHashing) (en realidad debería ser Static Hashing) para probar el static hash.


## Introducción

El objetivo del proyecto es desarrollar dos estructuras de indexación que son ampliamente usadas en el campo de las bases de datos: el árbol B+  y el static hashing. Para esto, trabajaremos sobre un dominio de datos que generamos nosotros que consisten en cuatro campos: **ID** (unsigned), **nombre** (char \[20\]), **PIN** (short), **país** (char \[35\]). Este archivo es de longitud fija. Finalmente, los resultados que deseamos obtener es que ambas estructuras de indexación hagan la búsqueda de los registros más rápida y que reduzcan el número de accesos a memoria secundaria.

## Técnicas Usadas

- Describa brevemente las técnicas de indexación de archivos que ha elegido. Explique procedimentalmente el proceso de inserción, eliminación y búsqueda.

### B+ Tree

El B+ tree es una estructura de datos que permite accesos logaritmicos a memoria secundaria. Todos los datos están almacenados en los nodos hoja y además estos están linkeados mediante una lista enlazada, lo cual permite que podamos hacer búsquedas secuenciales (búsqueda por rango). 

#### Búsqueda

A la función que hace la búsqueda, le pasamo el key del registro que queremos encontrar. Inicialmente, se hace la llamada desde el root, ya que a este siempre lo tenemos en memoria principal. Luego, ubicamos el puntero al hijo correcto para que hagamos la búsqueda recursiva. Cabe resaltar que como estamos manejando el B+ en disco, este "puntero" es en realidad un offset en el archivo donde tenemos todos los nodos guardados. Luego de ubicar el children (offset) correcto para poder hacer la búsqueda recursiva, leemos el nodo de disco mediante la función **readNode** y le pasamos como parámetro el archivo y el offset, el cual es igual a **ptr->children[index]**. Leemos ese nodo, y se lo pasamos a la llamada recursiva para continuar con la búsqueda. En caso de que el nodo en el que nos encontremos, en el proceso de la búsqueda, sea un nodo hoja, entonces iteramos sobre los keys de ese nodo para ver si está el key que queríamos encontrar, si es así, entonces retornamos un iterador a ese nodo, con la posición (index) del key que encontramos, sino, retornamos nullptr, ya que no podemos seguir buscando recursivamente.

![inserción](busqueda.png)

#### Inserción

Tenemos dos tipos funciones que se encargan de la inserción: **insert_into** y **insert**. **insert_into** se encarga de insertar el key y acomodar los children y los registros de cada nodo, es decir, solo inserta el dato en el nodo. Luego, **insert**, mira si el número de keys en el nodo ha sobrepasado el orden del árbol, si es así, entonces hacemos el split, sino, dejamos el nodo como está. Ahora, **insert**, usa la misma técnica que usamos en el find para encontrar la posición correcta del key para poder insertarlo. Hay dos casos mientras hacemos esta búsqueda recursiva: el nodo en el que estamos es un nodo interno o es un nodo hoja. Cuando estamos en un nodo interno, localizamos el índice por el que tenemos que continuar la búsqueda y leemos el hijo en esa posición, es decir, llamamos **readNode** y le pasamos como parámetro el archivo y el offset, el cual es igual a **ptr->children[index]**. Una vez que hemos leído ese nodo, continuamos la búsqueda recursiva. Cuando regresamos de la llamada recursiva, vemos si el estado es OK o OVERFLOW, si es OK, entonces solo escribimos el nodo en memoria secundaria, ya que lo hemos modificado, si es OVERFLOW, entonces llamamos split. Split lo que hace es crear dos nuevos nodos, copiar los hijos, keys y registros del nodo que se va a splitear a ambos hijos y luego escribe en memoria secundaria ese mismo nodo (ya que acaba de ser modificado), y sus dos nuevos hijos. Cuando estamos en un nodo hoja, simplemente llamamos a la función **insert_into** para insertar el key y el registro en la posición correcta en el nodo y luego escribimos ese nodo en disco, ya que lo acabamos de modificar. Hacemos un procedimiento análogo con el root, el cual tiene su propio método **split_root** el cual es casi igual al **split**.

![Split](split.png)
![Insert](insert.png)
![Insert Into](insertinto.png)

### Static Hashing

El static hashing es una técnica utilizada para almacenar datos y llevar un registro de posiciones para acceso rápido en un set de datos no ordenados. Permite accesos en O(1 + k), k siendo el número de buckets que se cargan a memoria (se toma en cuenta el overflow). Este método de indexación consta de una tabla hash, como key se tiene la llave del registro (pasada por una función hash) y como value se tiene la dirección lógica del bucket que le corresponde a esa llave hasheada. 

Cada Bucket tiene n espacios para almacenar registros y un puntero de overflow, cuando existe overflow, se revisa si es que existen buckets linkeados con espacio disponible, si no es así, se crea uno nuevo y se inserta ahí, los punteros de overflow se actualizan en cada iteración.

La tabla hash también se guarda en disco al terminar el programa, se guarda una lista de keys y values y se reconstruye cuando se inicia el programa.


#### Búsqueda

Para la búsqueda se provee una llave. Esta llave es hasheada aplicando módulo con la capacidad del Static Hash (definida previamente en el constructor). 

Paso 1:
Se busca dentro del hash, si es que no existe una entrada, se imprime en pantalla que no ha sido encontrado, pero si si existe una entrada accede al archivo de buckets en la posición dada por el value de esa entrada del hash, construye el bucket y va al paso 2.
Paso 2:
Se revisa dentro de el bucket de manera lineal si es que existe un registro con la llave provista . Si es que lo encuentra, imprime el valor, si es que no, se va al paso 3.
Paso 3:
Se revisa si existe un puntero de overflow con una dirección válida en el bucket, si es que no existe, se imprime en pantalla que no ha sido encontrado, si es que si, se carga el bucket de overflow en memoria accediendo a su dirección y se regresa al paso 2.

![Search](searchaccess.png)

#### Inserción

La inserción se hace de manera análoga a la búsqueda. Primero se hashea la llave del registro provisto y se revisa si existe una entrada en la tabla hash, si existe, se procede al proceso A. Si no existe, se procede al proceso B.

A:
Se revisa si hay espacio disponible para insertar y lo inserta. Si no, se revisa si tiene un bucket de overflow, si lo tiene se accede a él y se repite el proceso A. Si no tiene espacio y no tiene bucket de overflow, lo crea, linkea los punteros y lo inserta en el archivo de datos en la última posición.
![Caso A](caseA.png)

B:
Se crea un nuevo bucket, se crea la entrada en el hash, se inserta el registro en el bucket y luego se inserta el bucket al final del archivos de datos

![Caso B](caseB.png)

## Resultados Experimentales

- Cuadro y/o gráfico comparativo de desempeño de las técnicas de indexación de archivos sobre el dominio de datos. Tanto para inserción como para búsqueda.
- Considerar dos métricas: total de accesos a disco duro (read & write) y tiempo de ejecución en milisegundos.

### B+ Tree v.s Static Hashing

![Cuadro Comparativo 1](cuadro1.png)
![Cuadro Comparativo 2](cuadro2.png)

- Discusión y Análisis de los resultados experimentales.

### Discusión y Análisis

Como dato curioso, inicialmente corrimos las pruebas con el static hash, en una computadora con un i3 y 1TB de HDD, y corrimos las pruebas del B+ en una computadora con un i9 y un 1 TB de SDD. Al ver los resultados, el static hash tenía 10 veces menos accesos a disco que el B+ en la inserción; sin embargo, el B+ corría 10 veces más rápido que el static hash. Esto nos pareció raro, ya que en teoría el B+ debería demorarse más dados los mayores accesos a disco, pero luego nos dimos cuenta que era porque el static hash estaba en HDD y el B+ estaba en un SSD con NVMe, lo cual explicaba los resultados.

En el primer cuadro, podemos ver el tiempo de ejecución de insertar 1 y 200 registros al B+ y al Static Hash. En el segundo cuadro, podemos ver el número de lecturas y escrituras al insertar y buscar 200 registros en el B+ y en el Static Hash.

Como el B+ usa principalmente dos funciones utilitarias llamadas **readNode** y **writeNode**, las cuales leen y escriben un nodo en disco, respectivamente, decidimos crear dos variables globales llamadas **reads** y **writes**. En la función **readNode**, aumentamos **reads** en uno, ya que es un acceso a disco. Un caso análogo ocurre con **writeNode** y **writes**. La razón por la que hacemos esto, es que en teoría, solo se tiene que contar las lecturas y escrituras de nodos, ya que cada nodo ocupa un bloque de memoria.

Para contabilizar los reads y writes se crean contadores globales al inicio del programa. Cada vez que se hace una operación de write en el método **insert()** se suma 1 al contador, es importante decir que, cuando existe un overflow y se tiene que escribir sobre otro bucket, el contador también aumenta, pues eso cuenta como un write. Para los reads, se hace de la misma manera, pero esta vez contabilizándolos en los métodos **search()** e **insert()**, pues los dos tienen lecturas. Cada vez que se hace un read para alguno de los posibles escenarios en estas operaciones, se suma uno al contador, es decir, también cuenta lecturas extra por overflow.

La primera diferencia que podemos ver es que el número de lecturas en la búsqueda del B+ es menor al número de lecturas en la inserción. Esto se debe a que la inserción tiene que hacer splits, los cuales leen nodos de más para poder modificar sus atributos de tal manera que se mantenga la integridad de la estructura de datos.

Como se puede ver el Static Hash es más rápido que el B+ tree, eso se da por la cantidad de registros que se van a insertar y por el factor de bloque y número de buckets que tiene el static hash. Mientras se van aumentando la cantidad de registros el tiempo de ejecución del static hash va a aumentar, haciendo que el B+ tree sea mejor. Cabe resaltar que el factor de bloque y número de buckets son factores que afectan al tiempo de ejecución del static hash, ya que un factor de bloque de 1 por ejemplo, sería lo mismo que tener un linked list en disco, lo cual baja el performance, mientras un factor de bloque alto es bueno ya que de una lectura de bloque lees varios registros.




