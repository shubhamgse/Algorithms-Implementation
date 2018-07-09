all:bruteForce.out huffman.out dynamic.out backtrack.out

bruteForce.out:bruteForce.c
	gcc bruteForce.c -o bruteForce.out -lm

huffman.out:huffman.c
	gcc huffman.c -o huffman.out

dynamic.out:dynamic.c
	gcc dynamic.c -o dynamic.out

backtrack.out:backtrack.c
	gcc backtrack.c -o backtrack.out

clean:
	rm bruteForce.out huffman.out dynamic.out backtrack.out