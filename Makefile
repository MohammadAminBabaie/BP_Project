CC = gcc
CFLAGS = -Wall -g -Iinclude
SRC = src/main.c src/csv.c
OBJ = main.o csv.o
TARGET = project.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

csv.o: src/csv.c
	$(CC) $(CFLAGS) -c src/csv.c

clean:
	del *.o *.exe
