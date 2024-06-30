FIC = $(shell ls *.c)
EXEC = ../bin/
BIN = minijeu
DEBUG = -DDEBUG
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
OPTIONS = -Wall -Wextra -g
CC = gcc
OBJ = $(FIC:.c=.o)
ART = $(FIC:.c=.gch)

all: $(BIN)

debug: OPTIONS += $(DEBUG)
debug: clean
debug: $(BIN)

$(BIN): $(OBJ) $(EXEC)
	$(CC) -o $(EXEC)$(BIN) $(OBJ) $(OPTIONS) $(LFLAGS)

$(EXEC):
	mkdir $(EXEC)

%.o: %.c
	$(CC) -c -o $@ $< $(OPTIONS) $(LFLAGS)

remake: clean
	make

clean:
	rm -f $(OBJ) $(ART)
