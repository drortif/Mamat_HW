CC=gcc
CCLINK = $(CC)
CFLAGS= -g -Wall -std=c99 -fpic
EXEC = prog.exe
RM = *.o *libgrades.so

$(EXEC):libgrades.so
	$(CCLINK) libgrades.so -so $(EXEC) 

libgrades.so: grades.o 
	$(CC) -shared grades.o -o libgrades.so 

grades.o: grades.c grades.h linked-list.h 
	$(CC) $(CFLAGS)  -c grades.c


clean:
	rm -rf $(RM)	