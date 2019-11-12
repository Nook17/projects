nook: main.o Tmsg.o
	g++ main.o Tmsg.o -o nook

main.o: main.cpp
	g++ -c main.cpp

Tmsg.o: Tmsg.cpp Tmsg.h
	g++ -c Tmsg.cpp

clean:
	rm *.o nook
