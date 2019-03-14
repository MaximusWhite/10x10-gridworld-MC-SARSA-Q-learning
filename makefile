build-mc: mc.cpp
	clang++ -std=c++11 -o mc mc.cpp -w
run-mc: 
	make build-mc && ./mc
build-sarsa: sarsa.cpp
	clang++ -std=c++11 -o sarsa sarsa.cpp -w
run-sarsa:
	make build-sarsa && ./sarsa
build-q: q.cpp
	clang++ -std=c++11 -o q q.cpp -w
run-q:
	make build-q && ./q
build:
	make build-mc && make build-sarsa && make build-q
