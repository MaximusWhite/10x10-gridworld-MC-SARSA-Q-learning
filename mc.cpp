#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <ctime>

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

enum actions { UP, DOWN, LEFT, RIGHT};
map<string, int> reward_map = {{"transitional", -1} , {"terminal", 100}};
vector<vector<double>> V(4, vector<double>(25, 0.0)); 
vector<vector<vector<double>>> Q(4, vector<vector<double>>(25, vector<double>(4, 0.0)));
vector<vector<vector<double>>> rewards(4, vector<vector<double>>(25, vector<double>()));
vector<vector<actions>> policy(4, vector<actions>(25));


int main(int argc, char** argv) {
	if (argc > 2 && strcmp(argv[1], "-m") == 0) {
		p1 = atof(argv[2]);
		p2 = atof(argv[3]);

		for (int i = 0; i < 4; i++) {
			rewards[i] = atof(argv[4 + i]);
		}
	}

}