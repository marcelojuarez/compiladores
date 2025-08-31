# Compilador
CC = gcc
CFLAGS = -Wall -g -I. -Iast -Ist -Isintax -Ilexer -Isemantic

# Archivos y carpetas
BISON = bison -v -d
FLEX = flex

SRC_DIRS = sintax lexer ast st semantic
OBJS = sintax/calc-sintaxis.tab.o lexer/lex.yy.o ast/tree.o st/symbol_table.o semantic/type_chequer.o

TARGET = parser

# Regla principal
all: $(TARGET)

# Ejecutable final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Generar parser con Bison
sintax/calc-sintaxis.tab.c sintax/calc-sintaxis.tab.h: sintax/calc-sintaxis.y
	$(BISON) -o sintax/calc-sintaxis.tab.c $<

# Generar lexer con Flex
lexer/lex.yy.c: lexer/calc-lexico.l
	$(FLEX) -o $@ $<

# Compilar cada objeto
sintax/calc-sintaxis.tab.o: sintax/calc-sintaxis.tab.c
	$(CC) $(CFLAGS) -c -o $@ $<

lexer/lex.yy.o: lexer/lex.yy.c
	$(CC) $(CFLAGS) -c -o $@ $<

ast/tree.o: ast/tree.c ast/tree.h
	$(CC) $(CFLAGS) -c -o $@ $<

st/symbol_table.o: st/symbol_table.c st/symbol_table.h
	$(CC) $(CFLAGS) -c -o $@ $<

semantic/type_chequer.o: semantic/type_chequer.c semantic/type_chequer.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Limpiar archivos generados
clean:
	rm -f $(OBJS) $(TARGET) sintax/calc-sintaxis.tab.* lexer/lex.yy.c sintax/calc-sintaxis.output
