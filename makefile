CFLAGS = -c -Wall -Wextra -Werror -std=c11 -O2
CC = gcc
OBJ = wiersze.o dynamic_array.o heap_sort.o \
	line_record.o line_set.o list.o parsers.o \
	 safe_funcs.o sort_lex.o splay_tree.o

.PHONY: all clean

all: similar_lines

similar_lines: $(OBJ)
	$(CC) -o $@ $(OBJ)

wiersze.o: wiersze.c
	$(CC) $(CFLAGS) wiersze.c

dynamic_array.o: dynamic_array.c dynamic_array.h
	$(CC) $(CFLAGS) dynamic_array.c

heap_sort.o: heap_sort.c heap_sort.h
	$(CC) $(CFLAGS) heap_sort.c

line_record.o: line_record.c line_record.h
	$(CC) $(CFLAGS) line_record.c

line_set.o: line_set.c line_set.h
	$(CC) $(CFLAGS) line_set.c

list.o: list.c list.h
	$(CC) $(CFLAGS) list.c

parsers.o: parsers.c parsers.h
	$(CC) $(CFLAGS) parsers.c

safe_funcs.o: safe_funcs.c safe_funcs.h
	$(CC) $(CFLAGS) safe_funcs.c

sort_lex.o: sort_lex.c sort_lex.h
	$(CC) $(CFLAGS) sort_lex.c

splay_tree.o: splay_tree.c splay_tree.h
	$(CC) $(CFLAGS) splay_tree.c

clean:
	-rm $(OBJ) similar_lines
