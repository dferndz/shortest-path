CP = g++
CF = -std=c++11
PATH = ./src/
OUTPUT = path

all: main.o Map.o
	$(CP) $(CF) main.o Map.o -o $(OUTPUT)

main.o: $(PATH)main.cpp
	$(CP) $(CF) -c $(PATH)main.cpp -o main.o

Map.o: $(PATH)Map.cpp
	$(CP) $(CF) -c $(PATH)Map.cpp -o Map.o

clean:
	rm Map.o main.o path