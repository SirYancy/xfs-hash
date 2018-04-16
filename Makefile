CXX = g++
FLAGS += -std=c++11 -pthread -Wall -g

all: client

tcp.o: tcp.h tcp.cpp
	$(CXX) $(FLAGS) -c tcp.cpp

client.o: client.cpp
	$(CXX) $(FLAGS) -c client.cpp

client: client.o tcp.o
	$(CXX) $(FLAGS) -c client client.o tcp.o

clean:
	rm core *.o client
