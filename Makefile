CC=tcc
CFLAGS=-Wall -Wextra -Wpedantic -O3

main: src/update.c 
	$(CC) $(CFLAGS) -o update src/update.c 

install:
	cp ./update /usr/local/bin/

clean:
	rm -rf /usr/local/bin/update
	rm -rf *.o
