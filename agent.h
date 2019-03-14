#pragma once

#include <vector>
#include <map>
#include <cmath>
#include <ctime>
#include <random>
using namespace std;


class Agent {
	public: 
		Agent();
		Agent(vector<vector<double>> q_generated, double a, double gamma_c);
		void initialize_policy();
		int pick_action(int s);
		int pick_eplison_greedy_action(int s);
		void readjust_policy(int state, int optimal_action);
		void adjust_q_sarsa(int s, int a, int s_prime, int a_prime, int r);
		void adjust_q_q_learning(int s, int a, int s_prime, int r);
		void greedify_policy();
		void show_policy();

	private:
		double alpha;
		double gamma_constant;
		vector<vector<double>> Q;
		random_device r;
		default_random_engine generator{ r() };
		vector<vector<double>> policy;

};