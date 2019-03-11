#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <ctime>
#include <random>
#include "agent.h"
#include "environment.h"

using namespace std;

const double gamma_const = 0.9;
const double theta = 0.001;

const double alpha = 0.1;

enum action { UP, DOWN, LEFT, RIGHT};
map<string, int> reward_map = {{"transitional", -1} , {"terminal", 100}};
vector<vector<double>> V(4, vector<double>(25, 0.0)); 
vector<vector<vector<double>>> Q(4, vector<vector<double>>(25, vector<double>(4, 0.0)));
vector<vector<vector<double>>> rewards(4, vector<vector<double>>(25, vector<double>()));
vector<vector<vector<double>>> policy(4, vector<vector<double>>(25, vector<double>(4)));

void generate_episode(vector<int> &states, vector<int> &actions, vector<int> &rewards) {
	random_device r;
	default_random_engine generator{ r() };
	bool terminated = false;
	uniform_int_distribution<int> distribution(0, 98);
	states.push_back(distribution(generator));
	while (!terminated) {

	}
}

int main(int argc, char** argv) {
	if (argc > 2 && strcmp(argv[1], "-m") == 0) {
		const double p1 = atof(argv[2]);
		const double p2 = atof(argv[3]);
	}


	return 0;
}
