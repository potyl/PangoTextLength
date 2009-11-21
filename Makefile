all: text-length

text-length: text-length.c
	gcc -std=c99 -g3 -O0 `pkg-config --libs --cflags pango pangocairo glib-2.0` -o $@ $<

clean:
	rm text-length
