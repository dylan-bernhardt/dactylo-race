GCC = gcc -W -Wall -ansi -pedantic

vpath %.h include
vpath %.c src
vpath %.o obj

all : 
	mkdir obj
	make exe
	

%.o : %.c
	$(GCC) -c $< -Iinclude

cli : cli.o
	$(GCC) cli.o -o exe
	mv $^ ./obj

srv : srv.o
	$(GCC) srv.o -o srv

clean :
	rm -r ./obj exe