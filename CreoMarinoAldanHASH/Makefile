ARCHS_C := main.c

OUTPUTS := $(ARCHS_C:.c=.out)

HEADERS := lista.h tabla_hash_encadenamiento.h tabla_hash_recolocacion.h
HEADERS_DIR := .
IMPLS_HEADERS := $(HEADERS:.h=.c)
OBJS_HEADERS := $(HEADERS:.h=.o)

OBJS := $(ARCHS_C:.c=.o) $(OBJS_HEADERS)


ARGS := -Wall -Wextra -pedantic -g -lm

all: $(OUTPUTS)

enc:
	-make clean
	-make all
	gcc main.o lista.o tabla_hash_encadenamiento.o -o main -L $(HEADERS_DIR) $(ARGS)
	./main

rec:
	-make clean
	-make all
	gcc main.o tabla_hash_recolocacion.o -o main -L $(HEADERS_DIR) $(ARGS)
	./main


$(OUTPUTS): $(OBJS)
	gcc $(@:.out=.o) -o $(@:.out=) -L $(HEADERS_DIR) $(ARGS)

%.o: %.c
	gcc -o $@ -c $< $(ARGS)

clean:
	-find . -type f -name '*.o' -delete
	-find . -type f -name '*.out' -delete
	-rm $(OUTPUTS:.out=)