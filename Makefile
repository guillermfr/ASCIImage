# commande pour compiler
CC=gcc
CP=cp
CFLAGS=-Wall
RM=rm -r

#nom des dossiers
SRC=src
OBJ=obj
DATA=data

#arguments pour trouver les éléments dans les dossiers
SRCS=$(wildcard $(SRC)/*.c)
HEADS=$(wildcard $(SRC)/*.h)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

#dossier pour l'executable
BINDIR=bin
BIN=$(BINDIR)/main

.PHONY: dirs clean

#programme du make
all: dirs $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

dirs:
	mkdir -p $(BINDIR) $(OBJ)
#	mkdir -p $(BINDIR) $(OBJ) $(DATA)

clean:
	$(RM) $(BINDIR) || echo Rien à supprimer dans bin
	$(RM) $(OBJ) || echo Rien à supprimer dans obj
#	$(RM) $(DATA) || echo Rien à supprimer dans data