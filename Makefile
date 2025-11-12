CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -Llib -lmingw32 -lSDL3

TARGET = kingdomino
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)

ICON_RC = icon.rc
ICON_OBJ = build/icon.o

all: $(TARGET)

$(TARGET): $(OBJ) $(ICON_OBJ)
	$(CC) $(OBJ) $(ICON_OBJ) -o $(TARGET).exe $(LDFLAGS)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(ICON_OBJ): $(ICON_RC)
	windres $< -o $@

clean:
	del /Q build\*.o *.exe