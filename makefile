build: main.cpp
	clang++ -std=c++11 -o main main.cpp -w
run: 
	make build && ./main
