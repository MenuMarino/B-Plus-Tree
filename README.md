# Proyecto 1
Base de datos 2

## Integrantes
* Benjamín Díaz
* Gabriel Spranger
* Rodrigo Céspedes

## Introducción

El objetivo del proyecto es desarrolar dos estructuras de indexación que son ampliamente usadas en el campo de las bases de datos: el árbol B+ y el random file. Para esto, trabajaremos sobre un dominio de datos que generamos nosotros que consisten en cuatro campos: ID (unsigned), nombre (char \[20\]), PIN (short), país (char \[35\]). Este archivo es de longitud fija. Finalmente, los resultados que deseamos obtener es que ambas estructuras de indexación hagan la búsqueda de los registros más rápida y que reduzcan el número de accesos a memoria secundaria.

## Técnicas Usadas

- Describa brevemente las técnicas de indexación de archivos que ha elegido. Explique procedimentalmente el proceso de inserción, eliminación y búsqueda.
- Detalle los aspectos importantes de la implementación de dichas técnicas.
- Debe notarse con claridad el manejo de la memoria secundaria.

## Resultados Experimentales

- Cuadro y/o gráfico comparativo de desempeño de las técnicas de indexación de archivos sobre el dominio de datos. Tanto para inserción como para búsqueda.
- Considerar dos métricas: total de accesos a disco duro (read & write) y tiempo de ejecución en milisegundos.
- Discusión y Análisis de los resultados experimentales.

## Observaciones

* Compilar con C++ 17.
