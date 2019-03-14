#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <ctime>
#include <random>
#include <utility>
#ifdef _WIN32
	#include "agent.h"
	#include "environment.h"
#else 
	#include "agent.cpp"
	#include "environment.cpp"
#endif

using namespace std;

double p1 = 0.4;
double p2 = 0.5;
const double gamma_const = 0.9;
const double theta = 0.001;
const double alpha = 0.1;
const int EPISODE_NUM = 20000;
const int EPISODE_LIMIT = 100000;

int time_steps = 0; 

enum action { UP, DOWN, LEFT, RIGHT};

vector<vector<vector<double>>> returns(100, vector<vector<double>>(4, vector<double>()));
vector<vector<double>> Q(100, vector<double>(4, 0.0));
Agent agent;

void generate_episode(vector<int> &states, vector<int> &actions, vector<int> &rewards) {
	random_device r;
	default_random_engine generator{ r() };
	bool terminated = false;
	uniform_int_distribution<int> distribution(0, 98);
	int start_state = distribution(generator);
	Environment environment(p1, p2, start_state);
	int count = 0;
	while (!terminated) {
		int s = environment.get_current_state();
		states.push_back(s);
		int a = agent.pick_action(s);
		actions.push_back(a);
		int reward = environment.get_reward(a);
		rewards.push_back(reward);
		time_steps++;
		terminated = environment.is_terminated() || ++count == EPISODE_LIMIT;
		//if (count == EPISODE_LIMIT) cout << "*EXCESSIVE ITERATIONS*" << endl;
	}
}

int main(int argc, char** argv) {
	if (argc > 2 && strcmp(argv[1], "-m") == 0) {
		p1 = atof(argv[2]);
		p2 = atof(argv[3]);
	}
	int count = 0;
	cout << "Running MC..."; 
	cout.flush();
	clock_t start = clock();
	for (int i = 0; i < EPISODE_NUM; i++) {
		vector<int> rewards;
		vector<int>	states;
		vector<int> actions;
		map<int, int> action_pairs;
		generate_episode(states, actions, rewards);
		double G = 0.0;

		for (int t = states.size() - 2; t >= 0; t--) {
			G = G * gamma_const + rewards[t+1];
			int s = states[t];
			int a = actions[t];
			(returns[s][a]).push_back(G);
			vector<double> state_action_returns = returns[s][a];
			float average = accumulate( state_action_returns.begin(), state_action_returns.end(), 0.0)/state_action_returns.size(); 
			Q[s][a] = average;
			int max_index = 0;
			double max_q = Q[s][0];
			for (int action = 1; action < 4; action++) {
				if (Q[s][action] > max_q) {
					max_index = action;
					max_q = Q[s][action];
				}
			}

			int optimal_action = max_index;
			agent.readjust_policy(s, optimal_action);
		}
	}
	double elapsed_time = (clock() - start) / (double)(CLOCKS_PER_SEC / 1000);
	cout << "Done" << endl;
	cout << "Episodes: " << EPISODE_NUM << endl;
	cout << "Total time steps: " << time_steps << endl;
	cout << "Computation time: " << elapsed_time / 1000 << "s" << endl;

	cout << "Optimal policy: " << endl;
	agent.show_policy();

	return 0;
}
