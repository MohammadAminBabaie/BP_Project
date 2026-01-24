CC = gcc
CFLAGS = -Wall -g -Iinclude

SRC = src/main.c \
      src/csv.c \
      src/utils.c \
      src/csv_numeric.c \
      src/csv_ohe.c

OBJ = main.o csv.o utils.o csv_numeric.o csv_ohe.o

TARGET = project.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

csv.o: src/csv.c
	$(CC) $(CFLAGS) -c src/csv.c

utils.o: src/utils.c
	$(CC) $(CFLAGS) -c src/utils.c

csv_numeric.o: src/csv_numeric.c
	$(CC) $(CFLAGS) -c src/csv_numeric.c

csv_ohe.o: src/csv_ohe.c
	$(CC) $(CFLAGS) -c src/csv_ohe.c

clean:
	del *.o *.exe
