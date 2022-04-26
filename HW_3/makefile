#variebles
CC=gcc
CCLINK = $(CC)
CFLAGS= -g -Wall -std=c99
OBJS=main.o file0.o file1.o file2.o file3.o file4.o 
EXEC = prog.exe
RM = *.o *.exe

#limkimg all the obj files to the exe file (first rule invoked by default)
$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC) 

#compiling all the modules
main.o: main.c file0.h file1.h file2.h file3.h file4.h
	$(CC) $(CFLAGS) -c main.c

file0.o: file0.h file0.c file0.h file1.h file3.h file4.h
	$(CC) $(CFLAGS) -c file0.c

file1.o: file1.h file1.c file0.h file2.h file3.h
	$(CC) $(CFLAGS) -c file1.c

file2.o: file2.h file2.c file1.h file3.h file4.h
	$(CC) $(CFLAGS) -c file2.c	

file3.o: file3.h file3.c file0.h file1.h file2.h file4.h
	$(CC) $(CFLAGS) -c file3.c	

file4.o: file4.h file4.c file0.h file2.h file3.h
	$(CC) $(CFLAGS) -c file4.c	

#rmvs all the obj files and al the exe files
clean:
	rm -rf $(RM)	