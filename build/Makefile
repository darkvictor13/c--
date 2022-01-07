SRC=../src

CC=gcc
FLEX=flex

LEX_FLAGS=-o $@
CFLAGS=-O2
LIBFLAGS=-lfl -lm

LEX_SRC=$(SRC)/cmm.lex
LEX_DEST=$(SRC)/main.c
C_SRC=$(SRC)/*/*.c

EXEC=main.out

all: $(EXEC)

# recompila caso tenha mudancas nos headers no arquivo do lex ou nos src
$(EXEC): $(LEX_DEST) $(C_SRC) $(SRC)/*/*.h
	$(CC) $(CFLAGS) $(LEX_DEST) $(C_SRC) $(LIBFLAGS) -o $(EXEC)

$(LEX_DEST): $(LEX_SRC)
	$(FLEX) $(LEX_FLAGS) $^

run: all
	./$(EXEC)

clean:
	rm $(EXEC) $(LEX_DEST)
