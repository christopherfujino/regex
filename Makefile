CFLAGS = -std=c++20 -Wall

.PHONY: run
run: a.out
	./a.out

a.out: main.cpp
	clang++ $(CFLAGS) main.cpp -o a.out
