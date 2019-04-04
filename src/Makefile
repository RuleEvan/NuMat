CC=gcc -m64
CFLAGS=-c -Wall -lm -ldl

all: NuMat

NuMat: main.o angular.o romberg.o potential.o brody.o av18.o file_io.o matrix_element.o data_gen.o 
	$(CC) main.o angular.o romberg.o potential.o brody.o av18.o file_io.o matrix_element.o data_gen.o -o NuMat -lm -ldl -lgsl -lgslcblas

main.o: main.c
	$(CC) $(CFLAGS) main.c

data_gen.o: data_gen.c
	$(CC) $(CFLAGS) data_gen.c

matrix_element.o: matrix_element.c
	$(CC) $(CFLAGS) matrix_element.c

file_io.o: file_io.c
	$(CC) $(CFLAGS) file_io.c

potential.o: potential.c
	$(CC) $(CFLAGS) potential.c

av18.o: av18.c
	$(CC) $(CFLAGS) av18.c

brody.o: brody.c
	$(CC) $(CFLAGS) brody.c

romberg.o: romberg.c
	$(CC) $(CFLAGS) romberg.c

angular.o: angular.c
	$(CC) $(CFLAGS) angular.c

clean:
	rm -rf *.o NuMat
