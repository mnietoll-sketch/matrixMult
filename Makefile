ejecutable: matrixMult.c
	gcc -Wall -pthread matrixMult.c -o ejecutable

run: ejecutable
	./ejecutable

clean:
	rm ejecutable
