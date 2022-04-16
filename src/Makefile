CXX = g++
CXXFLAGS = -g -Wall

image: image.o main.o
	$(CXX) -o image image.o main.o $(CXXFLAGS)

main.o: main.cpp image.h
	$(CXX) -o main.o -c main.cpp $(CXXFLAGS)

image.o: image.cpp
	$(CXX) -o image.o -c image.cpp $(CXXFLAGS)

clean:
	rm image main.o image.o