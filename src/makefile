HEADERS = enigma.h base64.h
GCC = g++ -std=c++11
default: main

base64.o: base64.cpp $(HEADERS)
	$(GCC) -c base64.cpp -o base64.o

enigma.o: enigma.cpp base64.o $(HEADERS)
	$(GCC) -c enigma.cpp -o enigma.o

main: main.cpp enigma.o base64.o
	$(GCC) -c main.cpp -o main.o
	$(GCC) main.o enigma.o base64.o -o enigma

clean:
	-rm -f *.o
	-rm -f enigma
