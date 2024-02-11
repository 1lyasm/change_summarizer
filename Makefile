all:
	clang++ -g -fsanitize=address -Weverything \
		-Wno-c++98-compat src/main.cpp -o main
run:
	./main
