CC = clang

all: 2lab 3lab 4lab

2lab: 2lab.c
	$(CC) -o $@ $^

3lab: 3lab.c
	$(CC) -o $@ $^

4lab: 4lab.c
	$(CC) -o $@ $^




clean:
	rm -f 2lab 3lab 4lab
