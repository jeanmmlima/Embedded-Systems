EXEC	= main
CXX	= gcc
MAIN	= main.c
OPTIONS	= -O3 -Wall
LIBS	= -lufrn_lynx -lm
OBJECTS = ufrn_al5d.o

main:	clean ufrn_al5d lib_ufrn
	$(CXX) $(OPTIONS) $(MAIN) -L. $(LIBS) -o $(EXEC)

ufrn_al5d:
	$(CXX) $(OPTIONS) -c ufrn_al5d.c

lib_ufrn:
	ar rsc libufrn_lynx.a $(OBJECTS)
	rm $(OBJECTS)

demo:
	rm -f demo_lynx.tar.gz
	cp libufrn_lynx.a ./demo_lynx/lib/
	cp ufrn_al5d.h ./demo_lynx/include/
	tar czfv demo_lynx.tar.gz demo_lynx/
#tar -xzf Test.tar.gz

clean:
	clear
	rm -f $(OBJECTS)
	rm -f libufrn_lynx.a
	rm -f *~
	rm -f *.o

