all:editor

editor:editor.c
	$(CC) -o editor editor.c -O2

install:
	cp ./editor /usr/local/bin/editor

uninstall:
	rm /usr/local/bin/editor

clean:
	rm ./editor
