CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11
LDFLAGS =

.PHONY: forests clean

forests: main.o operations.o tree.o charvector.o namecheck.o
	$(CC) $(LDFLAGS) -o $@ $^

charvector.o: charvector.c charvector.h
	$(CC) $(CFLAGS) -c $<

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c $<

operations.o: operations.c operations.h
	$(CC) $(CFLAGS) -c $<

namecheck.o: namecheck.c namecheck.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c charvector.h tree.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o forests
