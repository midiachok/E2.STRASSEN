CC = gcc
DELETE = rm
CFLAGS = -Wall -Wextra
TARGET = exac.exe
OBJ_FILES = main.o matrices.o

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -lm -o $(TARGET)

main.o: main.c matrices.h
	$(CC) $(CFLAGS) -c main.c

matrices.o: matrices.c matrices.h
	$(CC) $(CFLAGS) -c matrices.c

clean:
	$(DELETE) $(OBJ_FILES) $(TARGET)

.PHONY: clean
