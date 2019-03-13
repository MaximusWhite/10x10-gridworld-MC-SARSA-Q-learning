#include "agent.h"

const double epsilon = 0.1;

double non_max_prob() {
	return (epsilon / 4.0);
}

double max_prob() {
	return 1 - epsilon + non_max_prob();
}

Agent::Agent() : policy(vector<vector<double>>(100, vector<double>(4, 0.0))) {
	initialize_policy();
}

void Agent::initialize_policy() {
	uniform_int_distribution<int> distribution(0, 3);
		for (int s = 0; s < 100; s++) {
			bool max_used = false;
			int roll = distribution(generator);
			for (int a = 0; a < 4; a++) {
				if (a == roll) {
					policy[s][a] = max_prob();
				} else {
					policy[s][a] = non_max_prob();
				}
			}
		}
}

int Agent::pick_action(int s) {
	vector<double> options = policy[s];

	uniform_real_distribution<double> distribution(0.0f, 1.0f);
	double dice_roll = distribution(generator);
	double cum_sum = 0;
	for (int i = 0; i < 4; i++) {
		cum_sum += options[i];
		if (dice_roll <= cum_sum) {
			return i;
		}
	}

	return 0;
}