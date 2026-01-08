CC = gcc
CFLAGS = -Wall -g

OBJ = main.o csv.o stats.o preprocess.o model.o

project.exe: $(OBJ)
	$(CC) $(OBJ) -o project.exe

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	del *.o project.exe
