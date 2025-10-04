CFLAGS = -std=c++20 -Wall

.PHONY: run
run: a.out
	./a.out

a.out: main.o
	clang++ main.o -o a.out

main.o: main.cpp regex.hpp
	clang++ $(CFLAGS) -c main.cpp -o main.o
