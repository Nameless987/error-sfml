all:
	g++ -I src/include -c main.cpp
	g++ main.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-network -l sfml-audio