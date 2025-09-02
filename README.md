#  Pre-Proyecto

  
Este proyecto implementa un mini compilador para un lenguaje de programación que soporta dos tipos de datos: `int` y `bool`. El compilador realiza análisis léxico, sintáctico, semántico y genera código en pseudo-ensamblador.

## Características

* Tipos de datos soportados: int y bool
* Declaraciones: Variables y constantes
* Operaciones: Aritméticas (`+`, `-`, `*`, `/`) y lógicas (`&&`, `||`)
* Una sola funcion main con `return` de tipo `void`, `int` o `bool`.
* Análisis semántico: Verificación de tipos y tabla de símbolos
* Generación de código: Salida en pseudo-assembler.

##  Estructura del proyecto

### Directorios principales
*   `ast/`
    *   Contiene el código fuente del arbol de parsing	   			  
*   `compile/`
    *   Contiene el codigo fuente que implementa el traductor a un pseudo assembler
* `lexer`
    *   Contiene el analizador sintactico generado con `Flex`
*   `semantic/`
    *   Documentación adicional del proyecto [6].
*   `sintax/`
* `semantic/`
* `st`
    *   Conjuntos de datos utilizados o generados por el proyecto.
*   `test`: Arhchivos con código de prueba.
*   `README.md`: Este archivo.

#### Dependencias
- **gcc** (GNU Compiler Collection) - versión 4.8 o superior
- **make** (GNU Make) - versión 3.81 o superior  
- **flex** (Fast Lexical Analyzer) - versión 2.5 o superior
- **bison** (GNU Parser Generator) - versión 3.0 o superior

## Compilar el proyecto
```
make 
```

## Ejecución de tests
Utilizar archivos del directorio test/ para probar el  funcionamiento mini compilador.
```
./parser test/<archivo_fuente>
```

## Limpiar archivos generados
```
make clean
```

## Autor
Juarez Marcelo - Reynoso Juan Cruz