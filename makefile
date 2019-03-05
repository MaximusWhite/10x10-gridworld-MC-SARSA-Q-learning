build: mc.cpp
	clang++ -std=c++11 -o mc mc.cpp -w
run-mc: 
	make build && ./mc
