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
const double alpha = 0.1;
const double gamma_const = 0.9;
const double theta = 0.001;
const int EPISODE_NUM = 2000;
const int EPISODE_LIMIT = 100000;

enum action { UP, DOWN, LEFT, RIGHT};

vector<vector<vector<double>>> returns(100, vector<vector<double>>(4, vector<double>()));
vector<vector<double>> Q(100, vector<double>(4, 0.0));
Agent agent(Q, alpha, gamma_const);

int main(int argc, char** argv) {
	if (argc > 2 && strcmp(argv[1], "-m") == 0) {
		const double p1 = atof(argv[2]);
		const double p2 = atof(argv[3]);
	}
	int cnt = 0;
	for (int i = 0; i < EPISODE_NUM; i++) {

        if (++cnt % 1000 == 0) cout << "Episode: " << cnt << endl;
        
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

            // cout << ", goes to " << s_prime << " with R: " << reward << endl;
            //int a_prime = agent.pick_eplison_greedy_action(s_prime);


            agent.adjust_q_q_learning(s, a, s_prime, reward);

            s = s_prime;
            // cout << "Agent picks: " << a;
            terminated = environment.is_terminated() || ++count == EPISODE_LIMIT;
            if (count == EPISODE_LIMIT) cout << "*EXCESSIVE ITERATIONS*" << endl;
        }
	}
    agent.greedify_policy();
	cout << "Optimal policy: " << endl;
	agent.show_policy();

	return 0;
}
