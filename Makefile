CC=gcc
CFLAGS=-o editor editor.c -O2

all:editor

editor:editor.c
	$(CC) $(CFLAGS)

install:
	cp ./editor /usr/local/bin/editor

uninstall:
	rm /usr/local/bin/editor

clean:
	rm ./editor
