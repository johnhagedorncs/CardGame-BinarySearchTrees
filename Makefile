game: main.cpp cards.cpp utility.cpp
	g++ --std=c++20 main.cpp cards.cpp utility.cpp -o game

tests: cards.cpp tests.cpp
	g++ --std=c++20 cards.cpp tests.cpp -o tests

clean:
	rm game
	rm tests