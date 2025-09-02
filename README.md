#  Compiladores

  
Este proyecto implementa un mini compilador para un lenguaje que puede trabajar con dos tipos de datos; int y bool



#  Estructura del proyecto

## Directorios principales
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
    *   `dataset.csv`: Datos de muestra.
*   `README.md`: Este archivo.


├── ast/  
│ ├── tree.c  
│ └── tree.h  
│  
├── compile/  
│ ├── assembly_generator.c  
│ ├── assembly_generator.h  
│ └── assembly.txt  
│  
├── lexer/  
│ ├── calc-lexico.l  
│ ├── lex.yy.c  
│ └── lex.yy.o  
│  
├── semantic/  
│ ├── expr_solver.c  
│ ├── expr_solver.h  
│ ├── type_checker.c  
│ ├── type_checker.h  
│ └── type_checker.o  
│  
├── sintax/  
│ ├── calc-sintaxis.y  
│ ├── calc-sintaxis.output  
│ ├── calc-sintaxis.tab.c  
│ ├── calc-sintaxis.tab.h  
│ └── calc-sintaxis.tab.o  
│  
├── st/  
│ ├── symbol_table.c  
│ ├── symbol_table.h  
│ └── symbol_table.o  
│  
├── .gitignore  
├── Makefile  
├── parser  
├── preproyecto.pdf  
├── prueba.txt  
└── README.md


# Compilar el proyecto
```
make 
```

# Ejecución de los test
```
./parser test/test.txt
```
Para poder testear este proyecto se debe ejecutar con alguno de los archivos de prueba que se encuentran en la carpeta /test

#  Limpiar archivos generados
```
make clean
```