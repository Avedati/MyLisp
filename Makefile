all: build/main.o build/lisp.o build/symtable.o build/stack.o build/striter.o
	gcc -o bin/my_lisp build/main.o build/lisp.o build/symtable.o build/stack.o build/striter.o

clean:
	rm -rf bin/my_lisp build/*.o

debug:
	gcc src/*.c -g -o bin/my_lisp

build/main.o: src/main.c include/lisp.h include/stack.h include/striter.h include/symtable.h
	gcc -o build/main.o -c src/main.c

build/lisp.o: src/lisp.c include/lisp.h include/stack.h include/striter.h include/symtable.h
	gcc -o build/lisp.o -c src/lisp.c

build/symtable.o: src/symtable.c include/symtable.h include/stack.h
	gcc -o build/symtable.o -c src/symtable.c

build/stack.o: src/stack.c include/stack.h
	gcc -o build/stack.o -c src/stack.c

build/striter.o: src/striter.c include/striter.h
	gcc -o build/striter.o -c src/striter.c
