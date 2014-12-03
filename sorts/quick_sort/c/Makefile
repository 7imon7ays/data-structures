CFLAGS=-Wall -g

all: quick-sort-spec quick-sort-print

quick-sort-spec: quick-sort-spec.c quick-sort.c
	gcc quick-sort-spec.c quick-sort.c -o quick-sort-spec

quick-sort-print: quick-sort-print.c quick-sort.c
	gcc quick-sort-print.c quick-sort.c -o quick-sort-print

clean:
	rm -f quick-sort-spec
	rm -f quick-sort-print

