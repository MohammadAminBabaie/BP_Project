CC = gcc
CFLAGS = -Wall -g -Iinclude

SRC = src/main.c \
      src/csv.c \
      src/utils.c \
      src/csv_numeric.c \
      src/csv_ohe.c \
	  src/stats.c \
	  src/impute.c \
	  src/plot.c \
	  src/feature_engineering.c \
	  src/scaling.c

OBJ = main.o csv.o utils.o csv_numeric.o csv_ohe.o stats.o impute.o plot.o feature_engineering.o scaling.o

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

stats.o: src/stats.c
	$(CC) $(CFLAGS) -c src/stats.c

impute.o: src/impute.c
	$(CC) $(CFLAGS) -c src/impute.c

plot.o: src/plot.c
	$(CC) $(CFLAGS) -c src/plot.c

feature_engineering.o: src/feature_engineering.c
	$(CC) $(CFLAGS) -c src/feature_engineering.c

scaling.o: src/scaling.c
	$(CC) $(CFLAGS) -c src/scaling.c

clean:
	del *.o *.exe
