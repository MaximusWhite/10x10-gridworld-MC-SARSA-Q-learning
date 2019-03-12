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

double p1 = 0.4;
double p2 = 0.5;
const double gamma_const = 0.9;
const double theta = 0.001;
const double alpha = 0.1;
const int EPISODE_NUM = 1000;

enum action { UP, DOWN, LEFT, RIGHT};

vector<vector<vector<int>>> returns(100, vector<vector<int>>(4, vector<int>()));
vector<vector<double>> Q(100, vector<double>(4, 0.0));

//map<string, int> reward_map = {{"transitional", -1} , {"terminal", 100}};
//vector<vector<double>> V(4, vector<double>(25, 0.0)); 
//vector<vector<vector<double>>> Q(4, vector<vector<double>>(25, vector<double>(4, 0.0)));
//vector<vector<vector<double>>> rewards(4, vector<vector<double>>(25, vector<double>()));
//vector<vector<vector<double>>> policy(4, vector<vector<double>>(25, vector<double>(4)));

void generate_episode(vector<int> &states, vector<int> &actions, vector<int> &rewards) {
	random_device r;
	default_random_engine generator{ r() };
	bool terminated = false;
	uniform_int_distribution<int> distribution(0, 98);
	int start_state = distribution(generator);
	Environment environment = Environment(p1, p2, start_state);
	Agent agent = Agent();
	while (!terminated) {
		int s = environment.get_current_state();
		states.push_back(s);
		int a = agent.pick_action(s);
		actions.push_back(a);
		int reward = environment.get_reward(a);
		rewards.push_back(reward);
		

	}
}

int main(int argc, char** argv) {
	if (argc > 2 && strcmp(argv[1], "-m") == 0) {
		const double p1 = atof(argv[2]);
		const double p2 = atof(argv[3]);
	}

	for (int i = 0; i < EPISODE_NUM; i++) {
		vector<int> rewards;
		vector<int>	states;
		vector<int> actions;
		generate_episode(states, actions, rewards);


	}

	return 0;
}
