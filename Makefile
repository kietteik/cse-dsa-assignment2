all: myMain.o processData.o 
	g++ -o myMain myMain.o processData.o 
processData.o: processData.cpp processData.h
	g++ -c processData.cpp -std=gnu++11
myMain.o: myMain.cpp main.h processData.h
	g++ -c myMain.cpp
clean: 
	rm *.o myMain