#
#makefile for CX compiler
#

#variables for makefile
OBJS += parse.o verb.o list.o interpreter.o error_handle.o

#
#make rules
#
%.c: %.l
	flex  -o $@ -i $<
%.c: %.y
	bison -o $@ -dvt $<

#
#targets and sources
#
#Final program
gcx: parse.c verb.c parse.h $(OBJS)
	cc -o gcx $(OBJS) -ly

verb.c: verb.l
parse.c: parse.y
verb.o: verb.c parse.h parse.c
parse.o: parse.c parse.h interpreter.h list.h
error_handle.o: error_handle.h error_handle.c parse.h
list.o: list.c list.h 
interpreter.o: interpreter.c interpreter.h list.h parse.h



#
#clean all mid-produce files
#

.PHONY: clean

clean:
	-rm $(OBJS) parse.c parse.h gcx verb.c parse.output


