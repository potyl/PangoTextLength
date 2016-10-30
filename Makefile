all: text-length

text-length: text-length.c
	gcc -std=c99 -g3 -O0 -o $@ $< `pkg-config --libs --cflags pango pangocairo glib-2.0`

clean:
	rm -rf text-length text-length.dSYM

