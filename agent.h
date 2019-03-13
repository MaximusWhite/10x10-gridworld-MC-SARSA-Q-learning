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
		void initialize_policy();
		int pick_action(int s);

	private:
		random_device r;
		default_random_engine generator{ r() };
		vector<vector<double>> policy;

};