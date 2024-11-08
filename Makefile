CC = clang

all: l2 l3 l4 l5 l6 l8

l2: 2lab.c
	$(CC) -o $@ $^

l3: 3lab.c
	$(CC) -o $@ $^

l4: 4lab.c
	$(CC) -o $@ $^

l5: 5lab.c
	$(CC) -o $@ $^

l6: 6lab.c
	$(CC) -o $@ $^

l8: 8lab.c
	$(CC) -o $@ $^

clean:
	rm -f l2 l3 l4 l5 l6 l8
