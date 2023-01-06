# makefile para o dedos.c

all: dedos

dedos: dedos.c
	gcc dedos.c -o dedos

clean:
	rm -f dedos
