# Consideraciones

- Antes de ejecutar, se debe tener en cuenta que la carpeta con las instancias debe estar en la misma ruta que el ejecutable, y debe llamarse "WTA".
- Dimensión se le denominará a la cantidad de armas y objetivos que tiene cada instancia.
- Las instancias deben tener el formato de nombre "wta{dimension}.txt".

# Ejecutar 

Lo siguiente compilará el código y luego lo ejecutará introduciendo la instancia de 5 objetivos y armas.

--------------------------
|    $ make              |
|    $ ./main 5          | 
--------------------------

# Árbol de proyecto

- root
    - WTA
        - wta5.txt
        ...
        - wta200.txt
    - main.cpp
    - Makefile

# Finalizar

Para finalizar se puede ejecutar un comando para eliminar los archivos compilados.

--------------------------
|    $ make clean        | 
--------------------------