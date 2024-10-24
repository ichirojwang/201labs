CC = clang

all: l2 l3 l4 l7

l2: 2lab.c
	$(CC) -o $@ $^

l3: 3lab.c
	$(CC) -o $@ $^

l4: 4lab.c
	$(CC) -o $@ $^

l7: 7lab.c
	$(CC) -o $@ $^




clean:
	rm -f l2 l3 l4 l7
