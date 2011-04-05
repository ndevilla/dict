
CFLAGS = -O3 -g -I. -Wall -pedantic $(EXTRA)

all: dict

dict: dict.c dict.h
	$(CC) $(CFLAGS) -o $@ $< -DMAIN

clean:
	rm -f dict
	find . \( -name \*.dSYM  -prune \) -exec rm -rf '{}' ';'
