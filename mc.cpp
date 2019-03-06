#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <ctime>
#include <random>

using namespace std;

double p1 = 0.5;
double p2 = 0.4;
const double p3 = (1 - p1 - p2) / 2;
const double off_the_grid_ignore = p1 + p2;
const double off_the_grid_adjacent = (1 - p1 - p2) / 2;
const double gamma_const = 0.9;
const double theta = 0.001;
const double epsilon = 0.1;
const double alpha = 0.1;

random_device r;
default_random_engine generator{ r() };

enum action { UP, DOWN, LEFT, RIGHT};
map<string, int> reward_map = {{"transitional", -1} , {"terminal", 100}};
vector<vector<double>> V(4, vector<double>(25, 0.0)); 
vector<vector<vector<double>>> Q(4, vector<vector<double>>(25, vector<double>(4, 0.0)));
vector<vector<vector<double>>> rewards(4, vector<vector<double>>(25, vector<double>()));
vector<vector<vector<double>>> policy(4, vector<vector<double>>(25, vector<double>(4)));

void initialize_policy();
double max_prob();
double non_max_prob();

int main(int argc, char** argv) {
	if (argc > 2 && strcmp(argv[1], "-m") == 0) {
		p1 = atof(argv[2]);
		p2 = atof(argv[3]);
	}

	initialize_policy();

	return 0;
}

double non_max_prob() {
	return (epsilon / 4.0);
}

double max_prob() {
	return 1 - epsilon + non_max_prob();
}

void initialize_policy() {
  	uniform_int_distribution<int> distribution(0,3);

	for (int cluster = 0; cluster < 4; cluster++) {
		for (int s = 0; s < 25; s++) {
			bool max_used = false;
			int roll = distribution(generator);
			for (int a = 0; a < 4; a++) {
				if (a == roll) {
					policy[cluster][s][a] = max_prob();
				} else {
					policy[cluster][s][a] = non_max_prob();
				}
			}
		}
	}
}