CXX = g++
CXXFLAGS = -std=c++20 -Wall -g

all: game_set game tests

card.o: card.cpp card.h
	$(CXX) $(CXXFLAGS) -c card.cpp

card_list.o: card_list.cpp card_list.h card.h
	$(CXX) $(CXXFLAGS) -c card_list.cpp

main_set.o: main_set.cpp card.h
	$(CXX) $(CXXFLAGS) -c main_set.cpp

main.o: main.cpp card_list.h card.h
	$(CXX) $(CXXFLAGS) -c main.cpp

tests.o: tests.cpp card_list.h card.h
	$(CXX) $(CXXFLAGS) -c tests.cpp

game_set: main_set.o card.o
	$(CXX) $(CXXFLAGS) -o game_set main_set.o card.o

game: main.o card_list.o card.o
	$(CXX) $(CXXFLAGS) -o game main.o card_list.o card.o

tests: tests.o card_list.o card.o
	$(CXX) $(CXXFLAGS) -o tests tests.o card_list.o card.o

clean:
	rm -f *.o game_set game tests
