SRC=../src
OBJ=./obj
CC=gcc
FLEX=flex
BISON=bison

LEX_FLAGS=-o $@
BISON_FLAGS=-d
CFLAGS=-O2 -std=c11
LIBFLAGS=-lfl

LEX_SRC=$(SRC)/lexico.lex
LEX_DEST=$(SRC)/lexico.c
C_SRC=$(SRC)/*/*.c

BISON_SRC=$(SRC)/sintatico.y
BISON_DEST=$(SRC)/sintatico.tab.c

EXEC=main.out

all: $(EXEC)

$(BISON_DEST): $(BISON_SRC)
	$(BISON) $(BISON_FLAGS) -b $(SRC)/sintatico $^

$(LEX_DEST): $(LEX_SRC)
	$(FLEX) $(LEX_FLAGS) $^

# recompila caso tenha mudancas nos headers no arquivo do lex ou nos src
$(EXEC): $(BISON_DEST) $(LEX_DEST) $(C_SRC) $(SRC)/*/*.h
	$(CC) $(CFLAGS) $(LEX_DEST) $(BISON_DEST) $(C_SRC) $(LIBFLAGS) -o $(EXEC)

run: all
	./$(EXEC)

clean:
	rm $(EXEC) $(LEX_DEST) $(BISON_DEST)
