# Compilation
CC = gcc
CFLAGS = -Wall -Iinclude

# Linkage
LDFLAGS = -Llib -lmingw32 -lSDL3 -lSDL3_image

# Fichiers
TARGET = kingdomino
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)

# Ressources icône
ICON_RC = assets/images/icon.rc
ICON_OBJ = build/icon.res

# Dossier de sortie
BIN = bin
EXE = $(BIN)/$(TARGET).exe

# Règle principale
all: $(BIN) $(EXE)

# Créer le dossier bin si nécessaire
$(BIN):
	mkdir -p $(BIN)

# Générer l'exécutable dans bin/
$(EXE): $(OBJ) $(ICON_OBJ)
	$(CC) $(OBJ) $(ICON_OBJ) -o $@ $(LDFLAGS)

# Compilation des fichiers .c en .o
build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation du fichier .rc en .res
$(ICON_OBJ): $(ICON_RC)
	windres $< -O coff -o $@

# Nettoyage
clean:
	rm -rf build/*.o build/*.res $(EXE)
