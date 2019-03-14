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
const double alpha = 0.2;
const double gamma_const = 0.9;
const double theta = 0.001;
const int EPISODE_NUM = 20000;
const int EPISODE_LIMIT = 100000;

int time_steps = 0; 

enum action { UP, DOWN, LEFT, RIGHT};

vector<vector<vector<double>>> returns(100, vector<vector<double>>(4, vector<double>()));
vector<vector<double>> Q(100, vector<double>(4, 0.0));
Agent agent(Q, alpha, gamma_const);

int main(int argc, char** argv) {
	if (argc > 2 && strcmp(argv[1], "-m") == 0) {
		p1 = atof(argv[2]);
		p2 = atof(argv[3]);
	}
	int cnt = 0;
    cout << "Running Q-learning..."; 
    cout.flush();
    clock_t start = clock();
	for (int i = 0; i < EPISODE_NUM; i++) {
        
        random_device r;
        default_random_engine generator{ r() };
        bool terminated = false;
        uniform_int_distribution<int> distribution(0, 98);
        int start_state = distribution(generator);
        Environment environment(p1, p2, start_state);
        int s = environment.get_current_state();
        int count = 0;
        while (!terminated) {
            int a = agent.pick_eplison_greedy_action(s);
            int reward = environment.get_reward(a);
            int s_prime = environment.get_current_state();

            agent.adjust_q_q_learning(s, a, s_prime, reward);

            s = s_prime;
            time_steps++;

            terminated = environment.is_terminated() || ++count == EPISODE_LIMIT;
        }
	}

    double elapsed_time = (clock() - start) / (double)(CLOCKS_PER_SEC / 1000);
	cout << "Done" << endl;
	cout << "Episodes: " << EPISODE_NUM << endl;
	cout << "Total time steps: " << time_steps << endl;
	cout << "Computation time: " << elapsed_time / 1000 << "s" << endl;

    agent.greedify_policy();
	cout << "Optimal policy: " << endl;
	agent.show_policy();

	return 0;
}
