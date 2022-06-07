CX=g++
CXFLAGS=-g -Wall -std=c++11
OBJS=string.o field.o ip.o port.o
EXEC=firewall.exe
LIBS=libfirewall.so libinput.so
RM= rm -rf *.exe *.o libfirewall.so

#### firewall.exe ####
$(EXEC): main.o $(LIBS)
	$(CX) $(CXFLAGS) main.o -lfirewall -linput -L. -o firewall.exe


#### main.o ####
main.o: main.cpp input.h string.h field.h ip.h port.h 
	$(CX) $(CXFLAGS) -c -fpic main.cpp
	
#### libfirewall.so ####
libfirewall.so: $(OBJS)
	$(CX) $(CXFLAGS) -shared $(OBJS) -o libfirewall.so
	
string.o: string.cpp string.h
	$(CX) $(CXFLAGS) -c -fpic string.cpp
	
field.o: field.cpp field.h string.h
	$(CX) $(CXFLAGS) -c -fpic field.cpp

ip.o: ip.cpp ip.h field.h string.h
	$(CX) $(CXFLAGS) -c -fpic ip.cpp

port.o: port.cpp port.h field.h string.h
	$(CX) $(CXFLAGS) -c -fpic port.cpp


#### clean ####
clean:
	$(RM)
