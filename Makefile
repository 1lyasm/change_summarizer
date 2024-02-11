all:
	clang++ -g -fsanitize=address -Weverything src/main.cpp -o main
run:
	./main
