CP = g++
CF = -std=c++11

all: main.o Map.o
	$(CP) $(CF) main.o Map.o -o path

main.o: main.cpp
	$(CP) $(CF) -c main.cpp -o main.o

Map.o: Map.cpp
	$(CP) $(CF) -c Map.cpp -o Map.o

clean:
	rm -f *.o path