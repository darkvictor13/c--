SRC=../src

CC=gcc
FLEX=flex

CFLAGS=-O2
LIBFLAGS=-lfl -lm

LEX_SRC=$(SRC)/cmm.lex
LEX_DEST=$(SRC)/main.c
C_SRC=$(SRC)/*/*.c
LEX_FLAGS=-o $@

EXEC=main.out

all: $(EXEC)

$(EXEC): $(LEX_DEST)
	$(CC) $(CFLAGS) $(LEX_DEST) $(C_SRC) $(LIBFLAGS) -o $(EXEC)

$(LEX_DEST): $(LEX_SRC)
	$(FLEX) $(LEX_FLAGS) $^

run: all
	./$(EXEC)

clean:
	rm $(EXEC) $(LEX_DEST)
