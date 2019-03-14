build-mc: mc.cpp
	clang++ -std=c++11 -o mc mc.cpp -w
run-mc: 
	make build-mc && ./mc
build-sarsa: sarsa.cpp
	clang++ -std=c++11 -o sarsa sarsa.cpp -w
run-sarsa:
	make build-sarsa && ./sarsa
build-q-learning: q-learning.cpp
	clang++ -std=c++11 -o q-learning q-learning.cpp -w
run-q-learning:
	make build-q-learning && ./q-learning
