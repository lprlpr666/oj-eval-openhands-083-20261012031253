code: main.c
	gcc -o code main.c

.PHONY: all clean
all: code

clean:
	rm -f code