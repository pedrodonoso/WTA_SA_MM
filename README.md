# Consideraciones

- Antes de ejecutar, se debe tener en cuenta que la carpeta con las instancias debe estar en la misma ruta que el ejecutable, y debe llamarse "WTA".
- Dimensión se le denominará a la cantidad de armas y objetivos que tiene cada instancia.
- Las instancias deben tener el formato de nombre "wta{dimension}.txt".
- Al ejecutar el algoritmo se generará un archivo de nombre "wta.csv" donde registrará los parametros más importantes, en la sección Log de este archivo se detallarán los parámetros que se imprimen en este archivo csv.

# Ejecutar 

Lo siguiente compilará el código y luego lo ejecutará introduciendo la instancia de 5 objetivos y armas.

## Opción 1:
Esta opción utiliza el archivo makefile solamente para compilar, luego simplemente ejecuta el archivo ejecutable directamente en consola.
-------------------------------------------------
|	$ make compile				                |
|	$ ./main 5 0.98 1000 0.1 100000 1	        |
-------------------------------------------------

## Opción 2:
Esta opción utiliza en todo momento el archivo makefile.
-----------------------------------------------------------------------------------------
|	$ make compile                                                                      |
|	$ make run INS=5 K=0.98 T_INIT=1000 T_FINISH=0.1 MAX_ITER=100000 MOVE=1		        |
-----------------------------------------------------------------------------------------

Luego se realizar la ejecución del algoritmo, este generará un registro en el archivo log llamado "wta.csv", donde imprimirá los parametros más relevantes.

# Árbol de proyecto

- root
    - WTA
        - wta5.txt
        ...
        - wta200.txt
    - main.cpp
    - Makefile

# Movimientos

MOVE=0 # movimiento completamente aleatorio.
MOVE=1 # movimiento con pivot.
MOVE=2 # movimiento swap iterativo.

# Experimentos

Para realizar los experimentos se realizaron dos ejecutables en bash.
Para las pruebas de temperatura el ejecutable se llama "test_temperature.sh".
Para las pruebas de movimiento el ejecutable se llama "test_movements.sh".

Para ejecutar las pruebas se debe ejecutar el siguiente comando:

-------------------------------------
|    $ ./test_temperature.sh        |
|    $ ./test_movements.sh          | 
-------------------------------------

# Log

Ejemplo primeras dos lineas de archivo wta.csv
---------------------------------------------------------
| 5, 1000, 0.1, 0.9, 100000, 48.364, 1, 0.033002, 87	|
| 5, 1000, 0.1, 0.9, 100000, 48.364, 1, 0.00974, 87	    |
| ...							                        |
---------------------------------------------------------

Parametros en órden:
- Dimensión
- Temperatura máxima
- Temperatura mínima
- Coeficiente de decrecimiento
- Cantidad máxima de iteraciones
- Óptimo local final
- Movimiento
- Tiempo de ejecución en segundos
- Cantidad de iteraciones realizadas

# Finalizar

Para finalizar se puede ejecutar un comando para eliminar los archivos compilados.

--------------------------
|    $ make clean        | 
--------------------------
