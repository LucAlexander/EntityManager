CC=gcc
CCWIN=x86_64-w64-mingw32-gcc
CFLAGS=-lm
CDEBUGFLAGS=-Wall -g
FILES=main.c systems.h systems.c asciiEsc.h entities.h entities.c hashMap.h hashMap.c vector.h vector.c memarena.h memarena.c bitmasks.h bitmasks.c
OUT=run

compile:
	clear
	$(CC) $(FILES) $(CFLAGS) -o $(OUT)

debug:
	clear
	$(CC) $(FILES) $(CFLAGS) $(CDEBUGFLAGS) -o $(OUT)

compile-windows:
	clear
	$(CCWIN) $(FILES) $(CFLAGS) -o $(OUT).exe

debug-windows:
	clear
	$(CCWIN) $(FILES) $(CFLAGS) $(CDEBUGFLAGS) -o $(OUT).exe

clean:
	rm -f $(OUT)
	rm -f $(OUT).exe

